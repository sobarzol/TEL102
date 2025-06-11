#include "clases.h"
#include <algorithm>
extern vector<MetroUnit*> Metros;
extern vector<Station*> Estaciones;

Passenger::Passenger() {
    actual_passenger_id++;
    passenger_id = actual_passenger_id;
    direction = this->generateDirection();
    total_passengers++;
}

Passenger::~Passenger() {
    total_passengers--;
}

string Passenger::generateDirection(){
    srand(time(NULL));
    int a = rand()%2;
    if (a == 0) return "Limache";
    else return "Puerto";
}

Schedule::Schedule() {}

bool Schedule::operator==(const Schedule& otra) const {
    return (static_cast<int>(Day) == static_cast<int>(otra.Day)) &&
           (Hour == otra.Hour) && (Minute == otra.Minute);
}

Station::Station(){
}

Station::Station(string name) {
    this->name = name;
    flow = "bajo";
}

int Station::getTimeToNextMetro(string direction){
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

void Station::setFlow(string flow){
    this->flow = flow;
}

void Station::receivePeople(Passenger *pasajero){
    AwaitingPeople.push_back(pasajero);
}

TimeController::TimeController() {}

void TimeController::moveTimeForward(){
    Passenger *pasajero;

}
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

