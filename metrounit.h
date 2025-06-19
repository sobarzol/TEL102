#ifndef METROUNIT_H
#define METROUNIT_H

#include <vector>
#include <string>
using namespace std;

class Station;
class Passenger;

class MetroUnit
{
public:
    MetroUnit();
    MetroUnit(int capacity, Station *initial_station);
    int getCapacity();
    Station *getActualStation();
    string getDirection();
    void moveToNextStation();
    void setOn(string direction);
    void ocuppyMetro(Passenger *pasajero);
    string getState();
private:
    int capacity;
    string state;
    vector<Passenger*> Ocupation;
    Station *actual_station;
    string actual_direction;
};

#endif // METROUNIT_H
