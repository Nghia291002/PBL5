#include "gps.h"
#include "sim.h"

#include <Arduino.h>
#include <TinyGPS++.h>
#include <TinyGsmClient.h>


//GPIO define
const int setBtn = 5;  // GPIO5 (D5)

TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
Location setLocation, currentLocation;

HardwareSerial simSerial(1);
TinyGsm modem(simSerial);

volatile bool tracking = false;  // To track the tracking state
float theftDistance = 0;

//define variable handle btn function
volatile unsigned long pressTime = 0;
void IRAM_ATTR handleBtnPress() {
  if (digitalRead(setBtn) == LOW) {
    pressTime = millis();
  } else {
    //hold for 7 seconds to toggle tracking
    if (millis() - pressTime >= 7000) {
      tracking = !tracking;
      Serial.print("Tracking: ");
      Serial.println(tracking);
      //hold for 3 seconds to set location
    } else if (millis() - pressTime >= 3000) {
      setLocation = currentLocation;
      Serial.println("Location set: ");
      Serial.print("Lat: ");
      Serial.println(setLocation.lat, 6);
      Serial.print("Lng: ");
      Serial.println(setLocation.lng, 6);
    } else {
      //do nothing
    }
  }
}

void setupSim() {
  pinMode(SIM_PWRKEY, OUTPUT);
  pinMode(SIM_PWR, OUTPUT);
  digitalWrite(SIM_PWR, HIGH);
  digitalWrite(SIM_PWRKEY, HIGH);
  delay(1000);
  digitalWrite(SIM_PWRKEY, LOW);
  delay(1000);
  digitalWrite(SIM_PWRKEY, HIGH);
  delay(2000);
  Serial.println("SIM ready");
}

void setup() {
  Serial.begin(115200);

  setupSim();
  simSerial.begin(SIM_BAUD, SERIAL_8N1, SIM_RX, SIM_TX);

  currentLocation.lat = 0.0;
  currentLocation.lng = 0.0;
  gpsSerial.begin(GPSBaud, SERIAL_8N1, GPS_RX, GPS_TX);
  
  pinMode(setBtn, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(setBtn), handleBtnPress, CHANGE);
}

void loop() {

  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        currentLocation.lat = gps.location.lat();
        currentLocation.lng = gps.location.lng();
      }
    }
    if (tracking) {
      Serial.println("Tracking...");
      theftDistance = calHarvesineDistance(setLocation, currentLocation);

      if (theftDistance > 50) {
        //emergency warning
        //call sim function
      } else if (theftDistance > 10) {
        //soft warning
        //call sim function
      }
    }
    else {
      Serial.println("Not tracking...");
    }
  }

  delay(1000);
}
