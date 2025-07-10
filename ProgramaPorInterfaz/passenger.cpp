#include "passenger.h"
#include "station.h"
#include <time.h>

Passenger::Passenger() {    //constructor por defecto
    passenger_id = next_passenger_id++;     //se le asigna una id
    direction = rand()%2 == 0? "Limache" : "Puerto";    //se crea con una direccion especifica.
}

int Passenger::next_passenger_id = []() {   //inicializacion variable estatica
    return 0;
}();

/*Passenger::~Passenger() {

}
*/

int Passenger::getId() {
    return passenger_id;    //metodo para obtener la id
}


string Passenger::getDirection() {  //metodo para obtener la direccion
    return direction;
}

Passenger::~Passenger() = default;
