#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "ControlArea.h"
#include "ControlAreaBuilder.h"
#include "ArrayOperation.h"

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
    map<int, vector<ControlArea>> areas = ao.initalizeModel(isFlowAlternately);
    ao.initalizeModel(isFlowAlternately);

    int i=0;
    do {
        //logic to calculate next i-airtemp and i-watertemp

        i++;
    }
    while(false);


    QFile file("C:/Users/Dell/Documents/Repositories/multiRowHE_cpp/multiRowHE/programFiles/testResult.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        //ArrayOperation ao;
        //list<float> tempsAirIn = areas[0].tempsAirIn();
        //float test = tempsAirIn.front();
        //QString txt = QString::number(test);
        stream << "Row, Area, TempAirIn, TampAirOut, TempWaterIn, TempWaterOut" <<'\n';
        //stream << txt <<'\n';

        file.close();
        qDebug() << "Writing finished";
    }

    // -- logic
    //ui->results->setText(txt);
}
