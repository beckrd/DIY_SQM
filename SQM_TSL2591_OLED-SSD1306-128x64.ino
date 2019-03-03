/*
  SQM using TSL2591 sensor as a Sky Quality Meter
  and 128x64 OLED as display

  Requires Arduino MEGA or MEGA 2560 because of size of code 
  plus buffer for display
  

  This code is in the public domain and is based on 
  Gabe Shaughnessy's example from Oct 21 2017

  RD Beck
  Jan 2019
 */

// setup for OLED1
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


// setup for TSL2591
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "SQM_TSL2591.h"

SQM_TSL2591 sqm = SQM_TSL2591(2591);
void readSQM(void);



void setup() {
  Serial.begin(9600);

  
  // pinMode(13, OUTPUT);
  if (sqm.begin()) {

    Serial.println("Found SQM (TSL) sensor");
    sqm.config.gain = TSL2591_GAIN_LOW;
    sqm.config.time = TSL2591_INTEGRATIONTIME_200MS;
    sqm.configSensor();
    sqm.showConfig();
    sqm.setCalibrationOffset(0.0);
  } else{
    Serial.println("SQM sensor not found");
 }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

// add a logo or other text for initialization
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(40,6);
  display.print("DIY");
  display.setCursor(40,34);
  display.print("SQM");  
  display.display();
  delay(1000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

}

void loop() {
 // digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)

  sqm.takeReading();
  // digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)

/*
//write to serial monitor for debugging purposes
  Serial.print("full:   "); Serial.println(sqm.full);
  Serial.print("ir:     "); Serial.println(sqm.ir);
  Serial.print("vis:    "); Serial.println(sqm.vis);
  Serial.print("mpsas:  "); Serial.print(sqm.mpsas);
  Serial.print(" +/- "); Serial.println(sqm.dmpsas);
*/

  Serial.println("======================================");

// write to OLED
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("   Mag/Arc-Sec");
  display.setTextSize(3);
  display.setCursor(0, 24);
  display.print(" ");
  display.print(sqm.mpsas);
  display.setTextSize(1);
  display.setCursor(0,48);
  display.print("  ");
  display.setCursor(0,56);
  display.print("   +/- ");
  display.print(sqm.dmpsas);
  display.display();


  delay(2000);
}
