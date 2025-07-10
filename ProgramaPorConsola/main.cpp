#include <iostream>
#include "metrounit.h"
#include "passenger.h"
#include "station.h"
#include "timecontroller.h"
#include "dia.h"
#include "schedule.h"
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>


using namespace std;

MetroUnit *encontrarMetroDisponible(vector<MetroUnit*>metros, int largo, Station *estacion);
int calcTimeToArrive(MetroUnit *metro, Station *estacionObjetivo);
MetroUnit *encontrarSiguienteMetro(vector<MetroUnit*>metros, Station *estacionObjetivo, string direction);



int Time_Between_Stations[19] = {2, 2, 2, 3, 5, 3, 1, 1, 1, 3, 13, 3, 3, 3, 2, 2, 2, 3, 12};          // vector de informacion de tiempo entre estaciones
const string nombre_estaciones[20] = {"Puerto", "Bellavista", "Francia", "Baron", "Portales", "Recreo", "Miramar",            //vector de informacion para crear estaciones
                                "Vina del Mar", "Hospital", "Chorrillos", "El Salto", "Quilpue", "El Sol", "El Belloto",
                                "Las Americas", "La Concepcion", "Villa Alemana", "Sargento Aldea", "Penablanca", "Limache"};
float Probability_to_descend [20] = {1, 0.17, 0.18, 0.2, 0.207, 0.15, 0.24, 0.5, 0.22, 0.28, 0.115, 0.35, 0.14, 0.2, 0.18, 0.15, 0.3, 0.2, 0.2, 1 };
vector<MetroUnit*> Metros; //vector de informacion de metros disponibles
vector<Station *> Estaciones; //vector de informacion de estaciones
vector<Schedule*> Horarios; //vector de informacion de horarios de salidas de metro
//
int main()
{
    srand(time(NULL));
    for(int i = 0; i < 20; i++){        //ciclo para crear estaciones con su nombre especifico
        Estaciones.push_back(new Station(nombre_estaciones[i],Probability_to_descend[i]));
    }
    for(int i = 0; i < 36;i++){         //ciclo para crear Metros, por defecto en 36 metros, la mitad se genera en limache y la otra en puerto
        Metros.push_back(new MetroUnit(392,i%2 == 0 ? Estaciones[0]:Estaciones[19]));
    }



    for(int i = 0; i < 7; i++){             //ciclo para crear informacion de salida de metros. por ahora cada 15 min
        for  (int j = 6; j < 23; j++){
            for (int k = 0; k < 4; k++){
                Horarios.push_back(new Schedule(static_cast<Dia>(i),j,k*15));
            }
        }
    }

    //Toma de informacion al usuario sobre cuando partir la simulacion y la estacion objetivo
    int dia = -1;
    int hora = -1;
    int minuto = -1;
    int numero_estacion_objetivo = -1;
    while (dia < 1 || dia > 7) {
        cout << "Ingrese dia \n 1. Lunes\n 2. Martes\n 3. Miercoles\n 4. Jueves \n 5. Viernes\n 6. Sabado \n 7. Domingo" << endl;
        cin >> dia;
    }
    while (hora < 5 || hora > 22) {
        cout << "Ingrese hora(entre 5 y 22):" <<endl;
        cin >> hora;
    }

    while (minuto < 0 || minuto > 59) {
        cout << "Ingrese minuto(entre 00 y 59):" <<endl;
        cin >> minuto;
    }
    while (numero_estacion_objetivo < 1 || numero_estacion_objetivo > 20) {
        cout << "Ingrese estacion objetivo: \n 1. Puerto \n 2. Bellavista \n " <<
                "3. Francia \n 4. Baron \n 5. Portales \n 6. Recreo \n" <<
                " 7. Miramar \n 8. Vina del Mar \n 9. Hospital \n" <<
                " 10. Chorrillos \n 11. El Salto \n 12. Quilpue \n" <<
                " 13. El Sol \n 14. El Belloto \n 15. Las Americas \n" <<
                " 16. La Concepcion \n 17. Villa Alemana \n 18. Sargento Aldea \n" <<
                " 19. Penablanca \n 20. Limache \n" << endl;
        cin >> numero_estacion_objetivo;
    }
    Station *estacion_objetivo = Estaciones[numero_estacion_objetivo-1]; //estacion de la cual se desplegara informacion

    TimeController Time;//iniciar un temporizador a un dia y horario especifico
    Time.setDay(dia-1);
    Time.setHour(hora);
    Time.setMinute(minuto);

    while (!((Time.actual_schedule.Day == Dia::Domingo) && ((Time.actual_schedule.Hour == 22)) && ((Time.actual_schedule.Minute == 59)))){
        //Si se esta en un horario de salida de metros se crean metros en ambas estaciones.

        auto it = std::find_if(Horarios.begin(), Horarios.end(), [&](Schedule* obj) {
                return *obj == Time.actual_schedule;  // Aquí sí comparas contenido usando tu operador ==
            });
        if (it != Horarios.end()) {
            Time.setMetroOn(encontrarMetroDisponible(Metros,20,Estaciones[0]), Estaciones[0]);
            Time.setMetroOn(encontrarMetroDisponible(Metros,20,Estaciones[19]), Estaciones[19]);
        }





        for (Station *estacion : Estaciones) {              //Generar personas en todas las estaciones segun el flujo
            int cantidad_personas_generadas=0;
            if (estacion ->getFlow() == "muy alto")
                cantidad_personas_generadas = 25+rand()%9;
            else if (estacion->getFlow() == "alto")
                cantidad_personas_generadas = 15+rand()%7;
            else if (estacion->getFlow() == "medio")
                cantidad_personas_generadas = 8+rand()%5;
            else if (estacion->getFlow() == "bajo")
                cantidad_personas_generadas = 3+rand()%3;
            else if (estacion->getFlow() == "muy bajo")
                cantidad_personas_generadas = 1+rand()%2;
            for (int i = 0; i < cantidad_personas_generadas; i++) {
                Passenger *pasajero = new Passenger();
                estacion->receivePeople(pasajero);
            }







            if (estacion == estacion_objetivo) {
                if (Time.actual_schedule.Minute<10) {
                    cout << "Dia:" << Time.getDay() << " Hora: " << Time.actual_schedule.Hour << ":" << "0" << Time.actual_schedule.Minute << endl;
                }
                else {
                    cout << "Dia:" << Time.getDay() << " Hora: " << Time.actual_schedule.Hour << ":" << Time.actual_schedule.Minute << endl;
                }
                cout << "Pasajeros en estacion " << estacion->getName() << ":"<< estacion->getTotalPassengers() <<endl;
                if (estacion->getPuertoPlatform() != NULL) {
                    cout << "El metro en direccion puerto tiene: " << estacion->getPuertoPlatform()->getOccupation() << " personas." << endl;
                }
                else {
                    cout << "No hay metro." << endl;
                }
                if (estacion->getLimachePlatform() != NULL) {
                    cout<<"El metro en direccion Limache tiene: " << estacion->getLimachePlatform()->getOccupation() << " personas." << endl;
                }
                else {
                    cout << "No hay metro." << endl;
                }
                MetroUnit *proximoAPuerto = encontrarSiguienteMetro(Metros, estacion_objetivo, "Puerto");
                MetroUnit *proximoALimache = encontrarSiguienteMetro(Metros, estacion_objetivo, "Limache");
                if (proximoAPuerto != NULL) {
                    int tiempo = calcTimeToArrive(proximoAPuerto, estacion_objetivo);
                    cout << "Siguiente metro a puerto pasa en: " << tiempo << endl;

                }
                else {
                    cout << "No hay metro en direccion puerto." << endl;
                }
                if (proximoALimache != NULL) {
                    int tiempo = calcTimeToArrive(proximoALimache, estacion_objetivo);
                    cout << "Siguiente metro a Limache pasa en: " << tiempo << endl;
                }
                else {
                    cout << "No hay metro en direccion Limache." << endl;
                }
                cout << endl;

            }

            MetroUnit *metroFinal;
            if (estacion == Estaciones[0]) {
                metroFinal = estacion->getPuertoPlatform();
                if (metroFinal != NULL) {
                    metroFinal->setOff();
                    estacion->setPlatformFree("Puerto");
                }
            }
            if (estacion == Estaciones[19]) {
                metroFinal = estacion->getLimachePlatform();
                if (metroFinal != NULL) {
                    metroFinal->setOff();
                    estacion->setPlatformFree("Limache");
                }
            }

            estacion->departureMetro();
        }
        cout << "Cantidad de gente metro 1: " << Metros[0]->getOccupation() << " en estacion: " << Metros[0]->getActualStation()->getName() << endl;





        for (MetroUnit* metro: Metros) {
            if (metro->getState() == "En transito") {
                metro->reduceTimeToArrive();
            }
            if (metro->getState() == "Esperando gente") {
                metro->descendPeople();
                metro->occupyMetro();
            }
        }



        Time.moveTimeForward();

    }
}



MetroUnit *encontrarMetroDisponible(vector<MetroUnit*>metros, int largo, Station *estacion){
    for(MetroUnit *metro : metros){
        if(metro->getState() == "Fuera de servicio" && metro->getActualStation() == estacion)
            return metro;
    }
    return NULL;
}

MetroUnit *encontrarSiguienteMetro(vector<MetroUnit*>metros, Station *estacionObjetivo, string direction) {
    MetroUnit *nextMetro = NULL;
    int minTime = INT_MAX;
    for (MetroUnit *metro : metros) {
        if (metro->getState() == "En transito" || metro->getState() == "Esperando gente") {
            if (metro->getDirection() == direction) {
                int estimatedTime = calcTimeToArrive(metro, estacionObjetivo);
                if (estimatedTime >= 0 && estimatedTime < minTime) {
                    minTime = estimatedTime;
                    nextMetro = metro;
                }
            }
        }
    }
    return nextMetro;
}

int calcTimeToArrive(MetroUnit *metro, Station *estacionObjetivo) {
    if (!metro || !estacionObjetivo) return -1;

    Station *actualStation = metro->getActualStation();
    string direction = metro->getDirection();

    int idxActual = -1, idxObjetivo = -1;
    for (int i = 0; i < 20; i++) {
        if (Estaciones[i] == actualStation)
            idxActual = i;
        if (Estaciones[i] == estacionObjetivo)
            idxObjetivo = i;
    }

    if (idxActual == -1 || idxObjetivo == -1) return -1;
    if (idxActual == idxObjetivo) return 0;

    int tiempoTotal = metro->getTimeToArrive();  // tiempo al primer tramo

    if (direction == "Puerto") {
        int siguiente = metro->getState() == "En transito" ? idxActual - 1 : idxActual;
        if (idxObjetivo > siguiente) return -1; // ya pasó

        // Suma desde la estacion siguiente hasta la estación objetivo
        for (int i = siguiente; i > idxObjetivo; --i)
            tiempoTotal += Time_Between_Stations[i - 1];

        return tiempoTotal;
    }

    if (direction == "Limache") {
        int siguiente = metro->getState() == "En transito" ? idxActual + 1 : idxActual;
        if (idxObjetivo < siguiente) return -1; // ya paso

        for (int i = siguiente; i < idxObjetivo; ++i)
            tiempoTotal += Time_Between_Stations[i];
        return tiempoTotal;
    }

    return -1;
}
