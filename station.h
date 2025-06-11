#ifndef STATION_H
#define STATION_H

#include <vector>
#include <string>


class Station
{
public:
    static vector<Station> Stations;
    Station(string name);
    int getTimeToNextMetro(string direction);
    void getPeopleIntoMetro();
    void setFlow(string flow);

private:
    string name;
    MetroUnit PuertoDirectionPlatform;
    MetroUnit LimacheDirectionPlatform;
    string flow;
    vector<Passenger> AwaitingPeople;
};

#endif // STATION_H
