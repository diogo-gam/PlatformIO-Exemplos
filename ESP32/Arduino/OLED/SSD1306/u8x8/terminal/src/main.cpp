/**
 *  Terminal.ino
 *  
 *  Demo for U8log
 *
 */

#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define OUTPUT_PORT Serial

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(22,21); //SCL, SDA

// End of constructor list


// setup the terminal (U8X8LOG) and connect to u8g2 for automatic refresh of the display
// The size (width * height) depends on the display 

#define U8LOG_WIDTH 16
#define U8LOG_HEIGHT 8
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];
U8X8LOG u8x8log;



void setup(void)
{
  /* U8g2 Project: SSD1306 Test Board */
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //digitalWrite(10, 0);
  //digitalWrite(9, 0);		
  
  /* U8g2 Project: KS0108 Test Board */
  //pinMode(16, OUTPUT);
  //digitalWrite(16, 0);	
  
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  
  u8x8log.begin(u8x8, U8LOG_WIDTH, U8LOG_HEIGHT, u8log_buffer);
  u8x8log.setRedrawMode(1);		// 0: Update screen with newline, 1: Update screen for every char  
  
}

unsigned long t = 0;

// print the output of millis() to the terminal every second
void loop(void) {
  if ( t < millis() ) {
    t = millis() + 15000;			// every 15 seconds
    u8x8log.print("\f");			// \f = form feed: clear the screen
  }
  u8x8log.print("millis=");
  u8x8log.print(millis());
  u8x8log.print("\n");
  delay(500);
}