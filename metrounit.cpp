#include "metrounit.h"
#include "passenger.h"
#include "station.h"
#include <algorithm>

extern string nombre_estaciones[20];
extern vector<Station *> Estaciones;
extern int Time_Between_Stations[19];
extern float Probability_to_descend[20];
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

void MetroUnit::occupyMetro() {
    vector <Passenger*> &AwaitingPeople = actual_station->getAwaitingPeople();
    int contador;
    auto it = AwaitingPeople.begin();
    while (it != AwaitingPeople.end() && Occupation.size() < capacity) {
        Passenger *pasajero = *it;
        if (pasajero->getDirection() == actual_direction) {
            Occupation.push_back(*it);
            it = AwaitingPeople.erase(it);
        }
        else {
            ++it;
        }
    }
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
    state = "En transito";
    auto it = std::find_if(Estaciones.begin(), Estaciones.end(),[this](Station *obj)  {
                return obj == actual_station;  // Aquí sí comparas contenido usando tu operador ==
            });
    if (it != Estaciones.end()) {
        int indice = distance(Estaciones.begin(),it);
        if (actual_direction == "Puerto") {
            time_to_arrive = Time_Between_Stations[indice-1];
        }
        else if (actual_direction == "Limache") {
            time_to_arrive = Time_Between_Stations[indice];
        }
    }
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

void MetroUnit::descendPeople() {
    auto it = std::find_if(Estaciones.begin(), Estaciones.end(),[this](Station *obj)  {
                return obj == actual_station;  // Aquí sí comparas contenido usando tu operador ==
            });
    if (it != Estaciones.end()) {
        int indice = distance(Estaciones.begin(),it);
        int Ocuppation_size = Occupation.size();
        for (int contador = 0; contador < Ocuppation_size;contador++) {
            Passenger *pasajero = Occupation[contador];
            float random = (rand()%100+1)/100.0;
            if (random < Probability_to_descend[indice]) {
                delete pasajero;
                Occupation.erase(Occupation.begin()+contador);
                contador--;
                Ocuppation_size--;
            }

        }
    }

}