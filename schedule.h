#ifndef SCHEDULE_H
#define SCHEDULE_H

enum class Dia;
class Schedule
{
public:
    Schedule();
    Schedule(Dia aDay, int aHour, int aMinute);
    Dia Day;
    int Hour;
    int Minute;
    bool operator ==(const Schedule& otra) const;
};

#endif // SCHEDULE_H
