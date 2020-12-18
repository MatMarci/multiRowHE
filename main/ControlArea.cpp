#include "ControlArea.h"
#include "ControlAreaBuilder.h"
#include "iostream"

ControlAreaBuilder ControlArea::create(string areaNumbering){ return ControlAreaBuilder{areaNumbering}; }

ostream& operator<<(ostream& os, const ControlArea& obj)
{
    return os << obj.m_waterFlowDirection
              << std::endl
              << "areaDescription : " << std::endl
              << "m_areaNumbering " << obj.m_areaNumbering
              << "m_rowNumber " << obj.m_rowNumber
              << "m_controlAreaNumber " << obj.m_controlAreaNumber;
}

vector<float> ControlArea::tempsAirIn() const
{
    return m_tempsAirIn;
}

void ControlArea::setTempsAirIn(float tempAirIn)
{
    m_tempsAirIn.push_back(tempAirIn);
}

vector<float> ControlArea::tempsAirOut() const
{
    return m_tempsAirOut;
}

void ControlArea::setTempsAirOut(float tempAirOut)
{
    m_tempsAirOut.push_back(tempAirOut);
}

vector<float> ControlArea::tempsWaterIn() const
{
    return m_tempsWaterIn;
}

void ControlArea::setTempsWaterIn(float tempWaterIn)
{
    m_tempsWaterIn.push_back(tempWaterIn);
}

vector<float> ControlArea::tempsWaterOut() const
{
    return m_tempsWaterOut;
}

void ControlArea::setTempsWaterOut(float tempWaterOut)
{
    m_tempsWaterOut.push_back(tempWaterOut);
}




