/**
 * @file sketch.ino
 * @author Nathanael Barben
 * @author Sven Marc 'cybrox' Gehring
 * @date 2015-08-04
 * @brief Button-dependent bar counter
 */


#include <Matrix_RKAG.h>
#include <Wire.h>
#include <SPI.h>

char barMap[] = { 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80 };
unsigned int barStep[] = { 0x00, 0x00, 0x00 };

void setup() {
    matrix.init();
    matrix.clear();
}

void loop() {
    matrix.read_io();

    if (matrix.taste_1) barStep[0]++;
    if (matrix.taste_2) barStep[1]++;
    if (matrix.taste_3) barStep[2]++;
    if (barStep[0] >= 16) barStep[0] = 1;
    if (barStep[1] >= 16) barStep[1] = 1;
    if (barStep[2] >= 16) barStep[2] = 1;
    if (matrix.taste_1 || matrix.taste_2 || matrix.taste_3) delay(250);

    matrix.write(barMap[barStep[0]], barMap[barStep[0]],
                0x00, barMap[barStep[1]], barMap[barStep[1]],
                0x00, barMap[barStep[2]], barMap[barStep[2]]);
}