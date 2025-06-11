#include <iostream>
#include "metrounit.h"
#include "passenger.h"
#include "station.h"
#include "timecontroller.h"
#include "dia.h"


using namespace std;

MetroUnit *encontrarMetroDisponible(vector<MetroUnit*>metros, int largo, Station *estacion);
int Station::Time_Between_Stations[19] = {2, 2, 2, 3, 5, 3, 1, 1, 1, 3, 13, 3, 3, 3, 2, 2, 2, 3, 12};
string nombre_estaciones[20] = {"Puerto", "Bellavista", "Francia", "Barón", "Portales", "Recreo", "Miramar",
                                "Viña del Mar", "Hospital", "Chorrillos", "El Salto", "Quilpué", "El Sol", "El Belloto",
                                "Las Américas", "La Concepción", "Villa Alemana", "Sargento Aldea", "Peñablanca", "Limache"};

vector<MetroUnit*> Metros;
vector<Station *>Estaciones;
vector<Schedule*> Horarios;
int main()
{
    for(int i = 0; i < 35;i++){
        Metros.push_back(new MetroUnit(340,i%2 == 0 ? Estaciones[0]:Estaciones[19]));
    }


    for(int i = 0; i < 20; i++){
        Estaciones.push_back(new Station(nombre_estaciones[i]));
    }
    //tomamos la decision de tirar metros cada 15 min
    for(int i = 0; i < 7; i++){
        for  (int j = 6; j < 24; j++){
            for (int k = 0; k < 4; k++){

                Horarios.push_back(new Schedule(static_cast<Dia>(i),j,k*15));
            }
        }
    }
    TimeController Time;//se va a inicializar en Lunes 5:45
    int contador_schedule = 0;
    while (static_cast<int>(Time.actual_schedule.Day) < static_cast<int>(Dia::Domingo) && (Time.actual_schedule.Hour < 24) && (Time.actual_schedule.Minute < 60)){
        if(*Horarios[contador_schedule] == Time.actual_schedule){
            contador_schedule++;
            Time.setMetroOn(encontrarMetroDisponible(Metros,20,Estaciones[0]), Estaciones[0]);
            Time.setMetroOn(encontrarMetroDisponible(Metros,20,Estaciones[19]), Estaciones[19]);

        }
        Time.moveTimeForward();
    }
}

MetroUnit *encontrarMetroDisponible(vector<MetroUnit*>metros, int largo, Station *estacion){
    for(MetroUnit *metro : metros){
        if(metro->state == "Fuera de servicio" && metro->getActualStation() == estacion)
            return metro;
    }
}
