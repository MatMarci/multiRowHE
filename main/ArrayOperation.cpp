#include "ArrayOperation.h"
#include "ControlAreaBuilder.h"

const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4

map<int, vector<ControlArea>> ArrayOperation::initalizeModel(bool isFlowAlternately){

    for(int i=0; i<ROWS; i++){
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
    return this->areas;
}

void ArrayOperation::setAirAndWaterFlow(bool isFlowAlternately){

    for(auto i=0; i < (int)(areas.size()); i++){ //iterate by keys
        if(i == 0 || ROWS%2 == 0 || !isFlowAlternately){
            for(auto j=0; j < (int)(areas[i].size()); j++){ //iterate by vectors
                if(i <= ROWS){
                    ((areas[i])[j]).nextAirAreaPointer = &((areas[i+1])[j]);
                }
                if(j<CONTROL_AREAS-1){
                    ((areas[i])[j]).nextWaterAreaPointer = &((areas[i])[j+1]);
                }
            }
        } else if((i == 1 || ROWS%2 != 0) && isFlowAlternately){
            for(int j=CONTROL_AREAS; j>=0; j--){
                if(i <= ROWS){
                    ((areas[i])[j]).nextAirAreaPointer = &((areas[i+1])[j]);
                }
                if(j>0){
                    ((areas[i])[j]).nextWaterAreaPointer = &((areas[i])[j-1]);
                }
            }

        }
    }
}
