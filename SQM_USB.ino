#include "SQM_TSL2591.h"
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define SEALEVELPRESSURE_HPA (1013.25)

#define PIN_T_SENSOR 10

SQM_TSL2591 sqm = SQM_TSL2591(2591);

void readSQM(void);

String PROTOCOL_NUMBER = "00000002";
String MODEL_NUMBER = "00000003";
String FEATURE_NUMBER = "00000001";
String SERIAL_NUMBER = "00000022";
String info;

String response;
bool new_data;

String temp_string;
float temp;

String c;

bool LED_ON = HIGH;
bool LED_OFF = LOW;

void setup_tsl() {
  pinMode(13, OUTPUT);
  if (sqm.begin()) {
    sqm.config.gain = TSL2591_GAIN_LOW;
    sqm.config.time = TSL2591_INTEGRATIONTIME_200MS;
    sqm.configSensor();
    sqm.setCalibrationOffset(0.0);
    sqm.verbose = false;
  } else {
    Serial.println("SQM sensor not found");
  }
  delay(1000);
}

// Setup temperature sensor.  This example uses the DHT22 sensor.
DHT dht(PIN_T_SENSOR, DHT22);
void setup_temperature() {
  bool status;
  // default settings
  dht.begin();
}

float get_temperature() { return dht.readTemperature(); }


void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LED_OFF);

  setup_temperature();

  setup_tsl(); 
}


void loop() {

  response = "";
  new_data = false;

while (Serial.available() > 0) {
 
    temp = dht.readTemperature();
    sqm.takeReading();
//    digitalWrite(LED_BUILTIN, LED_ON);

    c = Serial.readString();

    if (c[1] == 'x') {

      if (c[0] == 'i') {
        response = String("i," + PROTOCOL_NUMBER + "," + MODEL_NUMBER +
                        "," + FEATURE_NUMBER + "," + SERIAL_NUMBER);
        new_data = true;
      }
      
      if (c[0] == 'r' || c[0] == 'R') {
        if (sqm.mpsas < 0.) { //not an expected condition
          response = "r,";
        } 

        else if (sqm.mpsas < 10.) {
          response = "r, 0"; //space for no negative plus a zero for the 10's place
        }
        
        else  {
          response = "r, ";
        }

        if (temp < 10.) {
          temp_string = ","; 
        }

        else if(temp < 0.) {
          temp_string = ",-0";
          temp = abs(temp);
        }
       
        else {
          temp_string = ", 0"; //need 0 for padding -- logic breaks down at 100C
        }

      temp_string = String(temp_string + String(temp, 1) + "C");

      response = String(response + String(sqm.mpsas, 2) +
                 "m,0000005915Hz,0000000000c,0000000.000s" + temp_string);
      new_data = true;
    }
    }

    if (new_data) {
      Serial.println(response);
      new_data = false;
    }
    
//    digitalWrite(LED_BUILTIN, LED_OFF);


}
} // end loop
