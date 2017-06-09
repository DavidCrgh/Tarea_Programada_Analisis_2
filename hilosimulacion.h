#ifndef HILOEVOLUCION_H
#define HILOEVOLUCION_H

#include <QMutex>
#include <QObject>
#include <QThread>

#include "simulacion.h"

class HiloSimulacion : public QThread
{
    Q_OBJECT
public:
    //Atributos
    bool pause;
    bool stop;
    QMutex mute;

    Simulacion* simulacion;

    //Constructores
    HiloSimulacion(QObject* parent = 0, Simulacion* pSimulacion = 0);

    //Metodos
    void run();

signals:
    void triggerActualizarInterfaz();
    void triggerFinalizarSimulacion();
    void triggerCuadradoEncontrado();
};

#endif // HILOEVOLUCION_H
