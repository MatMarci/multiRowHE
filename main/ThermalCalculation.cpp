#include "ThermalCalculation.h"

const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4

void ThermalCalculation::airOutTempCalc(vector<ControlArea> &areas, bool isFlowAlternately)
{
    for(auto i=0; i < (int)(areas.size()); i++){

        int currentRow = areas[i].m_rowNumber;
        int currentArea = areas[i].m_controlAreaNumber;

        float airInTemp = areas[i].m_tempsAirIn[i];
        float waterInTemp = areas[i].m_tempsWaterIn[i];
        float airOutTemp;
        float waterOutTemp;

        //logic to transform temp
        airOutTemp = airInTemp + 20.0;
        waterOutTemp = waterInTemp - 30.0;

        areas[i].m_tempsAirOut[i] = airOutTemp;
        areas[i].m_tempsWaterOut[i] = waterOutTemp;
    }

}
