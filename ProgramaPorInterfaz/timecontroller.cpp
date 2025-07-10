#include "timecontroller.h"
#include "dia.h"
#include "metrounit.h"
#include "station.h"
using namespace std;
class Passenger;


TimeController::TimeController() {}

void TimeController::moveTimeForward(){ //avanza la fecha en un segundo
    if (actual_schedule.Minute < 60){
        actual_schedule.Minute++;
        if (actual_schedule.Minute == 60) {
            if (actual_schedule.Hour <= 22) {
                actual_schedule.Hour++;
                if (actual_schedule.Hour == 23) {
                    if (actual_schedule.Day != Dia::Domingo) {
                        actual_schedule.Day = static_cast<Dia>(static_cast<int>(actual_schedule.Day) + 1);
                        actual_schedule.Hour = 5;
                        actual_schedule.Minute = 45;
                    }
                }
                else
                    actual_schedule.Minute = 0;
            }
        }
    }
}

void TimeController::setDay(int dia){
    actual_schedule.Day = static_cast<Dia>(dia);
}

void TimeController::setHour(int hora){
    actual_schedule.Hour = hora;
}

void TimeController::setMinute(int minuto){
    actual_schedule.Minute = minuto;
}

string TimeController::getDay() {
    if (actual_schedule.Day == Dia::Lunes)
        return "Lunes";
    if (actual_schedule.Day == Dia::Martes) {
        return "Martes";
    }
    if (actual_schedule.Day == Dia::Miercoles) {
        return "Miercoles";
    }
    if (actual_schedule.Day == Dia::Jueves) {
        return "Jueves";
    }
    if (actual_schedule.Day == Dia::Viernes) {
        return "Viernes";
    }
    if (actual_schedule.Day == Dia::Sabado) {
        return "Sabado";
    }
    if (actual_schedule.Day == Dia::Domingo) {
        return "Domingo";
    }
    return "Nada";

}

void TimeController::setMetroOn(MetroUnit *metro,Station *estacion_de_inicio ) {    // enciende un metro en una estacion.
    metro->setOn(estacion_de_inicio->getName() == "Limache" ? "Puerto" : "Limache");
    estacion_de_inicio->setMetroPlatform(metro);
}
