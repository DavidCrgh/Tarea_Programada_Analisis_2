#ifndef MATRIZ_H
#define MATRIZ_H

#include <QList>

class Matriz
{
public:
    QList<QList<int>> matrizDatos;
    int tamanno;
    int fitness;

    Matriz(int tama, QList<int> numeros,int constanteMagica);
    Matriz(int tama);
    void mutacion();
    void imprimir();
    int getTamanno() const;
    void setTamanno(int value);

    QList<QList<int> > getMatrizDatos() const;
    void setMatrizDatos(const QList<QList<int> > &value);
    int funcionFitness(int numeroMagico);

    int getFitness() const;
    void setFitness(int value);

private:

};

#endif // MATRIZ_H
