#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "hilosimulacion.h"

namespace Ui {
class VentanaPrincipal;
}

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();

    Simulacion* simulacion;
    HiloSimulacion* hiloSimulacion;

    void pintarMatriz(int n, Matriz* matriz);

private slots:
    void actualizarInterfaz();

    void resetearSimulacion();

    void cuadradoEncontrado();

    void on_botonPausa_clicked();

    void on_botonResumir_clicked();

    void on_botonDetener_clicked();


private:
    Ui::VentanaPrincipal *ui;
    bool estaCorriendo;

    void obtenerEntradas();
};

#endif // VENTANAPRINCIPAL_H
