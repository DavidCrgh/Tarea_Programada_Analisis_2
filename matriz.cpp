#include <stdlib.h>
#include <iostream>

#include "matriz.h"

using namespace std;

int Matriz::getFitness() const
{
    return fitness;
}

void Matriz::setFitness(int value)
{
    fitness = value;
}

Matriz::Matriz(int tama, QList<int> numeros,int constanteMagica)
{
    this->setTamanno(tama);
    int tamRandom = tama*tama-1;

    //Controla las filas
    for(int i = 0;i<tama;i++)
    {
        //Controla las columnas
        QList<int> filas;
        for(int j = 0;j<tama;j++)
        {
            int indice;
            if(tamRandom == 0)
            {
                indice = 0;
            }
            else
            {
                indice = (rand()%tamRandom);
            }
            int numeroM = numeros.at(indice);
            numeros.move(indice,tamRandom);
            filas.append(numeroM);
            tamRandom--;
        }
        this->matrizDatos.append(filas);
    }
        this->fitness = this->funcionFitness(constanteMagica);
}

Matriz::Matriz(int tama)
{
    this->tamanno = tama;
     QList<int> filas;
     filas.append(2);
     filas.append(7);
     filas.append(6);
     this->matrizDatos.append(filas);

     QList<int> filas2;
     filas2.append(9);
     filas2.append(5);
     filas2.append(1);
     this->matrizDatos.append(filas2);

     QList<int> filas3;
     filas3.append(4);
     filas3.append(3);
     filas3.append(8);
     this->matrizDatos.append(filas3);
}

void Matriz::imprimir()
{
    int t = this->getTamanno();
    for(int i = 0;i<t;i++)
    {
        //Controla las columnas
        for(int j = 0;j<t;j++)
        {
            cout<<this->matrizDatos.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
}



int Matriz::getTamanno() const
{
    return tamanno;
}
int Matriz::funcionFitness(int numeroMagico)
{
    int score = 0;
        //Saca el score de las filas
    int resul;
        for(int i =0;i<this->tamanno;i++)
        {
            resul = 0;
            for(int j =0;j<this->tamanno;j++)
            {
               resul += this->matrizDatos.at(i).at(j);
            }
            if(numeroMagico == resul)
            {
                score++;
            }
        }


        //Saca el score de las columnas

        for(int i =0;i<this->tamanno;i++)
        {
             resul = 0;
            for(int j =0;j<this->tamanno;j++)
            {
               resul += this->matrizDatos.at(j).at(i);
            }
            if(numeroMagico == resul)
            {
                score++;
            }
        }

        //Saca el score de las diagonales
        //Diagonal
        resul = 0;
        for(int i =0;i<this->tamanno;i++)
        {
           resul += this->matrizDatos.at(i).at(i);
        }
        if(numeroMagico == resul)
        {
            score++;
        }
        //Diagonal inversa
        resul = 0;
        int temp = this->tamanno-1;
        for(int i =0;i<this->tamanno;i++)
        {

            resul += this->matrizDatos.at(i).at(temp);
            temp--;
        }
        if(numeroMagico == resul)
        {
            score++;
        }

        return score;


}

void Matriz::setTamanno(int value)
{
    tamanno = value;
}

QList<QList<int> > Matriz::getMatrizDatos() const
{
    return matrizDatos;
}

void Matriz::setMatrizDatos(const QList<QList<int> > &value)
{
    matrizDatos = value;
}
void Matriz::mutacion()
{
    int indice1 = rand()%this->tamanno;
    int indice2 = rand()%this->tamanno;

    int indice3 = rand()%this->tamanno;
    int indice4 = rand()%this->tamanno;

    int num1 = this->matrizDatos.at(indice1).at(indice2);
    int num2 = this->matrizDatos.at(indice3).at(indice4);

    this->matrizDatos[indice1][indice2] = num2;
    this->matrizDatos[indice3][indice4] = num1;


}
