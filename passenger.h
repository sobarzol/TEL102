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
    static int actual_passenger_id;
    static int total_passengers;
    string generateDirection();
private:
    int passenger_id;
    string direction;
};

#endif // PASSENGER_H
