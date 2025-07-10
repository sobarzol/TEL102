#include "station.h"
#include <vector>
#include "passenger.h"
#include "metrounit.h"
#include <iostream>
using namespace std;



Station::Station(const string &name, float aProbability) : name(name), probability(aProbability){
    flow = "muy bajo";
    PuertoDirectionPlatform = NULL;     //constructor con nombre y probabilidad de que un pasajero descienda en la estacion
    LimacheDirectionPlatform = NULL;    //ambos andenes comienzan vacios
}


void Station::setFlow(string flow){ //cambia el flujo de la estacion
    this->flow = flow;
}

void Station::receivePeople(Passenger *pasajero){   //un pasajero entra a la estacion
    AwaitingPeople.push_back(pasajero);
}

string Station::getFlow() { //retorna el flujo
    return flow;
}

string Station::getName() { //retorna el nombre
    return name;
}

void Station::showPassengers() {        //metodo para debuggear, muestra por consola los ids de los pasajeros de la estacion
    for (Passenger *passenger: AwaitingPeople) {
        cout << passenger->getId() << endl;
    }
}

int Station::getTotalPassengers() { //retorna la cantidad de gente esperando
    return AwaitingPeople.size();
}

MetroUnit *Station::getPuertoPlatform() {   //retorna la unidad de metro ubicada en el anden a puerto
    return PuertoDirectionPlatform;
}

MetroUnit *Station::getLimachePlatform() {  //retorna la unidad de metro ubicada en el anden a limache
    return LimacheDirectionPlatform;
}

void Station::setMetroPlatform(MetroUnit *metro) {  //ubica a un metro en el anden dependiendo de la direccion
    if (metro->getDirection() == "Puerto") {
        PuertoDirectionPlatform = metro;
    }
    else if (metro->getDirection() == "Limache") {
        LimacheDirectionPlatform = metro;
    }
}

void Station::departureMetro() {        //hace que el metro que esperava gente salga de la estacion
    if (PuertoDirectionPlatform != NULL) {
        PuertoDirectionPlatform->moveToNextStation();
        PuertoDirectionPlatform = NULL;
    }
    if (LimacheDirectionPlatform != NULL) {
        LimacheDirectionPlatform->moveToNextStation();
        LimacheDirectionPlatform = NULL;
    }
}

void Station::setPlatformFree(string platform) {    //libera la plataforma correspondiente a la direccion.
    if (platform == "Puerto") {
        PuertoDirectionPlatform = NULL;
    }
    else if (platform == "Limache") {
        LimacheDirectionPlatform = NULL;
    }
}

vector<Passenger*> &Station::getAwaitingPeople() {  //retorna el vector de gente esperando
    return AwaitingPeople;
}

int Station::getLimachePassengers(){    //cuenta la cantidad de gente en el anden a limache
    int sum = 0;
    for(Passenger* passenger: AwaitingPeople){
        if(passenger->getDirection() == "Limache")
            sum++;
    }
    return sum;
}

int Station::getPuertoPassengers(){ //cuenta la cantidad de gente en el anden a puerto
    int sum = 0;
    for(Passenger* passenger: AwaitingPeople){
        if(passenger->getDirection() == "Puerto")
            sum++;
    }
    return sum;
}
