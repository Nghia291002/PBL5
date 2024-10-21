#include <Arduino.h>
#include <TinyGPS++.h>
#include "gps.h"
// #include "sim.h"

//GPIO define
const int setBtn = 5;  // GPIO5 (D5)

Location setLocation, currentLocation;
// volatile bool BtnPress = false;  // To track the button press
volatile bool tracking = false;  // To track the tracking state


//define variable handle btn function
volatile unsigned long pressTime = 0;
void IRAM_ATTR handleBtnPress() {
  if (digitalRead(setBtn) == LOW) {
    pressTime = millis();
  } else {
    //hold for 3 seconds to set location
    //hold for 7 seconds to toggle tracking
    if (millis() - pressTime >= 7000) {
      tracking = !tracking;
      Serial.print("Tracking: ");
      Serial.println(tracking);
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

void setup() {
  Serial.begin(115200);

  currentLocation.lat = 0.0;
  currentLocation.lng = 0.0;

  pinMode(setBtn, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(setBtn), handleBtnPress, CHANGE);
}

void loop() {
  float burglarizeDistance = 0;

  if (tracking) {
    Serial.println("Tracking...");
    burglarizeDistance = calHarvesineDistance(setLocation, currentLocation);

    if (burglarizeDistance > 20) {
      //emergency warning
    } else if (burglarizeDistance > 5) {
      //soft warning
    }
    
  }
  else {
    Serial.println("Not tracking...");
  }
  delay(1000);
}
