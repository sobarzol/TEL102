#include "metrounit.h"
#include "passenger.h"
#include "station.h"
#include <algorithm>
#include "simulador_metro.h"


extern int Time_Between_Stations[19];
extern float Probability_to_descend[20];
MetroUnit::MetroUnit(){     //constructor por defecto
    capacity = 392;
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
    actual_station = NULL;
    Occupation = vector<Passenger*>();
    time_to_arrive = 0;
}

MetroUnit::MetroUnit(int capacity, Station *initial_station){   //constructor con capacidad y estacion inicial
    this->capacity = capacity;
    actual_station = initial_station;
    state = "Fuera de servicio";        //La unidad de metro al crearse se crea fuera de servicio.
    actual_direction = "Sin direccion";
    time_to_arrive = 0;
}

void MetroUnit::occupyMetro() {     //Los pasajeros que estan en la estacion actual asciendan al metro
    vector <Passenger*> &AwaitingPeople = actual_station->getAwaitingPeople();
    auto it = AwaitingPeople.begin();
    while (it != AwaitingPeople.end() && int(Occupation.size()) < capacity) {   //Solo si no supera la capacidad del tren.
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



void MetroUnit::setOn(string direction){    //enciende el metro en cierta direccion
    actual_direction = direction;
    state = "Esperando gente";
}

void MetroUnit::setOff() {  //apaga el metro y lo deja fuera de servicio
    state = "Fuera de servicio";
    actual_direction = "Sin direccion";
    Occupation.clear(); //libera el vector de ocupacion
}

string MetroUnit::getDirection(){   //retorna la direccion
    return this->actual_direction;
}

Station *MetroUnit::getActualStation(){ //retorna la estacion actual
    return actual_station;
}

int MetroUnit::getCapacity() {  //retorna la capacidad
    return capacity;
}

void MetroUnit::moveToNextStation() {   //metro abandona la estacion actual
    state = "En transito";  //se cambia a en transito el estado
    auto it = std::find_if(Simulador_Metro::Estaciones.begin(), Simulador_Metro::Estaciones.end(),[this](Station *obj)  {
        return obj == actual_station;  // Aquí sí comparas contenido usando tu operador ==
    });
    if (it != Simulador_Metro::Estaciones.end()) {
        int indice = distance(Simulador_Metro::Estaciones.begin(),it);
        if (actual_direction == "Puerto") {
            time_to_arrive = Time_Between_Stations[indice-1];   //obtiene el tiempo que se demora en llegar a la siguiente estacion desde un arreglo de informacion
        }
        else if (actual_direction == "Limache") {
            time_to_arrive = Time_Between_Stations[indice];
        }
    }
}

string MetroUnit::getState() {  //retorna el estado
    return state;
}

int MetroUnit::getOccupation() {
    return Occupation.size();   //retorna la cantidad de personas dentro del metro
}

void MetroUnit::reduceTimeToArrive() {      //reduce el tiempo para llegar a la siguiente estacion.
    time_to_arrive--;
    if (time_to_arrive == 0) {  //si llega a cero cambia el estado a esperando gente y se ubica en el anden de la estacion a la que llego.
        state = "Esperando gente";
        auto it = std::find_if(Simulador_Metro::Estaciones.begin(), Simulador_Metro::Estaciones.end(),[this](Station *obj)  {
            return obj == actual_station;   //encuentra a que estacion pertenece por indice en el vector estacion
        });
        if (it != Simulador_Metro::Estaciones.end()) {
            int indice = distance(Simulador_Metro::Estaciones.begin(),it);
            if (actual_direction == "Puerto") {
                actual_station = Simulador_Metro::Estaciones[indice-1];
                Simulador_Metro::Estaciones[indice-1]->setMetroPlatform(this);  //resta si esta en direccion puerto
            }
            else if (actual_direction == "Limache") {
                actual_station = Simulador_Metro::Estaciones[indice+1];
                Simulador_Metro::Estaciones[indice+1]->setMetroPlatform(this);  //suma si esta en direccion limache
            }
        }
    }

}

void MetroUnit::descendPeople() {   //metodo que baja la gente del metro
    auto it = std::find_if(Simulador_Metro::Estaciones.begin(), Simulador_Metro::Estaciones.end(),[this](Station *obj)  {
        return obj == actual_station;  // Aquí sí comparas contenido usando tu operador ==
    });
    if (it != Simulador_Metro::Estaciones.end()) {
        int indice = distance(Simulador_Metro::Estaciones.begin(),it);
        int Ocuppation_size = Occupation.size();
        for (int contador = 0; contador < Ocuppation_size;contador++) {
            Passenger *pasajero = Occupation[contador];
            float random = (rand()%100+1)/100.0; //se utiliza un numero aleatorio y la probabilidad de descender en cada estacion
            if (random < Probability_to_descend[indice]) {
                delete pasajero;    //se libera la memoria
                Occupation.erase(Occupation.begin()+contador);  //se libera el espacio en el vector
                contador--; //al eliminar un elemento se reduce el contador y el tamano del vector.
                Ocuppation_size--;
            }

        }
    }

}

int MetroUnit::getTimeToArrive() {  //retorna el tiempo para llegar a la siguiente estacion
    return time_to_arrive;
}
