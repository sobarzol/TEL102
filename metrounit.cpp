#include "metrounit.h"
#include "passenger.h"
#include "station.h"
#include <algorithm>

extern string nombre_estaciones[20];
extern vector<Station *> Estaciones;
MetroUnit::MetroUnit(){
    capacity = 392;
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
    actual_station = NULL;
    Occupation = vector<Passenger*>();
}

MetroUnit::MetroUnit(int capacity, Station *initial_station){
    this->capacity = capacity;
    actual_station = initial_station;
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
}

void MetroUnit::ocuppyMetro(Passenger *pasajero){
    Occupation.push_back(pasajero);
}

void MetroUnit::setOn(string direction){
    actual_direction = direction;
    state = "Esperando gente";
}

void MetroUnit::setOff() {
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
    Occupation.clear();
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
    time_to_arrive = 1;
    state = "En transito";
}

string MetroUnit::getState() {
    return state;
}

int MetroUnit::getOccupation() {
    return Occupation.size();
}

void MetroUnit::reduceTimeToArrive() {
    time_to_arrive--;
    if (time_to_arrive == 0) {
        state = "Esperando gente";
        auto it = std::find_if(Estaciones.begin(), Estaciones.end(),[this](Station *obj)  {
                return obj == actual_station;  // Aquí sí comparas contenido usando tu operador ==
            });
        if (it != Estaciones.end()) {
            int indice = distance(Estaciones.begin(),it);
            if (actual_direction == "Puerto") {
                actual_station = Estaciones[indice-1];
                Estaciones[indice-1]->setMetroPlatform(this);
            }
            else if (actual_direction == "Limache") {
                actual_station = Estaciones[indice+1];
                Estaciones[indice+1]->setMetroPlatform(this);
            }
        }
    }

}