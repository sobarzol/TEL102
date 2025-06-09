#ifndef PASSENGER_H
#define PASSENGER_H

#include <vector>
#include <string>

class Passenger
{
public:
    Passenger();
    ~Passenger();
    void joinToStation(Station station);
    void leaveSystem();
    static int actual_passenger_id;
private:
    int passenger_id;
    string direction;
    int total_passengers;
};

#endif // PASSENGER_H
