#include "ArrayOperation.h"
#include "ControlAreaBuilder.h"

list<ControlArea> ArrayOperation::initalizeModel(bool isFlowAlternately){
    int startArea = 0;
    int stopArea = 5;
    if(isFlowAlternately){
        startArea = 5;
        stopArea = 0;
    }

    int k = 0;
    for(int i=0; i<4; i++){
        for(int j=startArea; j<stopArea; j++){
            ControlArea controlArea = ControlArea::create("1;1")
                                            .areaDescription()
                                                .setRowNumber(i)
                                                .setControlAreaNumber(j)
                                                .setNextControlAreaRowNumber(i)
                                                .setNextControlAreaNumber(j);

            this->areas.push_back(controlArea);
            k++;
        }
    }
    this->areas.front().setTempsAirIn(20.0);
    this->areas.front().setTempsWaterIn(85.0);
    return this->areas;
}
