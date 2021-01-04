#include "ArrayOperation.h"
#include "ControlAreaBuilder.h"

#include <QDebug>

const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4
const float INIT_AIR_TEMP = 20.0;
const float INIT_WATER_TEMP = 85.0;

map<int, vector<ControlArea>>* ArrayOperation::initalizeModel(bool isFlowAlternately){

    for(int i=0; i<=ROWS; i++){
        vector<ControlArea> iRowVector;

        if(i == 0 || ROWS%2 == 0 || !isFlowAlternately){
            for(int j=0; j<=CONTROL_AREAS; j++){
                ControlArea controlArea = ControlArea::create("1;1")
                                                .areaDescription()
                                                    .setRowNumber(i)
                                                    .setControlAreaNumber(j);
                iRowVector.push_back(controlArea);
                this->areas[i] = iRowVector;
            }
        } else if((i == 1 || ROWS%2 != 0) && isFlowAlternately){
            for(int j=CONTROL_AREAS; j>=0; j--){
                ControlArea controlArea = ControlArea::create("1;1")
                                                .areaDescription()
                                                    .setRowNumber(i)
                                                    .setControlAreaNumber(j);
                iRowVector.push_back(controlArea);
                this->areas[i] = iRowVector;
            }
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
                qDebug() << "-------------------------------------------------------------------";
                if(row < ROWS){
                    qDebug() << "-------------Current Row--------------------------------";
                    qDebug() << row;
                    qDebug() << area;
                    qDebug() << "-------------Before assign Pointer---------------";
                    qDebug() << row+1;
                    qDebug() << CONTROL_AREAS-area;
                    qDebug() << "-------------Air Pointer---------------";
                    qDebug() << ((this->areas[row])[area]).nextAirAreaPointer;
                    qDebug() << &((this->areas[row+1])[CONTROL_AREAS-area]);
                    ((this->areas[row])[area]).nextAirAreaPointer = &((this->areas[row+1])[CONTROL_AREAS-area]);
                    qDebug() << "-------------After assign Pointer---------------";
                    qDebug() << row+1;
                    qDebug() << CONTROL_AREAS-area;
                    qDebug() << "-------------Air Pointer---------------";
                    qDebug() << ((this->areas[row])[area]).nextAirAreaPointer;
                    qDebug() << &((this->areas[row+1])[CONTROL_AREAS-area]);
                    qDebug() << &((this->areas[1])[4]);
                }
                if(area < CONTROL_AREAS-1){
                    qDebug() << "-------------Before Water Pointer---------------";
                    qDebug() << ((this->areas[row])[area]).nextWaterAreaPointer;
                    qDebug() << &((this->areas[row])[area+1]);
                    ((this->areas[row])[area]).nextWaterAreaPointer = &((this->areas[row])[area+1]);
                    qDebug() << "-------------After Water Pointer---------------";
                    qDebug() << ((this->areas[row])[area]).nextWaterAreaPointer;
                    qDebug() << &((this->areas[row])[area+1]);
                    qDebug() << &((this->areas[0])[1]);
                }
            }
        } else if((row == 1 || row % 2 != 0) && isFlowAlternately){
            for(int area = CONTROL_AREAS; area >= 0; area--){
                if(row < ROWS){
                    ((this->areas[row])[area]).nextAirAreaPointer = &((this->areas[row+1])[area-CONTROL_AREAS+count2]);
                }
                if(area > 0){
                    ((this->areas[row])[area]).nextWaterAreaPointer = &((this->areas[row])[CONTROL_AREAS-count1]);
                }
            }
        }
        count2 = count2 + 2;
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
