#ifndef METROUNIT_H
#define METROUNIT_H

#include <vector>
#include <string>
#include "station.h"

class MetroUnit
{
public:
    MetroUnit(int capacity);
    int getCapacity();
    Station getActualStation();
    string getDirection();
    void moveToNextStation();
    void setOn(string direction);

private:
    int capacity;
    string state:
    vector<Passenger> ocupation;
    Station actual_station;
    string actual_direction;
};

#endif // METROUNIT_H
