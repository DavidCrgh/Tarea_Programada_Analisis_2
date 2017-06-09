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

    estaCorriendo = false;

    //Inicializacion de simulacion
    simulacion = new Simulacion();
    hiloSimulacion = new HiloSimulacion(NULL, simulacion);

    connect(hiloSimulacion, SIGNAL(triggerActualizarInterfaz()),
            this, SLOT(actualizarInterfaz()));
    connect(hiloSimulacion, SIGNAL(triggerFinalizarSimulacion()),
            this, SLOT(resetearSimulacion()));
    connect(hiloSimulacion, SIGNAL(triggerCuadradoEncontrado()),
            this, SLOT(cuadradoEncontrado()));
    //hiloEvolucion->start();
}

void VentanaPrincipal::actualizarInterfaz(){
    QString textoGeneracion = "Generacion ";
    textoGeneracion.append(QString::number(simulacion->generacion + 1));
    ui->labelGeneracion->setText(textoGeneracion);

    QString textoFitness = "Fitness Promedio: ";
    textoFitness.append(QString::number(simulacion->calcularFitnessPromedio()));
    textoFitness.append("%");
    ui->labelFitness->setText(textoFitness);
}

void VentanaPrincipal::resetearSimulacion(){
    estaCorriendo = false;
    hiloSimulacion->stop = false;
    hiloSimulacion->pause = true;
}

void VentanaPrincipal::cuadradoEncontrado(){
    pintarMatriz(simulacion->tamannoMatriz, simulacion->cuadradoMagico);
}

void VentanaPrincipal::pintarMatriz(int n, Matriz* matriz){
    delete ui->scrollAreaWidgetContents->layout();
    QVBoxLayout* layoutVertical = new QVBoxLayout();
    QTableWidget* table = new QTableWidget(n,n);

    int celdaActual;
    QString valorActual;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            celdaActual = matriz->matrizDatos.at(i).at(j);
            valorActual = QString::number(celdaActual);
            table->setItem(i, j, new QTableWidgetItem(valorActual));
        }
    }
    layoutVertical->addWidget(table);
    ui->scrollAreaWidgetContents->setLayout(layoutVertical);
}

void VentanaPrincipal::obtenerEntradas(){
    simulacion->tamannoMatriz = ui->entradaCuadrado->text().toInt();
    simulacion->probabilidadMutacion = ui->entradaMutacion->value();
    simulacion->maximoPoblacion = ui->entradaMaxPoblacion->value();
    //AQUI VA ESPERANZA DE VIDA
    simulacion->maximoGeneraciones = ui->entradaMaxGeneraciones->text().toInt();
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::on_botonPausa_clicked()
{
    hiloSimulacion->pause = true;
}

void VentanaPrincipal::on_botonResumir_clicked()
{
    if(estaCorriendo){
        hiloSimulacion->pause = false;
    } else{
        estaCorriendo = true;
        hiloSimulacion->pause = false;
        obtenerEntradas();
        hiloSimulacion->start();
    }
}

void VentanaPrincipal::on_botonDetener_clicked()
{
    hiloSimulacion->stop = true;
    estaCorriendo = false;
}
