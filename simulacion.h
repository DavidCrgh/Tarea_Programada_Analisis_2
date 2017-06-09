#ifndef SIMULACION_H
#define SIMULACION_H

#include <QApplication>

#include <QHash>
#include <vector>
#include <algorithm>
#include <iostream>
#include "time.h"

#include "matriz.h"

class Simulacion
{
public:
    //Atributos
    double probabilidadMutacion;
    int tamannoMatriz;
    int maximoPoblacion;
    int maximoGeneraciones;
    int generacion;

    long sumaFitness;
    long tamannoPoblacion;

    Matriz* cuadradoMagico;

    //Constructores
    Simulacion();

    //Metodos
    double calcularFitnessPromedio();
    QList<QList<int>*> cruzar(QList<int> padre1, QList<int> padre2);
    void revisarNoMapeados(QList<int>* hijo, QHash<int, int> mapeo,
                           int inicioMapeo, int finMapeo);
    bool estaEnZonaMapeada(int posicion, int puntoInicio, int puntoFin);
    QList<int> pasarAVector(Matriz *matriz);
    QList<QList<int> > pasarAMatriz(QList<int> *vector);

    QList<Matriz*> crearPoblacion(QList<int> numerosNecesarios,
                                  int tamaPoblacion, int tamMatriz,
                                  int constanteMagica);
    QList<Matriz*> seleccionNatural(QList<Matriz *> poblacion,int porcentaje,
                                     int fitnessMaximo);
    QList<Matriz *> cruzarPoblacion(int tamPoblacion,int tamBucket,
                                    QList<Matriz *> bucket,
                                    QList<Matriz *> poblacion,int numeroMagico,
                                    double probMutacion);
    /*void cuadradoMagico(double probabilidadMutacion,int tamMatriz,
                        int maximoPoblacion);*/ //Implementar en hilo

};

#endif // SIMULACION_H
