#ifndef TIMECONTROLLER_H
#define TIMECONTROLLER_H

#include <vector>
#include <string>
#include "schedule.h"
enum class Dia;
class MetroUnit;
class Station;
using namespace std;

class TimeController
{
public:
    TimeController();
    void createPassenger();
    void moveTimeForward();
    void setMetroOn(MetroUnit *metro, Station *estacion_de_inicio);
    Schedule actual_schedule;
};

#endif // TIMECONTROLLER_H
