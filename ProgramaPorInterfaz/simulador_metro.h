#ifndef SIMULADOR_METRO_H
#define SIMULADOR_METRO_H
#include <iostream>
#include "metrounit.h"
#include "passenger.h"
#include "station.h"
#include "timecontroller.h"
#include "dia.h"
#include "schedule.h"
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <QMainWindow>
#include <QTimer>
#include <QLabel>

extern const string nombre_estaciones[20];
extern float Probability_to_descend[20];

QT_BEGIN_NAMESPACE
namespace Ui {
class Simulador_Metro;
}
QT_END_NAMESPACE

class Simulador_Metro : public QMainWindow
{
    Q_OBJECT

public:
    Simulador_Metro(QWidget *parent = nullptr);
    ~Simulador_Metro();
    MetroUnit *encontrarMetroDisponible(Station *estacion);
    static vector<MetroUnit*> Metros; //vector de informacion de metros disponibles
    static vector<Station *> Estaciones; //vector de informacion de estaciones
    static vector<Schedule*> Horarios; //vector de informacion de horarios de salidas de metro
    MetroUnit *encontrarSiguienteMetro(Station *estacionObjetivo, string direction);
    int calcTimeToArrive(MetroUnit *metro, Station *estacionObjetivo);
private slots:
    void avanzarSimulacion();
    void cambiarTiempoSimulacion();
    void cambiarEstacionObjetivo();
    void cambiarUnidadObjetivo();
    void tiempoSimulacion();
    void alternarSimulacion();
private:
    TimeController Time;
    Ui::Simulador_Metro *ui;
    QTimer *timer;
    int tiempo_actual = 0;
    QTimer *timerSeg;
    Station* EstacionObjetivo;
    MetroUnit* UnidadObjetivo;
};
#endif // SIMULADOR_METRO_H
