#include "timecontroller.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "dia.h"

using namespace std;
class Passenger;


TimeController::TimeController() {}

void TimeController::moveTimeForward(){
    if (actual_schedule.Minute < 60){
        actual_schedule.Minute++;
        if (actual_schedule.Minute == 60) {
            if (actual_schedule.Hour < 22) {
                actual_schedule.Hour++;
                if (actual_schedule.Hour == 23) {
                    actual_schedule.Day = static_cast<Dia>(static_cast<int>(actual_schedule.Day) + 1);
                    actual_schedule.Hour = 5;
                    actual_schedule.Minute = 45;
                }
                else
                    actual_schedule.Minute = 0;
            }
        }
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
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

