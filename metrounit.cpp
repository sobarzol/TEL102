#include "metrounit.h"
#include "passenger.h"
#include "station.h"

MetroUnit::MetroUnit(){
    capacity = 340;
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
}

MetroUnit::MetroUnit(int capacity, Station *initial_station){
    this->capacity = capacity;
    actual_station = initial_station;
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
}

void MetroUnit::ocuppyMetro(Passenger *pasajero){
    Ocupation.push_back(pasajero);
}

void MetroUnit::setOn(string direction){
    actual_direction = direction;
    state = "Esperando gente";
}

string MetroUnit::getDirection(){
    return actual_direction;
}

Station *MetroUnit::getActualStation(){
    return actual_station;
}

