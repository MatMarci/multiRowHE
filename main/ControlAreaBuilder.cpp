#include "ControlAreaBuilder.h"

ControlAreaBuilder&  ControlAreaBuilder::areaDescription() { return *this;}

ControlAreaBuilder&  ControlAreaBuilder::setWaterFlowDirection(int waterFlowDirection){
    controlArea.m_waterFlowDirection = waterFlowDirection;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setRowNumber(int rowNumber){
    controlArea.m_rowNumber = rowNumber;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setControlAreaNumber(int controlAreaNumber){
    controlArea.m_controlAreaNumber = controlAreaNumber;
    return *this;
}

//

ControlAreaBuilder&  ControlAreaBuilder::init(){
    float tempAirOut = 1.0;

    //controlArea.m_tempAirOut = tempAirOut;
    return *this;
}

