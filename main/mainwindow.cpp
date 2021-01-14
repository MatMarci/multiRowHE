#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "ControlArea.h"
#include "ControlAreaBuilder.h"
#include "ArrayOperation.h"
#include "ThermalCalculation.h"
#include "FileParser.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QTableWidget.h>
#include <SimulationData.h>
#include <ostream>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString text = ui->param1->toPlainText();
    //logic

    //config :
    bool isFlowAlternately = true;
    float eta = 0.001;
    //config

    //check if this way to initialize model provide original list from ArrayOperation class
    ArrayOperation ao;
    //ThermalCalculation tc();

    int iteration = 0;
    int simulationCount = 1; //later will be from input listAirFLow X listWaterFlow
    vector<SimulationData> simDataList;

    for(int i=0; i<simulationCount; i++){
        SimulationData *simulation = (ao.initalizeModel(isFlowAlternately));
        ThermalCalculation tc(simulation);
        iteration = 0;

        do {
            //logic to calculate next i-airtemp and i-watertemp
            ao.setInitialValues(*simulation, isFlowAlternately); //set initial value in each iteration
            tc.airAndWaterOutTempCalc(isFlowAlternately, iteration);
            iteration++;
        }
        while(iteration <= 20);
        tc.airHeatPowerCalc();
        tc.waterHeatPowerCalc();
        simDataList.push_back(*simulation);
    }

    ui->tempResults->setRowCount(10);
    ui->tempResults->setColumnCount(7);

    ui->tempResults->setSpan(0,0,1,3);
    ui->tempResults->setItem(0,0, new QTableWidgetItem("Air"));

    ui->tempResults->setItem(1,0, new QTableWidgetItem("v_before_HE"));
    ui->tempResults->setItem(1,1, (new QTableWidgetItem(QString::number(simDataList[0].airVelocityInFrontHE))));
    ui->tempResults->setItem(1,2, new QTableWidgetItem("m/s"));

    ui->tempResults->setItem(2,0, new QTableWidgetItem("v_max"));
    ui->tempResults->setItem(2,1, (new QTableWidgetItem(QString::number(simDataList[0].airMaxVelocity))));
    ui->tempResults->setItem(2,2, new QTableWidgetItem("m/s"));

    ui->tempResults->setItem(3,0, new QTableWidgetItem("Re"));
    ui->tempResults->setItem(3,1, (new QTableWidgetItem(QString::number(simDataList[0].airReynoldsNumb))));

    ui->tempResults->setItem(4,0, new QTableWidgetItem("Pr"));
    ui->tempResults->setItem(4,1, (new QTableWidgetItem(QString::number(simDataList[0].airPrandtlNumb))));

    ui->tempResults->setItem(5,0, new QTableWidgetItem("alfa_0"));
    ui->tempResults->setItem(5,1, (new QTableWidgetItem(QString::number(simDataList[0].airBasicHTC))));
    ui->tempResults->setItem(5,2, new QTableWidgetItem("W/(m.K)"));

    ui->tempResults->setItem(6,0, new QTableWidgetItem("alfa_zr"));
    ui->tempResults->setItem(6,1, (new QTableWidgetItem(QString::number(simDataList[0].airReducedHTC))));
    ui->tempResults->setItem(6,2, new QTableWidgetItem("W/(m.K)"));

    ui->tempResults->setItem(7,0, new QTableWidgetItem("Q_air"));
    ui->tempResults->setItem(7,1, (new QTableWidgetItem(QString::number(simDataList[0].airHeatPower))));
    ui->tempResults->setItem(7,2, new QTableWidgetItem("W"));


    ui->tempResults->setSpan(0,4,1,3);
    ui->tempResults->setItem(0,4, new QTableWidgetItem("Water"));

    ui->tempResults->setItem(1,4, new QTableWidgetItem("v"));
    ui->tempResults->setItem(1,5, (new QTableWidgetItem(QString::number(simDataList[0].waterVelocity))));
    ui->tempResults->setItem(1,6, new QTableWidgetItem("m/s"));

    ui->tempResults->setItem(2,4, new QTableWidgetItem("Re"));
    ui->tempResults->setItem(2,5, (new QTableWidgetItem(QString::number(simDataList[0].waterReynoldsNumb))));

    ui->tempResults->setItem(3,4, new QTableWidgetItem("Pr"));
    ui->tempResults->setItem(3,5, (new QTableWidgetItem(QString::number(simDataList[0].waterPrandtlNumb))));

    ui->tempResults->setItem(4,4, new QTableWidgetItem("alfa"));
    ui->tempResults->setItem(4,5, (new QTableWidgetItem(QString::number(simDataList[0].waterHTC))));
    ui->tempResults->setItem(4,6, new QTableWidgetItem("W/(m.K)"));

    ui->tempResults->setItem(5,4, new QTableWidgetItem("Q_water"));
    ui->tempResults->setItem(5,5, (new QTableWidgetItem(QString::number(simDataList[0].waterHeatPower))));
    ui->tempResults->setItem(5,6, new QTableWidgetItem("W"));

    /*QFile file("C:/Users/Dell/Documents/Repositories/multiRowHE_cpp/multiRowHE/programFiles/testResult.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);

        FileParser fp;
        QString csvText = fp.prepareFile(*areas);
        qDebug() << csvText;

        stream << csvText;

        file.close();
        qDebug() << "Writing finished";
    }*/

    // -- logic
    //ui->results->setText(txt);
}
