#include "hilosimulacion.h"

using namespace std;

HiloSimulacion::HiloSimulacion(QObject* parent, Simulacion* pSimulacion)
{
    stop = false;
    pause = true;
    simulacion = pSimulacion;
}

void HiloSimulacion::run(){
    QList<int> numerosNecesarios;
    QList<Matriz*> poblacion;
    int tamannoMatriz = simulacion->tamannoMatriz;

    for(int i = 1; i <= tamannoMatriz * tamannoMatriz; i++)
    {
        numerosNecesarios.append(i);
    }

    int tamanoPoblacion = 2500; //Tamanno inicial

    //Se define constante magica
    int constanteMagica = tamannoMatriz * (tamannoMatriz * tamannoMatriz
                                           + 1) / 2;
    cout<<"Consante Magica: "<<constanteMagica<<endl;

    //Realiza la creacion de poblacion segun el porcentaje deseado;
    poblacion = simulacion->crearPoblacion(numerosNecesarios,
                                           tamanoPoblacion,tamannoMatriz,
                                           constanteMagica);

    //Resultado que debe dar el fitness para que sea correcto
    int resultadoFinal = tamannoMatriz + tamannoMatriz + 2;
    cout<<"Resultado Final: "<<resultadoFinal<<endl;

    simulacion->generacion = 0;

    while(!stop & simulacion->generacion < simulacion->maximoGeneraciones){
        while(pause){
            msleep(100);
        }

        cout<<"Ronda #"<<simulacion->generacion<<endl;
        int fitnessMaximo = 0;
        bool encontrado = false;
        simulacion->sumaFitness = 0;
        for(int i = 0; i < tamanoPoblacion; i++)
        {
             int fitnessActual = poblacion.at(i)->fitness;
             simulacion->sumaFitness += fitnessActual;

             if (fitnessActual > 6)
             {
                 cout<<"Fitness en la pos "<<i<<" = "<<fitnessActual<<endl;
             }

            if (resultadoFinal == fitnessActual)
            {
                //Aqui se debe presentar en pantalla es la solucion
                simulacion->cuadradoMagico = poblacion.at(i);
                poblacion.at(i)->imprimir();
                encontrado = true;
                break;
            }
            else
            {
                if(fitnessMaximo < poblacion.at(i)->getFitness())
                {
                    fitnessMaximo = poblacion.at(i)->getFitness();
                }
            }
        }

        simulacion->tamannoPoblacion = poblacion.size();
        emit triggerActualizarInterfaz();

        if(encontrado == true)
        {
            emit triggerCuadradoEncontrado();
            emit triggerFinalizarSimulacion();
            break;
        }
        //Seleccion Natural
        QList<Matriz*> bucket = simulacion->seleccionNatural(poblacion,
                                                             tamanoPoblacion,
                                                             fitnessMaximo);

        //Generaciones
        poblacion = simulacion->cruzarPoblacion(tamanoPoblacion, bucket.size(),
                                                bucket, poblacion,
                                                constanteMagica,
                                                simulacion->probabilidadMutacion);
        tamanoPoblacion =  poblacion.size();
        while(tamanoPoblacion > simulacion->maximoPoblacion)
        {
            int indice = rand() % tamanoPoblacion;
            delete poblacion.takeAt(indice);
            tamanoPoblacion = poblacion.size();
        }

        simulacion->tamannoPoblacion = poblacion.size();
        cout<<poblacion.size()<<endl;
        cout<<"end"<<endl;
        cout<<endl;

        //qDebug("Aqui va algoritmo genetico");
        //emit triggerActualizarInterfaz();
        simulacion->generacion++;
        msleep(100);
    }
    emit triggerFinalizarSimulacion();
}
