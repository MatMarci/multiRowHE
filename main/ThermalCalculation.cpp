#include "ThermalCalculation.h"

#include <qDebug>

const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4

void ThermalCalculation::airAndWaterOutTempCalc(map<int, vector<ControlArea>> areas, bool isFlowAlternately, int iteration)
{
    for(auto row=0; row < (int)(areas.size()); row++){
        for(auto area=0; area < (int)(areas[row].size()); area++){

            qDebug() << "----------------------------------------------------------------------------------";
            qDebug() << "----------------Current Rows-------------------------";
            qDebug() << row;
            qDebug() << area;

            float airInTemp = (areas[row])[area].m_tempsAirIn[iteration];
            qDebug() << "----------------Current Temp In-------------------------";
            qDebug() << (areas[row])[area].m_tempsAirIn[iteration];
            qDebug() << &((areas[row])[area]);
            qDebug() << (areas[row])[area].nextWaterAreaPointer;
            qDebug() << (areas[row])[area].m_tempsWaterIn[iteration];

            float waterInTemp = (areas[row])[area].m_tempsWaterIn[iteration];
            float airOutTemp;
            float waterOutTemp;

            //logic to transform temp
            airOutTemp = airInTemp + 2.0;
            waterOutTemp = waterInTemp - 3.0;

            (areas[row])[area].setTempsAirOut(airOutTemp);
            (areas[row])[area].setTempsWaterOut(waterOutTemp);

            qDebug() << "----------------Current Temp Out-------------------------";
            qDebug() << (areas[row])[area].m_tempsAirOut[iteration];
            qDebug() << (areas[row])[area].m_tempsWaterOut[iteration];

            (areas[row])[area].nextAirAreaPointer->setTempsAirIn(airOutTemp);
            (areas[row])[area].nextWaterAreaPointer->setTempsWaterIn(waterOutTemp);

            qDebug() << "----------------Next Air Rows-------------------------";
            qDebug() << (areas[row])[area].nextAirAreaPointer->m_rowNumber;
            qDebug() << (areas[row])[area].nextAirAreaPointer->m_controlAreaNumber;

            qDebug() << "----------------Next Air Temp In-------------------------";
            qDebug() << (areas[row])[area].nextAirAreaPointer->m_tempsAirIn[iteration];
            qDebug() << (areas[1])[4].m_tempsAirIn[iteration];

            qDebug() << "----------------Next Water Rows-------------------------";
            qDebug() << (areas[row])[area].nextWaterAreaPointer->m_rowNumber;
            qDebug() << (areas[row])[area].nextWaterAreaPointer->m_controlAreaNumber;

            qDebug() << "----------------Next Water Temp In-------------------------";
            qDebug() << (areas[row])[area].nextWaterAreaPointer->m_tempsWaterIn[iteration];
            qDebug() << (areas[0])[1].m_tempsWaterIn[iteration];

            qDebug() << "-----------------------------------------------------------------------";



        }
    }
}
