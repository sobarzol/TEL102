#include "simulador_metro.h"

#include <QApplication>
int Time_Between_Stations[19] = {2, 2, 2, 3, 5, 3, 1, 1, 1, 3, 13, 3, 3, 3, 2, 2, 2, 3, 12};          // vector de informacion de tiempo entre estaciones
const string nombre_estaciones[20] = {"Puerto", "Bellavista", "Francia", "Barón", "Portales", "Recreo", "Miramar",            //vector de informacion para crear estaciones
                                      "Viña del Mar", "Hospital", "Chorrillos", "El Salto", "Quilpué", "El Sol", "El Belloto",
                                      "Las Américas", "La Concepción", "Villa Alemana", "Sargento Aldea", "Peñablanca", "Limache"};
float Probability_to_descend [20] = {1, 0.17, 0.18, 0.2, 0.207, 0.15, 0.24, 0.5, 0.22, 0.28, 0.115, 0.35, 0.14, 0.2, 0.18, 0.15, 0.3, 0.2, 0.2, 1 };



int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    Simulador_Metro w;

    //w.setFixedSize(1200,700);
    w.show();
    return a.exec();
}
