#ifndef CLASES_H
#define CLASES_H

#include <vector>
#include <string>
#include "time.h"

using namespace std;
class Passenger;
class Station;
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
    int time_in_transit;
private:
    int capacity;
    string state;
    vector<Passenger*> Ocupation;
    Station *actual_station;
    string actual_direction;
};


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

enum class Dia
{
    Lunes, Martes, Miercoles, Jueves, Viernes, Sabado, Domingo
};

class Schedule
{
public:
    Schedule();
    Schedule(Dia aDay, int aHour, int aMinute);
    Dia Day;
    int Hour;
    int Minute;
    bool operator ==(const Schedule& otra) const;
};

class TimeController
{
public:
    TimeController();
    void createPassenger();
    void moveTimeForward();
    void setMetroOn(MetroUnit *metro, Station *estacion_de_inicio);
    Schedule actual_schedule;
};

#endif // CLASES_H
