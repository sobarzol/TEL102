#ifndef PASSENGER_H
#define PASSENGER_H

#include <vector>
#include <string>
#include "time.h"
using namespace std;

class Station;

class Passenger
{
public:
    Passenger();
    ~Passenger();
    int getId();
    string getDirection();
    //static int total_passengers;
    //void joinToStation(Station *station);
private:
    int passenger_id;
    static int next_passenger_id;
    string direction;
};

#endif // PASSENGER_H
