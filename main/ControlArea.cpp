#include "ControlArea.h"
#include "ControlAreaBuilder.h"
#include "iostream"

#include <QString>

ControlAreaBuilder ControlArea::create(string areaNumbering){ return ControlAreaBuilder{areaNumbering}; }

ostream& operator<<(ostream& os, const ControlArea& obj)
{
    return os << obj.m_waterFlowDirection
              << std::endl
              << "areaDescription : " << std::endl
              << "m_areaNumbering " << obj.m_areaNumbering
              << "m_rowNumber " << obj.m_rowNumber
              << "m_controlAreaNumber " << obj.m_controlAreaNumber
              << std::endl
              << "parameters : " << std::endl
              << "m_tempWaterIn " << obj.m_tempWaterIn
              << "m_tempAirIn " << obj.m_tempAirIn;
}


