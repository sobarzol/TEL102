#include "passenger.h"
#include "station.h"
#include <time.h>

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

