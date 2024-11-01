#ifndef EPD_DISPLAY_H
#define EPD_DISPLAY_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>

// 墨水屏配置
#define EPD_WIDTH 152
#define EPD_HEIGHT 152

#define EPD_CS_PIN 15
#define EPD_DC_PIN 7
#define EPD_RST_PIN 6
#define EPD_BUSY_PIN 16
#define EPD_SCK_PIN 4
#define EPD_MOSI_PIN 5

class EPD_Display : public Adafruit_GFX {
public:
    EPD_Display(int16_t w, int16_t h);
    ~EPD_Display();

    void begin();
    void drawPixel(int16_t x, int16_t y, uint16_t color = true) override;
    void clearScreen();
    void updateDisplay();
    void UpdateAndclearDisplay();
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color = true);
    void drawBox(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color = true);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color = true);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color = true);
    void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, uint16_t color = true);
    void drawRoundedButton(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color = true);
    void displaytest1();
    void displaytest2();

private:
    uint8_t* buffer;
    void epdInit();
    void epdReset();
    void waitUntilIdle();
    void sendCommand(uint8_t command);
    void sendData(uint8_t data);
};

#endif
