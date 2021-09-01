/**
 *
 *  HelloWorld.ino
 *  
 *  "Hello World" version for U8x8 API
 *
 *  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
 *
 */

#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif


U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(22,21); //SCL, SDA

// End of constructor list


void setup(void)
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  
}

void loop(void)
{
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,1,"hello OLED!");
  u8x8.refreshDisplay();		// only required for SSD1606/7  
  delay(2000);
}