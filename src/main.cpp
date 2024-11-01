#include <Arduino.h>
#include "EPD_Display.h"

EPD_Display display(EPD_WIDTH, EPD_HEIGHT);

// void screenTest() {
//     display.clearScreen();
//     display.drawLine(10, 10, 140, 10);
//     display.drawLine(10, 10, 10, 140);
//     display.drawLine(10, 140, 140, 140);
//     display.drawLine(140, 10, 140, 140);
//     display.UpdateAndclearDisplay();
//     delay(1000);

//     display.drawBox(20, 20, 100, 100);
//     display.UpdateAndclearDisplay();
//     delay(1000);

//     for (int x = 0; x < 151; x += 2) {
//         for (int y = 0; y < 151; y += 2) {
//             display.drawPixel(x, y);
//         }
//     }
//     display.UpdateAndclearDisplay();
//     delay(1000);

//     for (int y = 0; y < 151; y++) {
//         for (int x = 0; x < 151; x++) {
//             if ((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0)) {
//                 display.drawPixel(x, y);
//             }
//         }
//     }
//     display.updateDisplay();
// }

void setup() {
    display.begin();
    // screenTest();
}

void loop() {
    delay(5000);
}
