#include "station.h"
#include <vector>
#include "passenger.h"
#include "metrounit.h"
#include <iostream>
using namespace std;
extern vector<MetroUnit*> Metros;
extern vector<Station*> Estaciones;


Station::Station(const string &name) : name(name) {
    flow = "muy bajo";
}

/*int Station::getTimeToNextMetro(string direction){
    MetroUnit *siguiente = NULL;
    int distancia_min = 100;
    auto it = find(Estaciones.begin(), Estaciones.end(), this);
    int indice = distance(Estaciones.begin(),it);

    for(MetroUnit *metro : Metros){
        if(metro->getDirection()==direction){
            if(direction == "Puerto"){
                for(int j = indice; j < 20; j++){
                    if(metro->getActualStation() == Estaciones[j]){
                        if(distancia_min > j-indice){
                            distancia_min = j-indice;
                            siguiente = metro;
                        }
                        else if(distancia_min == j-indice){
                            siguiente = siguiente->time_in_transit > metro->time_in_transit ? siguiente : metro;
                        }
                    }
                }
            }
            else{
                for(int j = indice; j > 0; j--){
                    if(metro->getActualStation() == Estaciones[j]){
                        if(distancia_min > indice-j){
                            distancia_min = indice-j;
                            siguiente = metro;
                        }
                        else if(distancia_min == indice-j){
                            siguiente = siguiente->time_in_transit > metro->time_in_transit ? siguiente : metro;
                        }
                    }
                }

            }
        }
    }
}
*/
void Station::setFlow(string flow){
    this->flow = flow;
}

void Station::receivePeople(Passenger *pasajero){
    AwaitingPeople.push_back(pasajero);
}

string Station::getFlow() {
    return flow;
}

string Station::getName() {
    return name;
}

void Station::showPassengers() {
    for (Passenger *passenger: AwaitingPeople) {
        cout << passenger->getId() << endl;
    }
}

int Station::getTotalPassengers() {
    return AwaitingPeople.size();
}

MetroUnit *Station::getPuertoPlatform() {
    return PuertoDirectionPlatform;
}

MetroUnit *Station::getLimachePlatform() {
    return LimacheDirectionPlatform;
}

void Station::setMetroPlatform(MetroUnit *metro) {
    if (metro->getDirection() == "Puerto") {
        PuertoDirectionPlatform = metro;
    }
    else if (metro->getDirection() == "Limache") {
        LimacheDirectionPlatform = metro;
    }
}

void Station::departureMetro() {
    if (PuertoDirectionPlatform != NULL) {
        PuertoDirectionPlatform->moveToNextStation();
        PuertoDirectionPlatform = NULL;
    }
    if (LimacheDirectionPlatform != NULL) {
        LimacheDirectionPlatform->moveToNextStation();
        LimacheDirectionPlatform = NULL;
    }
}

void Station::setPlatformFree(string platform) {
    if (platform == "Puerto") {
        PuertoDirectionPlatform = NULL;
    }
    else if (platform == "Limache") {
        LimacheDirectionPlatform = NULL;
    }
}