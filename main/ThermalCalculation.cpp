#include "ThermalCalculation.h"

#include <qDebug>

const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4

void ThermalCalculation::airAndWaterOutTempCalc(map<int, vector<ControlArea>> &areas, bool isFlowAlternately, int iteration)
{
    float airInTemp;
    float waterInTemp;
    float airOutTemp;
    float waterOutTemp;

    for(auto row=0; row < (int)(areas.size()); row++){
        if(row == 0 || row % 2 == 0 || !isFlowAlternately){
            for(auto area=0; area < (int)(areas[row].size()); area++){
                airInTemp = (areas[row])[area].m_tempsAirIn[iteration];
                waterInTemp = (areas[row])[area].m_tempsWaterIn[iteration];

                //logic to transform temp
                airOutTemp = airInTemp + 2.0;
                waterOutTemp = waterInTemp - 3.0;

                (areas[row])[area].setTempsAirOut(airOutTemp);
                (areas[row])[area].setTempsWaterOut(waterOutTemp);

                if(row < ROWS){
                    (areas[row])[area].nextAirAreaPointer->setTempsAirIn(airOutTemp);
                }
                if(area < CONTROL_AREAS){
                    (areas[row])[area].nextWaterAreaPointer->setTempsWaterIn(waterOutTemp);
                }
            }
        } else if((row == 1 || row % 2 != 0) && isFlowAlternately){
            for(auto area=CONTROL_AREAS; area >=0; area--){
                airInTemp = (areas[row])[area].m_tempsAirIn[iteration];
                waterInTemp = (areas[row])[area].m_tempsWaterIn[iteration];

                //logic to transform temp
                airOutTemp = airInTemp + 2.0;
                waterOutTemp = waterInTemp - 3.0;

                (areas[row])[area].setTempsAirOut(airOutTemp);
                (areas[row])[area].setTempsWaterOut(waterOutTemp);

                if(row < ROWS){
                    (areas[row])[area].nextAirAreaPointer->setTempsAirIn(airOutTemp);
                }
                if(area > 0){
                    (areas[row])[area].nextWaterAreaPointer->setTempsWaterIn(waterOutTemp);
                }
            }
        }
    }
}
