
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0,22,21); //clock, data

#define U8LOG_WIDTH 22
#define U8LOG_HEIGHT 7
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];
U8G2LOG u8g2log;


void setup(void) {
  Serial.begin(115200);				// Start reading from Serial communication interface

  u8g2.begin();  
  u8g2.setFont(u8g2_font_6x10_tr);	// set the font for the terminal window
  u8g2log.begin(u8g2, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  u8g2log.setLineHeightOffset(0);	// set extra space between lines in pixel, this can be negative
  u8g2log.setRedrawMode(1);		// 0: Update screen with newline, 1: Update screen for every char  
}

void loop(void) {
  char c;
  while (Serial.available() > 0) {
    c = Serial.read();			// read from Serial Monitor
    u8g2log.print(c);       // print to display
    Serial.print(c);        // and print back to monitor
  }
}