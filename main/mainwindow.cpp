#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "ControlArea.h"
#include "ControlAreaBuilder.h"

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

    int rowsTemp[4][6];
    bool isFlowAlternately = true;
    float tempIn = 20.00;

    //rows 0 is dedicated for determination of direction
    //flow from Left to Right = 0, from Right to Left = 1
    for(int i=0; i<4; i++){
        if(isFlowAlternately == true && ((i%2 == 0) || i == 0) && i != 1){
            rowsTemp[i][0] = 0;
        } else if(isFlowAlternately == true && ((i%2 != 0) || i ==1)){
            rowsTemp[i][0] = 1;
        } else {
            rowsTemp[i][0] = 0;
        }
   }

    for(int i=0; i<4; i++){

    }

    ControlArea controlArea1 = ControlArea::calculate("1;1")
                                    .setWaterFlowDirection(0)
                                    .areaDescription()
                                        .setRowNumber(1)
                                        .setControlAreaNumber(1)
                                    .parameters()
                                        .setTempAirIn(20.00)
                                        .setTempWaterIn(85.00);

    //controlArea1.

    //cout << "wef";
    //cout<< controlArea1;

    //QString textOut;
    for(int i=0; i<4; ++i){
        //
        //textOut = textOut + " - " + << controlArea1);
    }

    QFile file("C:/Users/Dell/Documents/Programs/programFiles/testResult.txt");
        if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
          {
              // We're going to streaming text to the file
              QTextStream stream(&file);

              stream << "Center Point: "  <<'\n';

              file.close();
              qDebug() << "Writing finished";
          }



    // -- logic
    //ui->results->setText(controlArea1);
}
