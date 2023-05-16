#include "ArrayOperation.h"
#include "ControlAreaBuilder.h"
#include <SimulationData.h>


const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4
const float INIT_AIR_TEMP = 24.2;
const float INIT_WATER_TEMP = 62.39;

SimulationData* ArrayOperation::initalizeModel(bool isFlowAlternately){
    string areaName;
    map<int, vector<ControlArea>> areas;

    for(int i=0; i<=ROWS; i++){
        vector<ControlArea> iRowVector;

        if(i == 0 || ROWS%2 == 0 || !isFlowAlternately){
            for(int j=0; j<=CONTROL_AREAS; j++){
                ControlArea controlArea = ControlArea::create(to_string(i) + ":" + to_string(j))
                                                .areaDescription()
                                                    .setRowNumber(i)
                                                    .setControlAreaNumber(j);
                iRowVector.push_back(controlArea);
            }
            areas[i] = iRowVector;
        } else if((i == 1 || ROWS%2 != 0) && isFlowAlternately){
            for(int j=CONTROL_AREAS; j>=0; j--){
                ControlArea controlArea = ControlArea::create(to_string(i) + ":" + to_string(j))
                                                .areaDescription()
                                                    .setRowNumber(i)
                                                    .setControlAreaNumber(j);
                iRowVector.push_back(controlArea);
            }
            areas[i] = iRowVector;
        }
    }
    this->simuData.areas = areas;
    setAirAndWaterFlow(isFlowAlternately);

    return this->simuDataPointer=&simuData;
}

void ArrayOperation::setAirAndWaterFlow(bool isFlowAlternately){
    int count1 = 0;
    int count2 = 0;

    for(auto row = 0; row < (int)(this->simuData.areas.size()); row++){ //iterate by keys
        if(row == 0 || row % 2 == 0 || !isFlowAlternately){
            for(auto area = 0; area < (int)(this->simuData.areas[row].size()); area++){ //iterate by vectors
                if(row < ROWS){
                    ((this->simuData.areas[row])[area]).nextAirAreaPointer = &(this->simuData.areas[row+1])[area];
                }
                if(area < CONTROL_AREAS){
                    ((this->simuData.areas[row])[area]).nextWaterAreaPointer = &((this->simuData.areas[row])[area+1]);
                }
            }
        } else if((row == 1 || row % 2 != 0) && isFlowAlternately){
            for(int area = CONTROL_AREAS; area >= 0; area--){
                if(row < ROWS){
                    ((this->simuData.areas[row])[area]).nextAirAreaPointer = &((this->simuData.areas[row+1])[area-CONTROL_AREAS+count2]);
                }
                if(area >= 0){
                    ((this->simuData.areas[row])[area-CONTROL_AREAS+count2]).nextWaterAreaPointer = &((this->simuData.areas[row])[area-CONTROL_AREAS+count2+1]);
                }
                count2 = count2 + 2;
            }
        }
        count2 = 0;
        count1++;
    }
}

void ArrayOperation::setInitialValues(bool isFlowAlternately){

    for(auto row = 0; row < (int)(this->simuData.areas.size()); row++){ //iterate by keys
       for(auto area = 0; area < (int)(this->simuData.areas[row].size()); area++){ //iterate by vectors
          if(row == 0){
             ((this->simuData.areas[row])[area]).setTempsAirIn(INIT_AIR_TEMP);
          }
          if(area == 0){
             ((this->simuData.areas[row])[area]).setTempsWaterIn(INIT_WATER_TEMP);
          }
       }
    }
}

float ArrayOperation::avgErrorCalc(int iteration)
{
    float error = 0;
    float tempAirOutCurrent;
    float tempAirOutPrevious;

    if(iteration > 0){
        for(auto area=0; area < (int)(this->simuData.areas[3].size()); area++){
           tempAirOutCurrent = (this->simuData.areas[3])[area].m_tempsAirOut[iteration];
           tempAirOutPrevious = (this->simuData.areas[3])[area].m_tempsAirOut[iteration-1];
           error += tempAirOutCurrent - tempAirOutPrevious;
        }
        error = error/5;
    }
    if(error < 0){
        error = -error;
    } else if (iteration == 0 && error == 0){
        error = 1;
    }

    return error;
}




















