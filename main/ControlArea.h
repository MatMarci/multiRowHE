#pragma once

#include "ArrayOperation.h"
#include "iostream"
#include <QString>

using namespace std;


class  ControlAreaBuilder;
class ArrayOperation;

class ControlArea
{

private:
    int m_waterFlowDirection; //0 - from Left to Right, 1 - from Right to Left

    string m_areaNumbering;
    int m_rowNumber;
    int m_controlAreaNumber;

    int m_nextControlAreaRowNumber;
    int m_nextControlAreaNumber;
    int m_previousControlAreaRowNumber;
    int m_previousControlAreaNumber;

    float m_tempWaterIn;
    float m_tempWaterOut;
    float m_tempAirIn;
    float m_tempAirOut;

    ControlArea(string areaNumbering) : m_areaNumbering(areaNumbering) {}



public:
    ControlArea() {}

    friend class ControlAreaBuilder;
    friend class ArrayOperation;
    friend ostream& operator<<(ostream&  os, const ControlArea& obj);
    static ControlAreaBuilder create(string areaNumbering);
};
