#pragma once
#include "ControlArea.h"

class ControlAreaBuilder
{
    ControlArea controlArea;

public:
    ControlAreaBuilder(string areaNumbering) : controlArea(areaNumbering) {}

    operator ControlArea() const { return move(controlArea); }

    ControlAreaBuilder&  setWaterFlowDirection(int waterFlowDirection);

    ControlAreaBuilder&  areaDescription();
    ControlAreaBuilder&  setRowNumber(int rowNumber);
    ControlAreaBuilder&  setControlAreaNumber(int controlAreaNumber);

    ControlAreaBuilder&  setNextControlAreaRowNumber(int nextControlAreaRowNumber);
    ControlAreaBuilder&  setNextControlAreaNumber(int nextControlAreaNumber);
    ControlAreaBuilder&  setPreviousControlAreaRowNumber(int previousControlAreaRowNumber);
    ControlAreaBuilder&  setPreviousControlAreaNumber(int previousControlAreaNumber);

    ControlAreaBuilder&  parameters();
    ControlAreaBuilder&  setTempWaterIn(float tempWaterIn);
    ControlAreaBuilder&  setTempWaterOut(float tempWaterOut);
    ControlAreaBuilder&  setTempAirIn(float tempAirIn);
    ControlAreaBuilder&  setTempAirOut(float tempAirOut);

};
