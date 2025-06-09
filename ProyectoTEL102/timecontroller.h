#ifndef TIMECONTROLLER_H
#define TIMECONTROLLER_H

#include <vector>
#include <string>

class TimeController
{
public:
    TimeController();
    void createPassenger();
    void moveTimeForward();
    void setMetroOn(MetroUnit metro);
private:
    string ActualDay;
    int ActualHour;
    int ActualMinute;
};

#endif // TIMECONTROLLER_H
