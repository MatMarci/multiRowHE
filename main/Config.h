#include <vector>

#pragma once

using namespace std;

class Config{

public:
    //HE param
    float HE_LENGTH = 0.3;
    float HE_HEIGHT = 0.3;
    int ROWS = 4;
    int CONTROL_AREAS = 5;
    float TUBE_PITCH = 0.025;
    float ROW_PITCH = 0.02156;

    int TUBES_IN_ROW = 0;

    float AREA_TUBE_LENGTH;
    float FINS_PER_AREA;
    float INNER_TUBE_DIAM;

    float IS_FLOW_ALTERNATELY = true;
    float ETA_ERR = 0.00001;


    //HE tube and fin param
        //tube
    float OUTER_TUBE_DIAM = 0.001;
    float TUBE_WALL_THICK = 0.0008;

        //fin
    float FIN_PITCH = 0.003;
    float FIN_THICK = 0.00018;
    float FIN_EFF = 0.8767;
    float FIN_THERMAL_CONDUCT_COEF = 207;


    //medium param
        //air
    float AIR_TEMP_IN = 20;
    vector<float> AIR_FLOW = {800};

    float AIR_VELOCITY_BEFORE_HE;

        //water
    float WATER_TEMP_IN = 85;
    vector<float> WATER_FLOW = {1};

    float AIR_FLOW_PER_AREA;
    float WATER_FLOW_PER_ROW;
    float WATER_FLOW_PER_TUBE;


    //methods
    void setOtherInitValues();

};
