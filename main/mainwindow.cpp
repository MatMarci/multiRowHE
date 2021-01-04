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
    map<int, vector<ControlArea>> *areas = (ao.initalizeModel(isFlowAlternately));
    ThermalCalculation tc;

    int iteration = 0;
    //do {
        //logic to calculate next i-airtemp and i-watertemp

        tc.airAndWaterOutTempCalc(*areas, isFlowAlternately, iteration);
        iteration++;

        if(iteration > 0){

        }
    //}
    //while(iteration < 5);

    QFile file("C:/Users/Dell/Documents/Repositories/multiRowHE_cpp/multiRowHE/programFiles/testResult.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);

        FileParser fp;
        QString csvText = fp.prepareFile(*areas);
        qDebug() << csvText;

        stream << csvText;

        file.close();
        qDebug() << "Writing finished";
    }

    // -- logic
    //ui->results->setText(txt);
}
