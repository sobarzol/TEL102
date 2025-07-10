#include "simulador_metro.h"
#include "ui_simulador_metro.h"
#include <vector>



extern int Time_Between_Stations[20];
vector <Station *>Simulador_Metro::Estaciones;
vector <Schedule *>Simulador_Metro::Horarios;
vector <MetroUnit *>Simulador_Metro::Metros;
Simulador_Metro::Simulador_Metro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Simulador_Metro)
{
    EstacionObjetivo = NULL;            //inicializacion de todos los elementos necesarios.
    UnidadObjetivo = NULL;
    timer = new QTimer(this);       //se crea un timer para la simulacion
    timerSeg = new QTimer(this);    //se crea un timer cada un segundo para llevar el tiempo de simulacion
    ui->setupUi(this);
    connect(timerSeg, &QTimer::timeout, this, &Simulador_Metro::tiempoSimulacion);  //conecta el timer con el tiempo de simulacion
    connect(timer, &QTimer::timeout, this, &Simulador_Metro::avanzarSimulacion);    //conecta otro timer con el avance de la simulacion
    connect(ui->botonSimulacion, &QPushButton::clicked, this, &Simulador_Metro::alternarSimulacion);    //boton para comenzar y pausar simulacion
    connect(ui->comboBox_2, &QComboBox::currentIndexChanged, this, &Simulador_Metro::cambiarEstacionObjetivo);  //combobox para cambiar la estacion a desplegar
    connect(ui->comboBox, &QComboBox::currentIndexChanged, this, &Simulador_Metro::cambiarUnidadObjetivo);  //combobox para cambial la unidad a desplegar.
    connect(ui->comboBox_3, &QComboBox::currentIndexChanged, this, &Simulador_Metro::cambiarTiempoSimulacion);  //combobox para cambiar la velocidad de la simulacion
    timer->setInterval(1000);
    timerSeg->setInterval(1000);
    for(int i = 0; i < 20; i++){        //ciclo para crear estaciones con su nombre especifico
        Estaciones.push_back(new Station(nombre_estaciones[i],Probability_to_descend[i]));
    }
    for(int i = 0; i < 36;i++){         //ciclo para crear Metros, por defecto en 36 metros, la mitad se genera en limache y la otra en puerto
        Metros.push_back(new MetroUnit(392,i%2 == 0 ? Estaciones[0]:Estaciones[19]));
    }

    UnidadObjetivo = Metros[0];
    EstacionObjetivo = Estaciones[0];

    for(int i = 0; i < 7; i++){             //ciclo para crear informacion de salida de metros. por ahora cada 15 min
        for  (int j = 6; j < 23; j++){
            for (int k = 0; k < 4; k++){
                Horarios.push_back(new Schedule(static_cast<Dia>(i),j,k*15));
            }
        }
    }
    Time.setDay(1); //la simulacion comienza lunes a las 5:52
    Time.setHour(5);
    Time.setMinute(52);

}

void Simulador_Metro::cambiarTiempoSimulacion(){        //metodo para cambiar el tiempo de simulacion
    QStringList partes = ui->comboBox_3->currentText().split(" ");
    if (partes.size() < 1) return;
    bool ok = true;
    int tiempo = 60000/partes[0].toInt(&ok);
    if (!ok || tiempo <= 0 || tiempo == timer->interval()) return;
    timer->setInterval(tiempo); //se modifica el intervalo del timer que llama a avanzarSimulacion
}

void Simulador_Metro::tiempoSimulacion(){
    tiempo_actual+=1;   //cuenta los segundos de simulacion
    ui->tiempoSimulacion->setText("Tiempo de simulación: "+QString::number(tiempo_actual)+" s " + QString::number(timer->interval()));
}

void Simulador_Metro::avanzarSimulacion(){
    ui->DiaHoraMinuto->setText(QString::number(Time.actual_schedule.Hour)+"     "+QString::number(Time.actual_schedule.Minute));
    auto it = std::find_if(Horarios.begin(), Horarios.end(), [&](Schedule* obj) {
        return *obj == Time.actual_schedule;  // verifica si la fecha actual corresponde con una fecha de salida de metro
    });
    if (it != Horarios.end()) {
        Time.setMetroOn(encontrarMetroDisponible(Estaciones[0]), Estaciones[0]);    //posiciona un metro ubicado en estacion puerto en el anden para salir
        Time.setMetroOn(encontrarMetroDisponible(Estaciones[19]), Estaciones[19]);  //posiciona un metro ubicado en estacion limache en el anden para salir
    }
    int cont = 0;
    for (MetroUnit* metro: Metros) {
        if (metro->getState() == "En transito") {
            metro->reduceTimeToArrive();    //todos los metros que esten en transito reducen en uno su tiempo para llegar a la prox estacion
        }
        if (metro->getState() == "Esperando gente") {
            metro->descendPeople(); //los metros que estan esperando gente en una estacion hacen bajar a los pasajeros y subir a los pasajeros de la estacion
            metro->occupyMetro();
        }
    }
    for (Station *estacion : Estaciones) {              //Generar personas en todas las estaciones segun el flujo
        int cantidad_personas_generadas=0;
        if (estacion ->getFlow() == "muy alto")
            cantidad_personas_generadas = 25+rand()%9;
        else if (estacion->getFlow() == "alto")
            cantidad_personas_generadas = 15+rand()%7;
        else if (estacion->getFlow() == "medio")
            cantidad_personas_generadas = 8+rand()%5;
        else if (estacion->getFlow() == "bajo")
            cantidad_personas_generadas = 3+rand()%3;
        else if (estacion->getFlow() == "muy bajo")
            cantidad_personas_generadas = 1+rand()%2;
        for (int i = 0; i < cantidad_personas_generadas; i++) {
            Passenger *pasajero = new Passenger();
            estacion->receivePeople(pasajero); //entra cada persona generada a la estacion correspondiente
        }



        if (estacion == Estaciones[0]) {    //comprueba si un metro llego a la estacion final puerto
            MetroUnit* metroFinal = estacion->getPuertoPlatform();
            if (metroFinal != NULL) {
                metroFinal->setOff(); //apaga el metro
                estacion->setPlatformFree("Puerto");//libera el anden
            }
        }
        if (estacion == Estaciones[19]) {       //comprueba si un metro llego a la estacion final limache
            MetroUnit* metroFinal = estacion->getLimachePlatform();
            if (metroFinal != NULL) {
                metroFinal->setOff();   //apaga el metro
                estacion->setPlatformFree("Limache");//libera el anden
            }
        }

        estacion->departureMetro();//los metros que estaban en la estacion se van de la estacion


        if(estacion != Estaciones[0] && estacion != Estaciones[19]){    //para todas las estaciones menos las primeras estaciones
            MetroUnit *proximoAPuerto = encontrarSiguienteMetro(estacion, "Puerto");    //se obtiene el prox metro en ambas direcciones
            MetroUnit *proximoALimache = encontrarSiguienteMetro(estacion, "Limache");
            QLabel* label1 = NULL;
            QLabel* label2 = NULL;
            QLayoutItem* filaItem = ui->verticalLayout->itemAt(cont);  //se obtiene la fila correspondiente

            if (filaItem){
                QHBoxLayout* HLayout = qobject_cast<QHBoxLayout*>(filaItem->layout());
                if (HLayout){
                    QLayoutItem* labelItemPuerto = HLayout->itemAt(1);  //informacion sobre direccion puerto
                    QLayoutItem* labelItemLimache = HLayout->itemAt(2); //informacion sobre direccion limache
                    if (labelItemPuerto){
                        label1 = qobject_cast<QLabel*>(labelItemPuerto->widget());
                    }
                    if (labelItemLimache){
                        label2 = qobject_cast<QLabel*>(labelItemLimache->widget());
                    }
                }
            }
            if (proximoAPuerto != NULL) {
                if (label1){
                    //se modifica el label si existe un metro que viene en camino
                    label1->setText("Metro a Puerto en "+QString::number(calcTimeToArrive(proximoAPuerto, estacion))+". Ocupación: "+QString::number(int(double(proximoAPuerto->getOccupation())/double(proximoAPuerto->getCapacity())*100))+"%");
                }
            }
            else {
                if (label1){
                    //se modifica el label si no existe un metro que biene en camino
                    label1->setText("No hay metro a Puerto");
                }
            }
            if (proximoALimache != NULL){
                if (label2){
                    //se modifica el label si existe un metro que viene en camino
                    label2->setText("Metro a Limache en "+QString::number(calcTimeToArrive(proximoALimache, estacion))+". Ocupación: "+QString::number(int(double(proximoALimache->getOccupation())/double(proximoALimache->getCapacity())*100))+"%");
                }
            }
            else{
                if (label2){
                    //se modifica el label si no existe un metro que viene en camino.
                    label2->setText("No hay metro a Limache");
                }
            }
        }



        cont++; //contador para fila aumenta

    }
    //despliegue de informacion de estacion y unidad objetivo
    ui->labelOcupacion->setText("Ocupación: " + QString::number(UnidadObjetivo->getOccupation())+ " personas.");
    ui->label_estacionactual->setText("Estación actual: " + QString::fromStdString(UnidadObjetivo->getActualStation()->getName()));
    ui->label_estadoactual->setText("Estado actual: " + QString::fromStdString(UnidadObjetivo->getState()));
    ui->label_estacionsiguiente->setText("Dirección: "+ QString::fromStdString(UnidadObjetivo->getDirection()));
    ui->label_tiempoasiguiente->setText("Tiempo a siguiente estación: "+ QString::number(UnidadObjetivo->getTimeToArrive()));
    ui->label_andenlimache->setText("Personas en anden a Limache: " + QString::number(EstacionObjetivo->getLimachePassengers()));
    ui->label_andenpuerto->setText("Personas en anden a Puerto: " + QString::number(EstacionObjetivo->getPuertoPassengers()));

    MetroUnit *proximoAPuertoObj = encontrarSiguienteMetro(EstacionObjetivo, "Puerto");
    ui->label_siguientepuerto->setText("Siguiente metro a puerto en: "+QString::number(calcTimeToArrive(proximoAPuertoObj, EstacionObjetivo)));

    MetroUnit *proximoALimacheObj = encontrarSiguienteMetro(EstacionObjetivo, "Limache");
    ui->label_siguientelimache->setText("Siguiente metro a limache en: "+ QString::number(calcTimeToArrive(proximoALimacheObj, EstacionObjetivo)));
    Time.moveTimeForward(); //avanza el tiempo
}

void Simulador_Metro::cambiarUnidadObjetivo(){  //metodo que cambia la unidad objetivo con respecto al cambio en la combobox
    UnidadObjetivo = NULL;
    QStringList partes = ui->comboBox->currentText().split(" ");
    if (partes.size()>2) return;
    bool ok = true;
    int indice = partes[1].toInt(&ok) - 1;
    UnidadObjetivo = Metros[indice];
    ui->DiaHoraMinuto->setText(QString::number(indice));
}

void Simulador_Metro::cambiarEstacionObjetivo(){    //metodo que cambia la estacion objetivo con respecto al cambio en la combobox
    EstacionObjetivo = NULL;
    QStringList partes = ui->comboBox_2->currentText().split("Estación ");
    if (partes.size()<1) return;
    for (int i = 0; i < int(Estaciones.size()); i++){
        if (partes[1].trimmed() == Estaciones[i]->getName()){
            EstacionObjetivo = Estaciones[i];

        }
    }
    ui->DiaHoraMinuto->setText(QString::fromStdString(EstacionObjetivo->getName()));

}

void Simulador_Metro::alternarSimulacion(){ //metodo que pausa o detiene la simulacion.
    if (ui->botonSimulacion->text()=="Comenzar simulación"){//si esta pausada comienza
        timerSeg->start();
        timer->start();
        ui->botonSimulacion->setText("Detener simulación");

    }
    else if (ui->botonSimulacion->text()=="Detener simulación"){//si esta ejecutandose se pausa
        timerSeg->stop();
        timer->stop();
        tiempo_actual = 0;
        ui->tiempoSimulacion->setText("Tiempo de simulación: 0 s");
        ui->botonSimulacion->setText("Comenzar simulación");
    }
}

Simulador_Metro::~Simulador_Metro()
{
    delete ui;
}

MetroUnit *Simulador_Metro::encontrarMetroDisponible(Station *estacion){    //metodo para encontrar un metro disponible para utilizar en una estacion especifica.
    for(MetroUnit *metro : Metros){
        if(metro->getState() == "Fuera de servicio" && metro->getActualStation() == estacion)
            return metro;
    }
    return NULL;
}

MetroUnit *Simulador_Metro::encontrarSiguienteMetro(Station *estacionObjetivo, string direction){   //metodo que retorna el siguiente metro en llegar a la estacion segun su direccion
    MetroUnit *nextMetro = NULL;
    int minTime = INT_MAX;
    for (MetroUnit *metro : Metros) {
        if ((metro->getState() == "En transito" && metro->getActualStation()!= estacionObjetivo) || metro->getState() == "Esperando gente") {
            if (metro->getDirection() == direction) {
                int estimatedTime = calcTimeToArrive(metro, estacionObjetivo);
                if (estimatedTime >= 0 && estimatedTime < minTime) {
                    minTime = estimatedTime;
                    nextMetro = metro;
                }
            }
        }
    }
    return nextMetro;
}

int Simulador_Metro::calcTimeToArrive(MetroUnit *metro, Station *estacionObjetivo){ //metodo que calcula el tiempo que demora en llegar un metro cualquierar a una estacion especifica.
    if (!metro || !estacionObjetivo) return -1; //retorna -1 si falla, o si el metro no llegara a la estacion segun su recorrido

    Station *actualStation = metro->getActualStation();
    string direction = metro->getDirection();

    int idxActual = -1, idxObjetivo = -1;
    for (int i = 0; i < 20; i++) {
        if (Estaciones[i] == actualStation)
            idxActual = i;
        if (Estaciones[i] == estacionObjetivo)
            idxObjetivo = i;
    }

    if (idxActual == -1 || idxObjetivo == -1) return -1;
    if (idxActual == idxObjetivo) return 0;

    int tiempoTotal = metro->getTimeToArrive();  // tiempo al primer tramo

    if (direction == "Puerto") {
        int siguiente = metro->getState() == "En transito" ? idxActual - 1 : idxActual;
        if (idxObjetivo > siguiente) return -1; // ya pasó

        // Suma desde la estacion siguiente hasta la estación objetivo
        for (int i = siguiente; i > idxObjetivo; --i)
            tiempoTotal += Time_Between_Stations[i - 1];

        return tiempoTotal;
    }

    if (direction == "Limache") {
        int siguiente = metro->getState() == "En transito" ? idxActual + 1 : idxActual;
        if (idxObjetivo < siguiente) return -1; // ya paso

        for (int i = siguiente; i < idxObjetivo; ++i)
            tiempoTotal += Time_Between_Stations[i];
        return tiempoTotal;
    }

    return -1;
}



