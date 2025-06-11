#include "station.h"
#include <algorithm>
extern vector<MetroUnit*> Metros;
extern vector<Station*> Estaciones;

Station::Station(){
}

Station::Station(string name) {
    this->name = name;
    flow = "bajo";
}

int Station::getTimeToNextMetro(string direction){
    MetroUnit *siguiente = NULL;
    auto it = find(Estaciones.begin(), Estaciones.end(), this);
    int indice = distance(Estaciones.begin(),it);

    for(MetroUnit *metro : Metros){
    }
}

void Station::setFlow(string flow){

}
