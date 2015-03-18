/**
 * @file sketch.ino
 * @author Sven Marc 'cybrox' Gehring
 * @date 2015-02-20
 * @brief Koch Matrix example file
 */


#include <Matrix_RKAG.h>
#include <SPI.h>
#include <Wire.h>

#define OBJECTS 5
#define WINNING_TIME 130


/**
 * Variabeldeklaration. Alle hier deklarierten Variablen
 * und Konstanten sind global, in jeder Funktion, verfügbar.
 */
bool started = false;
int  points = 0x00;
int  iteration = 0x00;
char positionX[OBJECTS];
char positionY[OBJECTS];
char leds[8];


/**
 * Setup wird einmal am Anfang des Programmes ausgeführt.
 * Hier können alle benötigten Werte initialisiert und
 * Standardparameter eingestellt werden.
 */
void setup() {
    matrix.init();                                                 /* initialisiere matrix objekt */
    Serial.begin(9600);

    // Arrays mit nullen füllen
    for(int i = 0; i < OBJECTS; i++) {
        positionX[i] = 0x00;
        positionY[i] = 0x00;
    }

    for(int i = 0; i < 8; i++) {
        leds[i] = 0x00;
    }
}


/**
 * Loop wird während dem Programmablauf endlos ausgeführt.
 * Dieser Teil beinhaltet das eigentliche Programm.
 */
void loop() {
    matrix.read_io();

    delay(10);
    iteration++;

    if (started) {
        for(int i = 0; i < 8; i++) { leds[i] = 0x00; }

        // Objekt zufällig generieren
        if (iteration >= (100 * ((matrix.potentiometer_0 + 100) / 1024.0)) ) {
            if (random(0, OBJECTS) == 3) {
                for(int i = 0; i < OBJECTS; i++) {
                    if (positionX[i] == 0x00) {
                        positionX[i] = random(1, 4);
                        positionY[i] = 0x00;
                    }
                }
            }
        }



        // Für jedes Objekt...
        for (int i = 0; i < OBJECTS; i++) {
            // Objekte nach unten verschieben
            if (iteration >= (100 * ((matrix.potentiometer_0 + 100) / 1024.0)) ) {
                iteration = 0x00;
                positionY[i]++;
            }

            // Objekte auf Tastendruck überprüfen
            if(positionY[i] > 5) {
                if((positionX[i] == 1 && matrix.taste_1) ||
                   (positionX[i] == 2 && matrix.taste_2) ||
                   (positionX[i] == 3 && matrix.taste_3)) {
                   positionX[i] = 0x00;
                   positionY[i] = 0x00;
                   points++;
               }

            }

            // Objekte auf Position überprüfen
            if(positionY[i] > 7) {
                started = false;
                for(int i = 0; i < OBJECTS; i++) {
                    positionX[i] = 0x00;
                    positionY[i] = 0x00;
                    delay(WINNING_TIME);
                }
            }

            // Objekte auf der Matrix anzeigen
            if (positionX[i] != 0x00 && positionY[i] != 0x00) {
                displayObject(positionX[i], positionY[i]);
            }

            matrix.write_array(leds);
        }

    } else {
        matrix.write(0xFF, 0xFF, 0x00, 0x00, points, 0x00, 0xFF, 0xFF);
        if (matrix.taste_1 || matrix.taste_2 || matrix.taste_3) {
            started = true;
            points = 0x00;
        }
    }
}


void displayObject(int x, int y) {
    int mask[] = { 0x00, 0xC0, 0x18, 0x3 };
    leds[y] |= mask[x];
}

