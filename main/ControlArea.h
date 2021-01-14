#pragma once

#include "ArrayOperation.h"
#include "iostream"
#include <vector>

using namespace std;

class  ControlAreaBuilder;

class ControlArea
{

    int m_waterFlowDirection; //0 - from Left to Right, 1 - from Right to Left

    string m_areaNumbering;
    int m_rowNumber;
    int m_controlAreaNumber;

    vector<float> m_tempsWaterIn;
    vector<float> m_tempsWaterOut;
    vector<float> m_tempsAirIn;
    vector<float> m_tempsAirOut;

    ControlArea *nextAirAreaPointer;
    ControlArea *nextWaterAreaPointer;

    ControlArea(string areaNumbering) : m_areaNumbering(areaNumbering) {}

public:
    ControlArea() {}

    friend class ControlAreaBuilder;
    friend class ArrayOperation;
    friend class ThermalCalculation;
    friend class FileParser;
    friend class MainWindow;

    friend ostream& operator<<(ostream&  os, const ControlArea& obj);
    static ControlAreaBuilder create(string areaNumbering);

    vector<float> tempsWaterIn() const;
    void setTempsWaterIn(float tempWaterIn);
    vector<float> tempsWaterOut() const;
    void setTempsWaterOut(float tempWaterOut);
    vector<float> tempsAirIn() const;
    void setTempsAirIn(float tempAirIn);
    vector<float> tempsAirOut() const;
    void setTempsAirOut(float tempAirOut);
};
