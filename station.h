#ifndef STATION_H
#define STATION_H

#include <vector>
#include <string>
using namespace std;

class MetroUnit;
class Passenger;

class Station
{
public:
    Station();
    static int Time_Between_Stations[19];
    Station(string name);
    int getTimeToNextMetro(string direction);
    void setFlow(string flow);
    vector<Passenger*> AwaitingPeople;
    void receivePeople(Passenger *pasajero);

private:
    string name;
    MetroUnit *PuertoDirectionPlatform;
    MetroUnit *LimacheDirectionPlatform;
    string flow;

};

#endif // STATION_H
