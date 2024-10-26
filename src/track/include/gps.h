#ifndef GPS_H
#define GPS_H

#define GPS_RX 16
#define GPS_TX 17
#define GPSBaud 9600

struct Location {
    float lat;
    float lng;
};

float calHarvesineDistance (Location setLoc, Location curLoc);

#endif