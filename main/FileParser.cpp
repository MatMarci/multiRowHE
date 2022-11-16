#include "FileParser.h"


QString FileParser::prepareFile(map<int, vector<ControlArea>> &areas){

    QString fileText = "Row, Area, TempAirIn, TempAirOut, TempWaterIn, TempWaterOut, '\n'";
    QString row;
    QString area;
    QString tempInAir;
    QString tempAirOut;
    QString tempWaterIn;
    QString tempWaterOut;

//    for(auto row=0; row < (int)(areas.size()); row++){
//        for(auto area=0; area < (int)(areas[row].size()); area++){

//            row = (areas[row])[area].m_rowNumber;
//            area = (areas[row])[area].m_controlAreaNumber;
//            tempInAir = (areas[row])[area].m_tempsAirIn[0];
//            tempAirOut = (areas[row])[area].m_tempsAirOut[0];
//            tempWaterIn = (areas[row])[area].m_tempsWaterIn[0];
//            tempWaterOut = (areas[row])[area].m_tempsWaterOut[0];

//            fileText = fileText + QString::number(row) + ", " + QString::number(area) + ", " + tempInAir + ", " + tempAirOut + ", " + tempWaterIn + ", " + tempWaterOut + ", '\n'";
//        }
//    }
    //ArrayOperation ao;
    //list<float> tempsAirIn = areas[0].tempsAirIn();
    //float test = tempsAirIn.front();
    //QString txt = QString::number(test);
    //<< "Row, Area, TempAirIn, TempAirOut, TempWaterIn, TempWaterOut" <<'\n';
    //stream << txt <<'\n';

    return fileText;
}
