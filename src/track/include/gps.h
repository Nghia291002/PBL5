#ifndef GPS_H
#define GPS_H

struct Location {
    float lat;
    float lng;
};

float calHarvesineDistance(Location loc1, Location loc2);

#endif