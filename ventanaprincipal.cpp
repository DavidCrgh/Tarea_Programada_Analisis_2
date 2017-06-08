#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);

    //Se ponen validaciones de entradas numericas
    ui->entradaCuadrado->setValidator(new QIntValidator(this));
    ui->entradaEsperanzaVida->setValidator(new QIntValidator(this));
    ui->entradaMaxGeneraciones->setValidator(new QIntValidator(this));
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}
