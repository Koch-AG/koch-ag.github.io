/**
 * @file sketch.ino
 * @author Nathanael Barben
 * @author Sven Marc 'cybrox' Gehring
 * @date 2015-08-04
 * @brief Button-dependent bar counter
 */


#include <Magenta_lib.h>

char barMap[] = { 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80 };
unsigned int barStep[] = { 0x00, 0x00, 0x00 };

void setup() {
    megentaobj.init();
    megentaobj.clear();
}

void loop() {
    megentaobj.read_io();

    if (megentaobj.button_1) barStep[0]++;
    if (megentaobj.button_2) barStep[1]++;
    if (megentaobj.button_3) barStep[2]++;
    if (barStep[0] >= 16) barStep[0] = 1;
    if (barStep[1] >= 16) barStep[1] = 1;
    if (barStep[2] >= 16) barStep[2] = 1;
    if (megentaobj.button_1 || megentaobj.button_2 || megentaobj.button_3) delay(250);

    megentaobj.write(barMap[barStep[0]], barMap[barStep[0]],
                0x00, barMap[barStep[1]], barMap[barStep[1]],
                0x00, barMap[barStep[2]], barMap[barStep[2]]);
}