#include "schedule.h"

Schedule::Schedule() {}

Schedule::Schedule(Dia aDay, int aHour, int aMinute) {  //constructor con  dia hora y minuto
    Day = aDay;
    Hour = aHour;
    Minute = aMinute;
}


bool Schedule::operator==(const Schedule& otra) const {     //sobrecarga de operador == para comparar dos horarios.
    return (static_cast<int>(Day) == static_cast<int>(otra.Day)) &&
           (Hour == otra.Hour) && (Minute == otra.Minute);
}
