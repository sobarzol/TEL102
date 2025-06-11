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
    Station getActualStation();
    string getDirection();
    void moveToNextStation();
    void setOn(string direction);
    void ocuppyMetro(Passenger *pasajero);
    int time_in_transit;
    string state;
private:
    int capacity;
    vector<Passenger*> Ocupation;
    Station *actual_station;
    string actual_direction;

};

#endif // METROUNIT_H
