#include "ArrayOperation.h"
#include "ControlAreaBuilder.h"

#include <QDebug>


const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4
const float INIT_AIR_TEMP = 20.0;
const float INIT_WATER_TEMP = 85.0;

map<int, vector<ControlArea>>* ArrayOperation::initalizeModel(bool isFlowAlternately){

    string areaName;

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
            this->areas[i] = iRowVector;
        } else if((i == 1 || ROWS%2 != 0) && isFlowAlternately){
            for(int j=CONTROL_AREAS; j>=0; j--){
                ControlArea controlArea = ControlArea::create(to_string(i) + ":" + to_string(j))
                                                .areaDescription()
                                                    .setRowNumber(i)
                                                    .setControlAreaNumber(j);
                iRowVector.push_back(controlArea);
            }
            this->areas[i] = iRowVector;
        }
    }
    setAirAndWaterFlow(isFlowAlternately);
    setInitialValues(isFlowAlternately);

    return this->areasPointer=&areas;
}

void ArrayOperation::setAirAndWaterFlow(bool isFlowAlternately){
    int count1 = 0;
    int count2 = 0;

    for(auto row = 0; row < (int)(this->areas.size()); row++){ //iterate by keys
        if(row == 0 || row % 2 == 0 || !isFlowAlternately){
            for(auto area = 0; area < (int)(this->areas[row].size()); area++){ //iterate by vectors
                if(row < ROWS){
                    ((this->areas[row])[area]).nextAirAreaPointer = &((this->areas[row+1])[area]);
                }
                if(area < CONTROL_AREAS){
                    ((this->areas[row])[area]).nextWaterAreaPointer = &((this->areas[row])[area+1]);
                }
            }
        } else if((row == 1 || row % 2 != 0) && isFlowAlternately){
            for(int area = CONTROL_AREAS; area >= 0; area--){
                if(row < ROWS){
                    ((this->areas[row])[area]).nextAirAreaPointer = &((this->areas[row+1])[area-CONTROL_AREAS+count2]);
                }
                if(area > 0){
                    ((this->areas[row])[area]).nextWaterAreaPointer = &((this->areas[row])[area-1]);
                }
                count2 = count2 + 2;
            }
        }
        count1++;
    }
}

void ArrayOperation::setInitialValues(bool isFlowAlternately){

    for(auto row = 0; row < (int)(this->areas.size()); row++){ //iterate by keys
        if(row == 0 || row % 2 == 0 || !isFlowAlternately){
            for(auto area = 0; area < (int)(this->areas[row].size()); area++){ //iterate by vectors
                if(row == 0){
                    ((this->areas[row])[area]).setTempsAirIn(INIT_AIR_TEMP);
                }
                if(area == 0){
                    ((this->areas[row])[area]).setTempsWaterIn(INIT_WATER_TEMP);
                }
            }
        } else if((row == 1 || row % 2 != 0) && isFlowAlternately){
            for(int area = CONTROL_AREAS; area >= 0; area--){
                if(row == 0){
                    ((this->areas[row])[area]).setTempsAirIn(INIT_AIR_TEMP);
                }
                if(area == CONTROL_AREAS){
                    ((this->areas[row])[area]).setTempsWaterIn(INIT_WATER_TEMP);
                }
            }

        }
    }
}
