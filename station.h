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
    Station(const string &name, float aProbability);
    //int getTimeToNextMetro(string direction);
    void setFlow(string flow);
    string getName();
    void receivePeople(Passenger *pasajero);
    string getFlow();
    void showPassengers();
    int getTotalPassengers();
    MetroUnit *getPuertoPlatform();
    MetroUnit *getLimachePlatform();
    void setMetroPlatform(MetroUnit *metro);
    void departureMetro();
    void setPlatformFree(string platform);
    vector<Passenger*> &getAwaitingPeople();
    float getProbability();
private:
    string name;
    vector<Passenger*> AwaitingPeople;
    MetroUnit *PuertoDirectionPlatform;
    MetroUnit *LimacheDirectionPlatform;
    string flow;
    float probability;
};

#endif // STATION_H
