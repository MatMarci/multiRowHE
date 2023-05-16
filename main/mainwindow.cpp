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
#include <QScrollBar>
#include <QAbstractScrollArea>
#include <QScrollArea>
#include <QButtonGroup>
#include <ResultsProcessing.h>


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->HE_Height->setPlaceholderText("0.35");
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
        ResultsProcessing rp(simulation, config);
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
        rp.airNusseltPerRowCalc();
        rp.avgMediumsTempCalc();

        simDataList.push_back(*simulation);
    }


    // prepare general results Table
    for(int i=0; i<1; i++){

        //create main elements
        QLabel *generalTitle = new QLabel(this);
        generalTitle->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        generalTitle->setText("Simulation: " + QString::number(i+1) + "\n V_{air}: " + QString::number(simDataList[i].airFlow) + " m^3/h \n m_{water}: " + QString::number(simDataList[i].waterFlowBeforeHE) + " kg/s");
        generalTitle->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        QTableWidget *generalResults = new QTableWidget();
        generalResults->verticalScrollBar()->setDisabled(true);
        generalResults->setMinimumHeight(700);
        generalResults->setRowCount(20);
        generalResults->setColumnCount(8);

        QLabel *tempTitle = new QLabel(this);
        tempTitle->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        tempTitle->setText("Temperatures results:");
        tempTitle->setAlignment(Qt::AlignTop | Qt::AlignLeft);

        QTableWidget *tempResults = new QTableWidget();
        int tempTableRows = config->ROWS *2 + 2;
        int tempTableCol = config->CONTROL_AREAS + 4;
        tempResults->verticalScrollBar()->setDisabled(true);
        tempResults->setRowCount(tempTableRows);
        tempResults->setColumnCount(tempTableCol);
        tempResults->setMinimumHeight(tempTableRows * 43); //43j per row

        QSplitter *tabsSplitter = new QSplitter();
        tabsSplitter->setOrientation(Qt::Vertical);
        tabsSplitter->addWidget(generalTitle);
        tabsSplitter->addWidget(generalResults);
        tabsSplitter->addWidget(tempTitle);
        tabsSplitter->addWidget(tempResults);

        ui->resultsAreaScroll->setWidget(tabsSplitter);


        //prepare general table
        //air
        generalResults->setSpan(0,0,1,3);
        generalResults->setItem(0,0, new QTableWidgetItem("Air"));

        generalResults->setItem(1,0, new QTableWidgetItem("v_before_HE"));
        generalResults->setItem(1,1, (new QTableWidgetItem(QString::number(simDataList[0].airVelocityInFrontHE))));
        generalResults->setItem(1,2, new QTableWidgetItem("m/s"));

        generalResults->setItem(2,0, new QTableWidgetItem("v_max"));
        generalResults->setItem(2,1, (new QTableWidgetItem(QString::number(simDataList[0].airMaxVelocity))));
        generalResults->setItem(2,2, new QTableWidgetItem("m/s"));

        generalResults->setItem(3,0, new QTableWidgetItem("Re_avg"));
        generalResults->setItem(3,1, (new QTableWidgetItem(QString::number(simDataList[0].airReynoldsNumb))));

        generalResults->setItem(4,0, new QTableWidgetItem("Pr"));
        generalResults->setItem(4,1, (new QTableWidgetItem(QString::number(simDataList[0].airPrandtlNumb))));

        generalResults->setItem(5,0, new QTableWidgetItem("α_0,avg"));
        generalResults->setItem(5,1, (new QTableWidgetItem(QString::number(simDataList[0].airBasicHTCAnalPerRow[0].back()))));
        generalResults->setItem(5,2, new QTableWidgetItem("W/(m.K)"));

        generalResults->setItem(6,0, new QTableWidgetItem("α_zr,avg"));
        generalResults->setItem(6,1, (new QTableWidgetItem(QString::number(simDataList[0].airReducedHTCANalPerRow[0].back()))));
        generalResults->setItem(6,2, new QTableWidgetItem("W/(m.K)"));

        generalResults->setItem(7,0, new QTableWidgetItem("Nu"));
        generalResults->setItem(7,1, (new QTableWidgetItem(QString::number(simDataList[0].airNusseltNumb))));
        generalResults->setItem(7,2, new QTableWidgetItem("-"));

        generalResults->setItem(8,0, new QTableWidgetItem("Q_air,tot"));
        generalResults->setItem(8,1, (new QTableWidgetItem(QString::number(simDataList[0].sumTotalAirHeatPower))));
        generalResults->setItem(8,2, new QTableWidgetItem("W"));

        generalResults->setItem(10,0, new QTableWidgetItem("iteration"));
        generalResults->setItem(10,1, (new QTableWidgetItem(QString::number(simDataList[0].iteration))));
        generalResults->setItem(10,2, new QTableWidgetItem("-"));


        //Air per row
        generalResults->setItem(14,0, new QTableWidgetItem("R1"));
        generalResults->setItem(15,0, new QTableWidgetItem("R2"));
        generalResults->setItem(16,0, new QTableWidgetItem("R3"));
        generalResults->setItem(17,0, new QTableWidgetItem("R4"));


        //Info - analytical
        generalResults->setItem(11,0, new QTableWidgetItem("Air - analytical"));
        //Qa - title
        generalResults->setItem(12,1, new QTableWidgetItem("Q_a"));
        generalResults->setItem(13,1, new QTableWidgetItem("[W]"));
        //Qa
        generalResults->setItem(14,1, (new QTableWidgetItem(QString::number(simDataList[0].sumRowAirHeatPower[0]))));
        generalResults->setItem(15,1, (new QTableWidgetItem(QString::number(simDataList[0].sumRowAirHeatPower[1]))));
        generalResults->setItem(16,1, (new QTableWidgetItem(QString::number(simDataList[0].sumRowAirHeatPower[2]))));
        generalResults->setItem(17,1, (new QTableWidgetItem(QString::number(simDataList[0].sumRowAirHeatPower[3]))));

        //air HTC alfa - title
        generalResults->setItem(12,2, new QTableWidgetItem("α_a"));
        generalResults->setItem(13,2, new QTableWidgetItem("[W/(m^2.K]"));
        //air HTC alfa air
        generalResults->setItem(14,2, (new QTableWidgetItem(QString::number(simDataList[0].airBasicHTCAnalPerRow[0].back()))));
        generalResults->setItem(15,2, (new QTableWidgetItem(QString::number(simDataList[0].airBasicHTCAnalPerRow[1].back()))));
        generalResults->setItem(16,2, (new QTableWidgetItem(QString::number(simDataList[0].airBasicHTCAnalPerRow[2].back()))));
        generalResults->setItem(17,2, (new QTableWidgetItem(QString::number(simDataList[0].airBasicHTCAnalPerRow[3].back()))));

        //air NU - title
        generalResults->setItem(12,3, new QTableWidgetItem("Nu_a"));
        generalResults->setItem(13,3, new QTableWidgetItem("[-]"));
        //air Nu
        generalResults->setItem(14,3, (new QTableWidgetItem(QString::number(simDataList[0].airNusseltAnalPerRow[0].back()))));
        generalResults->setItem(15,3, (new QTableWidgetItem(QString::number(simDataList[0].airNusseltAnalPerRow[1].back()))));
        generalResults->setItem(16,3, (new QTableWidgetItem(QString::number(simDataList[0].airNusseltAnalPerRow[2].back()))));
        generalResults->setItem(17,3, (new QTableWidgetItem(QString::number(simDataList[0].airNusseltAnalPerRow[3].back()))));


        //Info - experimental
        generalResults->setItem(11,4, new QTableWidgetItem("Air - experimental"));
        //Qa, exp - title
        generalResults->setItem(12,4, new QTableWidgetItem("Q_a"));
        generalResults->setItem(13,4, new QTableWidgetItem("[W]"));
        //Qa, exp
        generalResults->setItem(14,4, (new QTableWidgetItem(QString::number(simDataList[0].airHeatPowersExp[0]))));
        generalResults->setItem(15,4, (new QTableWidgetItem(QString::number(simDataList[0].airHeatPowersExp[1]))));
        generalResults->setItem(16,4, (new QTableWidgetItem(QString::number(simDataList[0].airHeatPowersExp[2]))));
        generalResults->setItem(17,4, (new QTableWidgetItem(QString::number(simDataList[0].airHeatPowersExp[3]))));

        //air HTC alfa, exp - title
        generalResults->setItem(12,5, new QTableWidgetItem("α_a"));
        generalResults->setItem(13,5, new QTableWidgetItem("[W/(m^2.K]"));
        //air HTC alfa, exp
        generalResults->setItem(14,5, (new QTableWidgetItem(QString::number(simDataList[0].avgAirHTCperRow[0]))));
        generalResults->setItem(15,5, (new QTableWidgetItem(QString::number(simDataList[0].avgAirHTCperRow[1]))));
        generalResults->setItem(16,5, (new QTableWidgetItem(QString::number(simDataList[0].avgAirHTCperRow[2]))));
        generalResults->setItem(17,5, (new QTableWidgetItem(QString::number(simDataList[0].avgAirHTCperRow[3]))));

        //air NU, exp - title
        generalResults->setItem(12,6, new QTableWidgetItem("Nu_a"));
        generalResults->setItem(13,6, new QTableWidgetItem("[-]"));
        //air Nu, exp
        generalResults->setItem(14,6, (new QTableWidgetItem(QString::number(simDataList[0].avgAirNusseltNumbPerRow[0]))));
        generalResults->setItem(15,6, (new QTableWidgetItem(QString::number(simDataList[0].avgAirNusseltNumbPerRow[1]))));
        generalResults->setItem(16,6, (new QTableWidgetItem(QString::number(simDataList[0].avgAirNusseltNumbPerRow[2]))));
        generalResults->setItem(17,6, (new QTableWidgetItem(QString::number(simDataList[0].avgAirNusseltNumbPerRow[3]))));



        generalResults->setSpan(0,4,1,3);
        generalResults->setItem(0,4, new QTableWidgetItem("Water"));

        generalResults->setItem(1,4, new QTableWidgetItem("v"));
        generalResults->setItem(1,5, (new QTableWidgetItem(QString::number(simDataList[0].waterVelocity))));
        generalResults->setItem(1,6, new QTableWidgetItem("m/s"));

        generalResults->setItem(2,4, new QTableWidgetItem("Re"));
        generalResults->setItem(2,5, (new QTableWidgetItem(QString::number(simDataList[0].waterReynoldsNumb))));

        generalResults->setItem(3,4, new QTableWidgetItem("Pr"));
        generalResults->setItem(3,5, (new QTableWidgetItem(QString::number(simDataList[0].waterPrandtlNumb))));

        generalResults->setItem(4,4, new QTableWidgetItem("alfa"));
        generalResults->setItem(4,5, (new QTableWidgetItem(QString::number(simDataList[0].waterHTC[0].back()))));
        generalResults->setItem(4,6, new QTableWidgetItem("W/(m.K)"));

        generalResults->setItem(5,4, new QTableWidgetItem("Q_water"));
        generalResults->setItem(5,5, (new QTableWidgetItem(QString::number(simDataList[0].waterHeatPower))));
        generalResults->setItem(5,6, new QTableWidgetItem("W"));









        //prepare Temp Table
        int colOffset = 1;
        int rowHE = 0;
        int areaHE = 0;

        for(auto col=0; col < conf.ROWS+1; col++){
            areaHE = 0;

            for(auto row=0; row < tempTableRows; row++){

                //prepare table headers
                if(col >= 1 && row < 3){
                    if(row == 0){
                        tempResults->setSpan(row,colOffset,1,2);
                        tempResults->setItem(row, colOffset, (new QTableWidgetItem("Row: " + QString::number(rowHE+1))));
                        tempResults->item(row, colOffset)->setTextAlignment(Qt::AlignCenter);
                        tempResults->setItem(row+1, colOffset, (new QTableWidgetItem("T_water [C]")));
                        tempResults->item(row+1, colOffset)->setTextAlignment(Qt::AlignCenter);
                        tempResults->setItem(row+1, colOffset+1, (new QTableWidgetItem("T_air [C]")));
                        tempResults->item(row+1, colOffset+1)->setTextAlignment(Qt::AlignCenter);
                    }
                }

                //prepare 1st column header
                if(col == 0 && row == 1){
                    tempResults->setItem(row, col, (new QTableWidgetItem("T_air_in")));
                }

                //prepare 1st column
                if(col == 0 && (row >= 3 && row < conf.CONTROL_AREAS+3)){
                    tempResults->setItem(row, col, (new QTableWidgetItem(QString::number(conf.AIR_TEMP_IN))));
                    tempResults->item(row, col)->setBackground(QColor(255,230,230));
                    tempResults->item(row, col)->setTextAlignment(Qt::AlignCenter);
                }

                //prepare temp data
                if((col >= 1 && col < conf.ROWS+1) && (row >= 3 && row < conf.CONTROL_AREAS+3)){
                   if(rowHE == 0 || rowHE % 2 == 0 || !conf.IS_FLOW_ALTERNATELY){
                       if(row == 3){
                            tempResults->setItem(row-1, colOffset, (new QTableWidgetItem(QString::number(conf.WATER_TEMP_IN))));
                            tempResults->item(row-1, colOffset)->setBackground(QColor(255,130,0));
                            tempResults->item(row-1, colOffset)->setTextAlignment(Qt::AlignCenter);
                       }
                       tempResults->setItem(row, colOffset, (new QTableWidgetItem(QString::number(simDataList[i].areas[rowHE][areaHE].m_tempsWaterOut.back() * 1000 / 1000.0, 'g', 3))));
                       tempResults->item(row, colOffset)->setBackground(QColor(255,120+areaHE*25,0+areaHE*50));
                       tempResults->item(row, colOffset)->setTextAlignment(Qt::AlignCenter);
                   } else if((rowHE == 1 || rowHE % 2 != 0) && conf.IS_FLOW_ALTERNATELY){
                       if(row == 3){
                            tempResults->setItem(row + conf.CONTROL_AREAS, colOffset, (new QTableWidgetItem(QString::number(conf.WATER_TEMP_IN))));
                            tempResults->item(row + conf.CONTROL_AREAS, colOffset)->setBackground(QColor(255,130,0));
                            tempResults->item(row + conf.CONTROL_AREAS, colOffset)->setTextAlignment(Qt::AlignCenter);
                       }
                       tempResults->setItem(tempTableRows - row + 1, colOffset, (new QTableWidgetItem(QString::number(simDataList[i].areas[rowHE][areaHE].m_tempsWaterOut.back() * 1000 / 1000.0, 'g', 3))));
                       tempResults->item(tempTableRows - row + 1, colOffset)->setBackground(QColor(255,120+areaHE*25,0+areaHE*50));
                       tempResults->item(tempTableRows - row + 1, colOffset)->setTextAlignment(Qt::AlignCenter);
                   }
                   tempResults->setItem(row, colOffset+1, (new QTableWidgetItem(QString::number(simDataList[i].areas[rowHE][areaHE].m_tempsAirOut.back() * 1000 / 1000.0, 'g', 3))));
                   tempResults->item(row, colOffset+1)->setBackground(QColor(255,200-rowHE*20,200-rowHE*20));
                   tempResults->item(row, colOffset+1)->setTextAlignment(Qt::AlignCenter);

                   areaHE++;
               }
            }

            if(col >= 1 && col < conf.ROWS+1){
                colOffset += 2;
                rowHE++;
            }

        }

        //avg Temps
        tempResults->setItem(9,1, (new QTableWidgetItem(QString::number(simDataList[0].avgWaterTempOut[0]))));
        tempResults->setItem(9,2, (new QTableWidgetItem(QString::number(simDataList[0].avgAirTempOut[0]))));
        tempResults->setItem(9,3, (new QTableWidgetItem(QString::number(simDataList[0].avgWaterTempOut[1]))));
        tempResults->setItem(9,4, (new QTableWidgetItem(QString::number(simDataList[0].avgAirTempOut[1]))));
        tempResults->setItem(9,5, (new QTableWidgetItem(QString::number(simDataList[0].avgWaterTempOut[2]))));
        tempResults->setItem(9,6, (new QTableWidgetItem(QString::number(simDataList[0].avgAirTempOut[2]))));
        tempResults->setItem(9,7, (new QTableWidgetItem(QString::number(simDataList[0].avgWaterTempOut[3]))));
        tempResults->setItem(9,8, (new QTableWidgetItem(QString::number(simDataList[0].avgAirTempOut[3]))));


    }



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
