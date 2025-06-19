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


using namespace std;

MetroUnit *encontrarMetroDisponible(vector<MetroUnit*>metros, int largo, Station *estacion);



int Time_Between_Stations[19] = {2, 2, 2, 3, 5, 3, 1, 1, 1, 3, 13, 3, 3, 3, 2, 2, 2, 3, 12};          // vector de informacion de tiempo entre estaciones
const string nombre_estaciones[20] = {"Puerto", "Bellavista", "Francia", "Barón", "Portales", "Recreo", "Miramar",            //vector de informacion para crear estaciones
                                "Viña del Mar", "Hospital", "Chorrillos", "El Salto", "Quilpué", "El Sol", "El Belloto",
                                "Las Américas", "La Concepción", "Villa Alemana", "Sargento Aldea", "Peñablanca", "Limache"};

vector<MetroUnit*> Metros; //vector de informacion de metros disponibles
vector<Station *> Estaciones; //vector de informacion de estaciones
vector<Schedule*> Horarios; //vector de informacion de horarios de salidas de metro
int main()
{
    srand(time(NULL));
    for(int i = 0; i < 20; i++){        //ciclo para crear estaciones con su nombre especifico
        Estaciones.push_back(new Station(nombre_estaciones[i]));
    }
    for(int i = 0; i < 36;i++){         //ciclo para crear Metros, por defecto en 36 metros, la mitad se genera en limache y la otra en puerto
        Metros.push_back(new MetroUnit(392,i%2 == 0 ? Estaciones[0]:Estaciones[19]));
    }



    for(int i = 0; i < 7; i++){             //ciclo para crear informacion de salida de metros. por ahora cada 15 min
        for  (int j = 6; j < 24; j++){
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
        cout << "Ingrese dia \n 1. Lunes\n 2. Martes\n 3. Miercoles\n 4.Jueves \n 5. Viernes\n 6. Sabado \n 7. Domingo" << endl;
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
        cout << "Ingrese estacion objetivo: \n 1.Puerto \n 2.Bellavista \n " <<
                "3. Francia \n 4. Baron \n 5.Portales \n 6. Recreo \n" <<
                " 7. Miramar \n 8. Viña del Mar \n 9. Hospital \n" <<
                " 10. Chorrillos \n 11. El Salto \n 12. Quilpue \n" <<
                " 13. El Sol \n 14.El Belloto \n 15.Las Americas \n" <<
                " 16.La Concepcion \n 17.Villa Alemana \n 18.Sargento Aldea \n" <<
                " 19. Peñablanca \n 20.Limache \n" << endl;
        cin >> numero_estacion_objetivo;
    }
    Station *estacion_objetivo = Estaciones[numero_estacion_objetivo-1]; //estacion de la cual se desplegara informacion

    TimeController Time;//iniciar un temporizador a un dia y horario especifico
    Time.setDay(dia);
    Time.setHour(hora);
    Time.setMinute(minuto);

    int contador_schedule = 0; //contador para horarios especificos de salida de metro
    while (static_cast<int>(Time.actual_schedule.Day) < static_cast<int>(Dia::Domingo) && (Time.actual_schedule.Hour < 23) && (Time.actual_schedule.Minute < 60)){
        for (Station *estacion : Estaciones) {
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
                cout << "Dia:" << static_cast<int>(Time.actual_schedule.Day) << " Hora: " << Time.actual_schedule.Hour << ":" << Time.actual_schedule.Minute << endl;
                cout << "Pasajeros en estacion: " << estacion->getName() << endl;
                estacion->showPassengers();
            }
        }
        //si un instante coincide con un horario de salida de un metro, iniciar su servicio en algun metro disponible
        /*
        if(*Horarios[contador_schedule] == Time.actual_schedule){
            contador_schedule++;
            Time.setMetroOn(encontrarMetroDisponible(Metros,20,Estaciones[0]), Estaciones[0]);
            Time.setMetroOn(encontrarMetroDisponible(Metros,20,Estaciones[19]), Estaciones[19]);

        }
        */
        Time.moveTimeForward();

    }
}

/*

MetroUnit *encontrarMetroDisponible(vector<MetroUnit*>metros, int largo, Station *estacion){
    for(MetroUnit *metro : metros){
        if(metro->getState() == "Fuera de servicio" && metro->getActualStation() == estacion)
            return metro;
    }
}
*/