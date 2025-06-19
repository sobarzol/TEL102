#include "passenger.h"
#include "station.h"
#include <time.h>

Passenger::Passenger() {
    passenger_id = next_passenger_id++;
    direction = rand()%2 == 0? "Limache" : "Puerto";
    //total_passengers++;
}

int Passenger::next_passenger_id = []() {
    return 0;
}();

/*Passenger::~Passenger() {
    total_passengers--;
}
*/

int Passenger::getId() {
    return passenger_id;
}


