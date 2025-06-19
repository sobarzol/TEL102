#include "schedule.h"

Schedule::Schedule() {}

Schedule::Schedule(Dia aDay, int aHour, int aMinute) {
    Day = aDay;
    Hour = aHour;
    Minute = aMinute;
}


bool Schedule::operator==(const Schedule& otra) const {
    return (static_cast<int>(Day) == static_cast<int>(otra.Day)) &&
           (Hour == otra.Hour) && (Minute == otra.Minute);
}
