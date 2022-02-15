extern "C"
{
#include <nes/nes.h>
}

#include "hw_config.h"

#include <Arduino_GFX_Library.h>


#define TFT_BRIGHTNESS 180 /* 0 - 255 */

// TTGO T-DISPLAY.
#define TFT_BL 4
Arduino_DataBus *bus = new Arduino_ESP32SPI(16 /* DC */, 5 /* CS */, 18 /* SCK */, 19 /* MOSI */, -1 /* MISO */);
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, 23 /* RST */, 2 /* rotation */, true /* IPS */, 135 /* width */, 240 /* height */, 53 /* col offset 1 */, 40 /* row offset 1 */, 52 /* col offset 2 */, 40 /* row offset 2 */);


static int16_t w, h, frame_x, frame_y, frame_x_offset, frame_width, frame_height, frame_line_pixels;
extern int16_t bg_color;
extern uint16_t myPalette[];

extern void display_begin()
{      
    gfx->begin();
    bg_color = gfx->color565(0, 0, 0);
    gfx->fillScreen(bg_color);
    gfx->setRotation(3); // valori 0,1,2,3 varie orientazioni dello schermo. TTGO ha senso solo 1 e 3

    ledcAttachPin(TFT_BL, 1);     // assign TFT_BL pin to channel 1
    ledcSetup(1, 12000, 8);       // 12 kHz PWM, 8-bit resolution
    ledcWrite(1, TFT_BRIGHTNESS); // brightness 0 - 255
}

extern "C" void display_init()
{
    Serial.println("display_init!");
  
    w = gfx->width();
    h = gfx->height();
    if (w < 480) // assume only 240x240 or 320x240
    {
        if (w > NES_SCREEN_WIDTH)
        {
            frame_x = (w - NES_SCREEN_WIDTH) / 2;
            frame_x_offset = 0;
            frame_width = NES_SCREEN_WIDTH;
            frame_height = NES_SCREEN_HEIGHT;
            frame_line_pixels = frame_width;
        }
        else
        {
            // TTGO.
            frame_x = 0;
            frame_x_offset = 8;
            frame_width = w+16;
            frame_height = NES_SCREEN_HEIGHT;
            frame_line_pixels = frame_width;
        }
        frame_y = (gfx->height() - NES_SCREEN_HEIGHT) / 2;
    }
    else // assume 480x320
    {
        frame_x = 0;
        frame_y = 0;
        frame_x_offset = 8;
        frame_width = w;
        frame_height = h;
        frame_line_pixels = frame_width / 2;
    }
    
    Serial.print("gfx->width:");
    Serial.println(w);
    Serial.print("gfx->height:");
    Serial.println(h);    
}

extern "C" void display_write_frame(const uint8_t *data[])
{    
    gfx->startWrite();
    // TTGO.
    if (w == 240 && h==135){
      gfx->writeAddrWindow(0, 0, frame_width, frame_height);
      for (int32_t i = 0; i < NES_SCREEN_HEIGHT; i++)
      {
        if ((i % 2) == 1)
          gfx->writeIndexedPixels((uint8_t *)(data[i] + frame_x_offset), myPalette, frame_line_pixels);
      }
    }else if (w < 480){            
        gfx->writeAddrWindow(frame_x, frame_y, frame_width, frame_height);
        for (int32_t i = 0; i < NES_SCREEN_HEIGHT; i++)
        {
            gfx->writeIndexedPixels((uint8_t *)(data[i] + frame_x_offset), myPalette, frame_line_pixels);
        }      
    }
    else
    {
        int16_t y = 0;
        for (int16_t i = 10; i < (10 + 214); i++)
        {
            gfx->writeAddrWindow(frame_x, y++, frame_width, 1);
            gfx->writeIndexedPixelsDouble((uint8_t *)(data[i] + 8), myPalette, frame_line_pixels);
            if ((i % 2) == 1)
            {
                y++; // blank line
            }
        }
    }
    gfx->endWrite();       
}

extern "C" void display_clear()
{
    gfx->fillScreen(bg_color);
}
