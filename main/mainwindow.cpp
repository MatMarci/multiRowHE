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

    //int rowsTemp[4][6];
    //bool isFlowAlternately = true;

    //rows 0 is dedicated for determination of direction
    //flow from Left to Right = 0, from Right to Left = 1
    /*for(int i=0; i<4; i++){
        if(isFlowAlternately == true && ((i%2 == 0) || i == 0) && i != 1){
            rowsTemp[i][0] = 0;
        } else if(isFlowAlternately == true && ((i%2 != 0) || i ==1)){
            rowsTemp[i][0] = 1;
        } else {
            rowsTemp[i][0] = 0;
        }
    }*/
    ControlArea areas[20];

    int k = 0;
    for(int i=0; i<4; i++){
        for(int j=0; j<5; j++){
            ControlArea controlArea = ControlArea::create("1;1")
                                            .setWaterFlowDirection(0)
                                            .areaDescription()
                                                .setRowNumber(i)
                                                .setControlAreaNumber(j);
            areas[k] = controlArea;
            k++;
        }
    }

    ControlArea controlArea1 = ControlArea::create("1;1")
                                    .setWaterFlowDirection(0)
                                    .areaDescription()
                                        .setRowNumber(1)
                                        .setControlAreaNumber(1)
                                    .parameters()
                                        .setTempAirIn(20.00)
                                        .setTempWaterIn(85.00)
                                    .calculate();



    QFile file("C:/Users/Dell/Documents/Repositories/multiRowHE_cpp/multiRowHE/programFiles/testResult.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        ArrayOperation ao;
        QString txt = QString::fromStdString(ao.getParameters(controlArea1));
        stream << "Center Point: " + txt <<'\n';
        stream << "Center Point: " + txt <<'\n';
        stream << "Center Point: " + txt <<'\n';
        file.close();
        qDebug() << "Writing finished";
    }

    // -- logic
    //ui->results->setText(txt);
}
