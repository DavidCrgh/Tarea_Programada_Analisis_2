#include "simulacion.h"

Simulacion::Simulacion()
{
    generacion = 0;
    sumaFitness = 0;
    tamannoPoblacion = 0;
    cuadradoMagico = NULL;
}

double Simulacion::calcularFitnessPromedio(){
    return (((double) sumaFitness / (double) tamannoPoblacion) /
            ((double)(2*tamannoMatriz + 2))) * 100;
}

QList<Matriz*> Simulacion::crearPoblacion(QList<int> numerosNecesarios,
                                          int tamaPoblacion, int tamMatriz,
                                          int constanteMagica)
{
    QList<Matriz*> poblacion;
    for(int i = 0;i<tamaPoblacion;i++)
    {

      Matriz* nuevaMatriz = new Matriz(tamMatriz, numerosNecesarios,
                                       constanteMagica);
      poblacion.append(nuevaMatriz);
    }
    return poblacion;
}

QList<Matriz*> Simulacion::seleccionNatural(QList<Matriz *> poblacion,
                                            int porcentaje, int fitnessMaximo)
{
    QList<Matriz *> bucket;
    for(int i = 0;i<porcentaje;i++)
    {
        int fitnessMatriz =poblacion.at(i)->fitness;
        double div = (double)fitnessMatriz/(double)fitnessMaximo;
        int porFitness = floor(div*100.00);
        for(int j = 0;j<porFitness;j++)
        {
            bucket.append(poblacion.at(i));
        }
    }
    return bucket;
}


QList<Matriz*> Simulacion::cruzarPoblacion(int tamPoblacion,int tamBucket,
                                QList<Matriz *> bucket,
                                QList<Matriz *> poblacion,int numeroMagico,
                                double probMutacion)
{

    for(int i = 0;i<tamPoblacion;i++)
    {

        int a = rand()%tamBucket;
        int b = rand()%tamBucket;

        Matriz * Father = bucket.at(a);
        Matriz * Mother = bucket.at(b);
        int tamUniversal = Father->getTamanno();

        QList<int> vFather = pasarAVector(Father);
        QList<int> vMother = pasarAVector(Mother);

        QList<QList<int>*> vHijos= cruzar(vFather,vMother);
        QList<int>* hijo1 = vHijos.takeAt(0);
        QList<int>* hijo2 = vHijos.takeAt(0);


        Matriz * hijoMatriz = new Matriz(tamUniversal);
        hijoMatriz->setMatrizDatos(pasarAMatriz(hijo1));


        int numeroRandom = rand() % 100000 + 1;

        /*int random = rand();
        double division = (1.00/(double)probMutacion)*100;
        int entero = floor(division);
        int numeroRan = random % entero;
        numeroRan++;*/
        if (numeroRandom < probMutacion * 1000)
        {
            hijoMatriz->mutacion();
        }
        hijoMatriz->fitness = hijoMatriz->funcionFitness(numeroMagico);
        poblacion.push_front(hijoMatriz);

        Matriz * hijaMatriz = new Matriz(tamUniversal);
        hijaMatriz->setMatrizDatos(pasarAMatriz(hijo2));
        numeroRandom = rand() % 100000 + 1;
        /*division = (1.00 / (double)probMutacion)*100;
        entero = floor(division);
        numeroRan = random % entero;
        numeroRan++;*/
        if (numeroRandom < probMutacion * 1000)
        {
            hijaMatriz->mutacion();
        }
        hijaMatriz->fitness = hijaMatriz->funcionFitness(numeroMagico);
        poblacion.push_front(hijaMatriz);
    }
    return poblacion;
}

QList<QList<int>*> Simulacion::cruzar(QList<int> padre1, QList<int> padre2){
    QList<int>* hijo1 = new QList<int>(padre1);
    QList<int>* hijo2 = new QList<int>(padre2);

    int punto1 = qrand() % padre1.size();
    int punto2 = qrand() % padre1.size();

    int longitud = punto2 - punto1;

    if(longitud < 0){
        longitud += padre1.size();
    }

    QHash<int,int> mapeo1;
    QHash<int,int> mapeo2;

    for(int i = 0; i < longitud; i++){
        int indice = (i + punto1) % padre1.size();

        int elemento1 = hijo1->at(indice);
        int elemento2 = hijo2->at(indice);

        hijo1->operator [](indice) = elemento2;
        hijo2->operator [](indice) = elemento1;

        mapeo1.insert(elemento1, elemento2);
        mapeo2.insert(elemento2, elemento1);
    }

    revisarNoMapeados(hijo1, mapeo2, punto1, punto2);
    revisarNoMapeados(hijo2, mapeo1, punto1, punto2);

    QList<QList<int>*> hijos;
    hijos.insert(0, hijo1);
    hijos.insert(1, hijo2);

    return hijos;
}

void Simulacion::revisarNoMapeados(QList<int>* hijo, QHash<int, int> mapeo,
                                   int inicioMapeo, int finMapeo){
    for(int i = 0; i < hijo->size(); i++){
        if(!estaEnZonaMapeada(i, inicioMapeo, finMapeo)){
            int mapeado = hijo->at(i);

            while(mapeo.contains(mapeado)){
                mapeado = mapeo[mapeado];
            }

            hijo->operator [](i) = mapeado;
        }
    }
}

bool Simulacion::estaEnZonaMapeada(int posicion, int puntoInicio, int puntoFin){
    bool encerrado = (posicion < puntoFin && posicion >= puntoInicio);
    bool circular = (puntoInicio > puntoFin && (posicion >= puntoInicio
                                                || posicion < puntoFin));

    return encerrado || circular;
}

QList<int> Simulacion::pasarAVector(Matriz * matriz)
{

    QList<int> vSalida;
    int tam = matriz->getTamanno();
    for (int i = 0; i<tam;i++){
        for(int j = 0; j<tam;j++){

            vSalida.push_back(matriz->getMatrizDatos().at(i).at(j));
        }
    }
    return vSalida;
}

QList<QList<int>> Simulacion::pasarAMatriz(QList<int> *vector)
{
    int dim = sqrt(vector->size());
    QList<QList<int>> mSalida;
    for (int i = 0; i<dim;i++){
        QList<int> v;
        mSalida.operator <<(v);
        for (int j = 0;j<dim;j++){
            mSalida[i].operator <<(0);
        }
    }
    for (int i = 0; i<vector->size() ; i++){
        int mI = i/dim;
        int mJ = i%dim;
        mSalida[mI][mJ] = vector->at(i);
    }
    return mSalida;
}
