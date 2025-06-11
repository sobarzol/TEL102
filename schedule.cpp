#include "schedule.h"

Schedule::Schedule() {}

bool Schedule::operator==(const Schedule& otra) const {
    return (static_cast<int>(Day) == static_cast<int>(otra.Day)) &&
           (Hour == otra.Hour) && (Minute == otra.Minute);
}
