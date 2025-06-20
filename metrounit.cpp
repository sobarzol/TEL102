#include "metrounit.h"
#include "passenger.h"
#include "station.h"
extern string nombre_estaciones[20];
extern vector<Station *> Estaciones;
MetroUnit::MetroUnit(){
    capacity = 392;
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
    actual_station = NULL;
    Occupation = vector<Passenger*>();
    time_in_transit = 0;
}

MetroUnit::MetroUnit(int capacity, Station *initial_station){
    this->capacity = capacity;
    actual_station = initial_station;
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
    time_in_transit = 0;
}

void MetroUnit::ocuppyMetro(Passenger *pasajero){
    Occupation.push_back(pasajero);
}

void MetroUnit::setOn(string direction){
    actual_direction = direction;
    state = "Esperando gente";
}

string MetroUnit::getDirection(){
    return this->actual_direction;
}

Station *MetroUnit::getActualStation(){
    return actual_station;
}

int MetroUnit::getCapacity() {
    return capacity;
}

void MetroUnit::moveToNextStation() {
    //actual_station = ;
}

string MetroUnit::getState() {
    return state;
}

int MetroUnit::getOccupation() {
    return Occupation.size();
}