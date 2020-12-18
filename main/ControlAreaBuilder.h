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

    ControlAreaBuilder&  init();

};
