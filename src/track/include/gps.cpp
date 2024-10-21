#include <math.h>
#include "gps.h"
#define PI 3.14159265358979323846

float calHarvesineDistance (Location setLoc, Location curLoc) {
    float lat1 = setLoc.lat;
    float lon1 = setLoc.lng;
    float lat2 = curLoc.lat;
    float lon2 = curLoc.lng;
    float dLat = (lat2 - lat1) * PI / 180.0;
    float dLon = (lon2 - lon1) * PI / 180.0;
    lat1 = (lat1) * PI / 180.0;
    lat2 = (lat2) * PI / 180.0;
    float a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    float rad = 6371;
    float c = 2 * asin(sqrt(a));
    return rad * c;
} 

