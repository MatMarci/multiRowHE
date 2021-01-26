#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "ControlArea.h"
#include "ControlAreaBuilder.h"
#include "ArrayOperation.h"
#include "ThermalCalculation.h"
#include "FileParser.h"

#include <Config.h>
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
    //config :
    Config conf;
    conf.HE_HEIGHT = (ui->HE_Height->text()).toFloat();
    conf.HE_LENGTH = (ui->HE_Lenght->text()).toFloat();
    conf.TUBE_PITCH = (ui->Tube_Pitch->text()).toFloat()/1000;
    conf.ROW_PITCH = (ui->Row_Pitch->text()).toFloat()/1000;
    conf.ROWS = (ui->Rows->text()).toInt();
    conf.CONTROL_AREAS = (ui->Control_Areas->text()).toInt();

    conf.OUTER_TUBE_DIAM = (ui->Tube_Outer_Diameter->text()).toFloat()/1000;
    conf.TUBE_WALL_THICK = (ui->Tube_Wall_Thickness->text()).toFloat()/1000;

    conf.FIN_PITCH = (ui->Fin_Pitch->text()).toFloat()/1000;
    conf.FIN_THICK = (ui->Fin_Thickness->text()).toFloat()/1000;
    conf.FIN_EFF = (ui->Fin_Efficiency->text()).toFloat();

    conf.AIR_TEMP_IN = (ui->Air_Temp_In->text()).toFloat();
    conf.AIR_FLOW[0] = ((ui->Air_Flows->text()).toFloat());

    conf.WATER_TEMP_IN = (ui->Water_Temp_In->text()).toFloat();
    conf.WATER_FLOW[0] = ((ui->Water_Flows->text()).toFloat());
    conf.setOtherInitValues();
    Config *config = &conf;
    //config

    int iteration = 0;
    float avgError = 1;
    int simulationCount = 1; //later will be from input listAirFLow X listWaterFlow

    ArrayOperation ao;
    vector<SimulationData> simDataList;

    for(int i=0; i<simulationCount; i++){
        SimulationData *simulation = (ao.initalizeModel(config->IS_FLOW_ALTERNATELY));
        ThermalCalculation tc(simulation, config);
        iteration = 0;

        do {
            //logic to calculate next i-airtemp and i-watertemp
            ao.setInitialValues(config->IS_FLOW_ALTERNATELY); //set initial value in each iteration
            tc.airAndWaterOutTempCalc(config->IS_FLOW_ALTERNATELY, iteration);
            avgError = ao.avgErrorCalc(iteration);
            iteration++;
        }
        while(avgError > config->ETA_ERR);
        simulation->iteration = iteration;

        tc.airHeatPowerCalc();
        tc.waterHeatPowerCalc();
        simDataList.push_back(*simulation);
    }



    // prepare Table
    ui->tempResults->setRowCount(15);
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
    ui->tempResults->setItem(7,1, (new QTableWidgetItem(QString::number(simDataList[0].sumTotalAirHeatPower))));
    ui->tempResults->setItem(7,2, new QTableWidgetItem("W"));


    ui->tempResults->setItem(9,0, new QTableWidgetItem("iteration"));
    ui->tempResults->setItem(9,1, (new QTableWidgetItem(QString::number(simDataList[0].iteration))));
    ui->tempResults->setItem(9,2, new QTableWidgetItem("-"));

    ui->tempResults->setItem(10,0, new QTableWidgetItem("j_a"));
    ui->tempResults->setItem(10,1, (new QTableWidgetItem(QString::number(simDataList[0].colburnParam))));
    ui->tempResults->setItem(10,2, new QTableWidgetItem("-"));

    ui->tempResults->setItem(11,0, new QTableWidgetItem("Nu_a"));
    ui->tempResults->setItem(11,1, (new QTableWidgetItem(QString::number(simDataList[0].airNusseltNumb))));
    ui->tempResults->setItem(11,2, new QTableWidgetItem("-"));



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


    //prepare csv to fuurther place in DB
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
