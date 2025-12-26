/**
 * @file ST7735.hpp
 * @author your name (you@domain.com)
 * @brief driver for ST7735 graphics ic (only supports write cmds)
 * @version 0.1
 * @date 2025-12-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <stdint.h>


class ST7735{
private:
    const uint16_t screenWidth;
    const uint16_t screenHeight;

    const uint16_t pinA0;
    const uint16_t pinCS;

    enum commands{
    };

    /**
     * @brief function to send a command byte to the display
     * 
     * @param cmd the command to be send
     */
    void sendCMDByte(commands cmd);

    /**
     * @brief function to send a data byte to the display
     * 
     * @param data the byte to send
     */
    void sendDataByte(uint8_t data);

    void writePixelData();

    //required callbacks
    void (*transmitByte)(uint8_t data);
    void (*writePin)(uint8_t pin, bool val);

public:
    ST7735();
    ST7735(ST7735 &other) = delete;
    ST7735(ST7735 &&other) = delete;

    struct RGB{
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t intensity;
    };
    
    //API
    void drawPixel(uint16_t x, uint16_t y, RGB color);
    void reset();
    void on();
    void off();
    void inversion(bool enable);
};
