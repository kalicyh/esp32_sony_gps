#include "EPD_Display.h"

EPD_Display::EPD_Display(int16_t w, int16_t h) : Adafruit_GFX(w, h) {
    buffer = new uint8_t[EPD_WIDTH * EPD_HEIGHT / 8];
}

EPD_Display::~EPD_Display() {
    delete[] buffer;
}

void EPD_Display::begin() {
    pinMode(EPD_CS_PIN, OUTPUT);
    pinMode(EPD_DC_PIN, OUTPUT);
    pinMode(EPD_RST_PIN, OUTPUT);
    pinMode(EPD_BUSY_PIN, INPUT);
    SPI.begin(EPD_SCK_PIN, -1, EPD_MOSI_PIN, EPD_CS_PIN);
    epdInit();
}

void EPD_Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
    if (x < 0 || x >= width() || y < 0 || y >= height()) return;

    uint16_t byteIndex = (y * 19) + (x / 8);
    uint8_t bitIndex = x % 8;

    if (color) {
        buffer[byteIndex] &= ~(1 << (7 - bitIndex));
    } else {
        buffer[byteIndex] |= (1 << (7 - bitIndex));
    }
}

void EPD_Display::clearScreen() {
    memset(buffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 8);
}

void EPD_Display::updateDisplay() {
    sendCommand(0x24);
    for (uint16_t i = 0; i < (EPD_WIDTH * EPD_HEIGHT / 8); i++) {
        sendData(buffer[i]);
    }
    sendCommand(0x20);
    waitUntilIdle();
}

void EPD_Display::UpdateAndclearDisplay() {
    updateDisplay();
    clearScreen();
}

void EPD_Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    int16_t dx = abs(x1 - x0);
    int16_t dy = abs(y1 - y0);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;

    while (true) {
        drawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int16_t err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void EPD_Display::drawBox(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    drawLine(x, y, x + w - 1, y, color);
    drawLine(x, y, x, y + h - 1, color);
    drawLine(x + w - 1, y, x + w - 1, y + h - 1, color);
    drawLine(x, y + h - 1, x + w - 1, y + h - 1, color);
}

void EPD_Display::epdInit() {
    epdReset();
    sendCommand(0x12);
    waitUntilIdle();
}

void EPD_Display::epdReset() {
    digitalWrite(EPD_RST_PIN, LOW);
    delay(10);
    digitalWrite(EPD_RST_PIN, HIGH);
    delay(10);
}

void EPD_Display::waitUntilIdle() {
    while (digitalRead(EPD_BUSY_PIN) == HIGH) {
        delay(100);
    }
}

void EPD_Display::sendCommand(uint8_t command) {
    digitalWrite(EPD_DC_PIN, LOW);
    digitalWrite(EPD_CS_PIN, LOW);
    SPI.transfer(command);
    digitalWrite(EPD_CS_PIN, HIGH);
}

void EPD_Display::sendData(uint8_t data) {
    digitalWrite(EPD_DC_PIN, HIGH);
    digitalWrite(EPD_CS_PIN, LOW);
    SPI.transfer(data);
    digitalWrite(EPD_CS_PIN, HIGH);
}
