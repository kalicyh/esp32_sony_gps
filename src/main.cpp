#include <Arduino.h>
#include "EPD_Display.h"

EPD_Display display(EPD_WIDTH, EPD_HEIGHT);

void screenTest() {
    display.clearScreen();
    // display.drawLine(10, 10, 140, 10);
    // display.drawCircleHelper(76,76,10,1);
    // display.drawCircleHelper(76,76,15,2);
    // display.drawCircleHelper(76,76,20,4);
    // display.drawCircleHelper(76,76,25,8);
    // display.drawLine(10, 10, 10, 140);
    // display.drawLine(10, 140, 140, 140);
    // display.drawLine(140, 10, 140, 140);
    display.drawRoundedButton(16,40,50,80,10);
    display.drawRoundedButton(86,40,50,80,10);
    // delay(1000);

    // display.drawBox(20, 20, 100, 100);
    // display.drawFastHLine(10,15,10);
    // display.drawFastHLine(12,15,15);
    // display.drawFastHLine(140,15,10);
    // display.drawFastVLine(140,15,10);
    // display.UpdateAndclearDisplay();

    display.updateDisplay();
}

void setup() {
    display.begin();
    screenTest();
}

void loop() {
    delay(5000);
}
