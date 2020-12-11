#include "ControlAreaBuilder.h"

ControlAreaBuilder&  ControlAreaBuilder::areaDescription() { return *this;}
ControlAreaBuilder&  ControlAreaBuilder::parameters(){ return *this;}

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

ControlAreaBuilder&  ControlAreaBuilder::setNextControlAreaRowNumber(int nextControlAreaRowNumber){
    controlArea.m_nextControlAreaRowNumber = nextControlAreaRowNumber;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setNextControlAreaNumber(int nextControlAreaNumber){
    controlArea.m_nextControlAreaNumber = nextControlAreaNumber;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setPreviousControlAreaRowNumber(int previousControlAreaRowNumber){
    controlArea.m_previousControlAreaRowNumber = previousControlAreaRowNumber;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setPreviousControlAreaNumber(int previousControlAreaNumber){
    controlArea.m_previousControlAreaNumber = previousControlAreaNumber;
    return *this;
}

//

ControlAreaBuilder&  ControlAreaBuilder::setTempWaterIn(float tempWaterIn){
    controlArea.m_tempWaterIn = tempWaterIn;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setTempWaterOut(float tempWaterOut){
    controlArea.m_tempWaterOut = tempWaterOut;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setTempAirIn(float tempAirIn){
    controlArea.m_tempAirIn = tempAirIn;
    return *this;
}

ControlAreaBuilder&  ControlAreaBuilder::setTempAirOut(float tempAirOut){
    controlArea.m_tempAirOut = tempAirOut;
    return *this;
}

