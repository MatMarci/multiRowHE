#include "ThermalCalculation.h"

#include <math.h>
#include <qDebug>

const int ROWS = 4-1; //0,1,2,3
const int CONTROL_AREAS = 5-1; //areas in one row, 0,1,2,3,4

//params - later complete in Config file and collect from GUI
const float HE_TUBE_LENGTH = 0.3; //he HeatExchanger
const float HE_TUBE_HEIGHT = 0.3;
const int AREAS_PER_TUBE = 5;
const int TUBES_IN_ROW = 13;
const float AREA_TUBE_LENGTH = HE_TUBE_LENGTH/AREAS_PER_TUBE; //he HeatExchanger
const float WALL_TUBE_THICK = 0.00028;
const float FIN_THICK = 0.00018;
const float FIN_PITCH = 0.003;
const float FINS_PER_AREA = AREA_TUBE_LENGTH/FIN_PITCH;
const float DIM_OUTER_TUBE = 0.008;
const float DIM_INNER_TUBE = DIM_OUTER_TUBE - (2 * WALL_TUBE_THICK);
//const float TUBE_THERMAL_CONDUCT_COEF = 0; // tube lambda coefficient
const float FIN_THERMAL_CONDUCT_COEF = 207; // fin lambda coefficient [W/mK]
const float FIN_EFF = 0.8765;
const float TUBE_PITCH = 0.025; //m
const float ROW_PITCH = 0.02165; //m
const float AIR_FLOW = 243.0; //m3/h
const float AIR_VELOCITY_BEFORE_HE = (AIR_FLOW/3600)/(HE_TUBE_HEIGHT*HE_TUBE_LENGTH); //m/s
const float AIR_FLOW_PER_AREA = AIR_FLOW / AREAS_PER_TUBE / TUBES_IN_ROW; //m3/h
const float WATER_FLOW = 1.0; //kg/s
const float WATER_FLOW_PER_ROW = WATER_FLOW/(ROWS+1); //kg/s
const float WATER_FLOW_PER_TUBE = WATER_FLOW_PER_ROW/TUBES_IN_ROW; //kg/s

void ThermalCalculation::airAndWaterOutTempCalc(map<int, vector<ControlArea>> &areas, bool isFlowAlternately, int iteration)
{

    for(auto row=0; row < (int)(areas.size()); row++){
        //if(row == 0 || row % 2 == 0 || !isFlowAlternately){
            for(auto area=0; area < (int)(areas[row].size()); area++){
                outTempCalc((areas[row])[area], iteration, row, area);
        //    }
       //// } else if((row == 1 || row % 2 != 0) && isFlowAlternately){
       //     for(auto area=CONTROL_AREAS; area >=0; area--){
       //         outTempCalc((areas[row])[area], iteration, row, area);
       //     }
        }
    }
}

void ThermalCalculation::outTempCalc(ControlArea &area, int iteration, int row, int cArea){
    float airInTemp = area.m_tempsAirIn[iteration];
    float waterInTemp = area.m_tempsWaterIn[iteration];
    if(iteration == 0){
        area.setTempsAirOut(airInTemp);
        area.setTempsWaterOut(waterInTemp);
    }

    //logic to transform temp
    float airOutTemp = airOutTempCalc(area, iteration);
    area.m_tempsAirOut[iteration] = airOutTemp; //set T_a_out(i)
    area.setTempsAirOut(airOutTemp); //set T_a_out(i+1)

    float waterOutTemp = waterOutTempCalc(area, iteration);
    area.m_tempsWaterOut[iteration] = waterOutTemp; //set T_w_out(i)
    area.setTempsWaterOut(waterOutTemp); //set T_w_out(i+1)

    // set next pointer temps
    if(row < ROWS){
        area.nextAirAreaPointer->setTempsAirIn(airOutTemp);
    }
    if(cArea < CONTROL_AREAS){
        area.nextWaterAreaPointer->setTempsWaterIn(waterOutTemp);
    }
}

float ThermalCalculation::airOutTempCalc(ControlArea area, int iteration){
    float airInTemp = area.m_tempsAirIn[iteration];
    float airOutTemp = area.m_tempsAirOut[iteration];
    float waterInTemp = area.m_tempsWaterIn[iteration];
    float waterOutTemp = area.m_tempsWaterOut[iteration];

    float avgWaterTemp = avgWaterTempCalc(waterInTemp, waterOutTemp);
    float airParamN = airParamNCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);

    float newAirOutTemp = avgWaterTemp - ((avgWaterTemp - airInTemp)*exp(-airParamN));
    area.setTempsAirOut(newAirOutTemp);
}

float ThermalCalculation::waterOutTempCalc(ControlArea area, int iteration){
    float airInTemp = area.m_tempsAirIn[iteration];
    float airOutTemp = area.m_tempsAirOut[iteration];
    float waterInTemp = area.m_tempsWaterIn[iteration];
    float waterOutTemp = area.m_tempsWaterOut[iteration];

    float internalAvgAirTemp = internalAvgAirTempCalc(area, iteration);
    float waterParamN = waterParamNCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);

    float newWaterOutTemp = ((1)/(1+(waterParamN/2)))*(((1-(waterParamN/2))*waterInTemp)+(waterParamN*internalAvgAirTemp));
    area.setTempsWaterOut(newWaterOutTemp);
}

float ThermalCalculation::internalAvgAirTempCalc(ControlArea &area, int iteration){  //avgT_a
    float airInTemp = area.m_tempsAirIn[iteration];
    float airOutTemp = area.m_tempsAirOut[iteration];
    float waterInTemp = area.m_tempsWaterIn[iteration];
    float waterOutTemp = area.m_tempsWaterOut[iteration];

    float avgWaterTemp = avgWaterTempCalc(waterInTemp, waterOutTemp);
    float airParamN = airParamNCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);

    float avgAirTemp = avgWaterTemp - ((1/airParamN)*(avgWaterTemp-airInTemp)*(1-exp(-airParamN)));
    return avgAirTemp;
}

float ThermalCalculation::avgWaterTempCalc(float waterInTemp, float waterOutTemp){  //T_w
    return (waterInTemp+waterOutTemp)/2;
}

float ThermalCalculation::airParamNCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp){  //delta N_a
    float UCoef = UCoefCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);
    float outBareTubeArea = outBareTubeAreaCalc();
    float airMassFlow = airMassFlowCalc(airInTemp, airOutTemp);
    float avgSpecHeat = (airSpecHeatCalc(airInTemp)+airSpecHeatCalc(airOutTemp))/2;

    float airParamN = (UCoef * outBareTubeArea)/(airMassFlow * avgSpecHeat);
    return airParamN;
}

float ThermalCalculation::waterParamNCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp){  //delta N_w
    float UCoef = UCoefCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);
    float outBareTubeArea = outBareTubeAreaCalc();
    float waterMassFlow = WATER_FLOW_PER_TUBE;
    float avgWaterSpecHeat = (waterSpecHeatCalc(waterInTemp)+waterSpecHeatCalc(waterOutTemp))/2;

    float airParamN = (UCoef * outBareTubeArea)/(waterMassFlow * avgWaterSpecHeat);
    return airParamN;
}

float ThermalCalculation::UCoefCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp){
    float reductAirHtc = reductAirHtcCalc(airInTemp, airOutTemp);
    float outBareTubeArea = outBareTubeAreaCalc();  //A_o
    float inBareTubeArea = inBareTubeAreaCalc();  //A_in
    float avgTubeArea = (inBareTubeArea+outBareTubeArea)/2; //A_m
    float waterHtc = waterHtcCalc(waterInTemp, waterOutTemp);

    float airUCoef = 1/((1/reductAirHtc)+((avgTubeArea/inBareTubeArea)*(WALL_TUBE_THICK/FIN_THERMAL_CONDUCT_COEF))+((outBareTubeArea/inBareTubeArea)*(1/waterHtc)));
    return airUCoef;
}

float ThermalCalculation::airMassFlowCalc(float airInTemp, float airOutTemp){ //delta m_a
    float avgAirDens = (airDensCalc(airInTemp)+airDensCalc(airOutTemp))/2.0;
    float airMassFlow = (AIR_FLOW_PER_AREA/3600) * avgAirDens;
    return airMassFlow;
}

float ThermalCalculation::reductAirHtcCalc(float airInTemp, float airOutTemp){ //h_o or alfa_o
    float airHtc = airHtcCalc(airInTemp, airOutTemp);
    float bareTipeBetweenFinsArea = bareTubeBetweenFinsAreaCalc();   // A_mf
    float finsArea = finAreaCalc(); //A_f
    float outBareTubeArea = outBareTubeAreaCalc();  //A_o

    float reductAirHtc = airHtc * ((bareTipeBetweenFinsArea/outBareTubeArea)+(FIN_EFF*finsArea/outBareTubeArea));
    return reductAirHtc;
}

float ThermalCalculation::outBareTubeAreaCalc(){ //A_o /A_g /A
    float outBareTubeArea = 2*3.14*(DIM_OUTER_TUBE/2)*AREA_TUBE_LENGTH;
    return outBareTubeArea;
}

float ThermalCalculation::inBareTubeAreaCalc(){ //A_in
    float inBareTubeArea = 2*3.14*(DIM_INNER_TUBE/2)*AREA_TUBE_LENGTH;
    return inBareTubeArea;
}

float ThermalCalculation::waterHtcCalc(float waterInTemp, float waterOutTemp){ //h_w or //alfa_w
    float waterNusseltNum;
    float waterReynoldNum = waterReynoldsNumbCalc(waterInTemp, waterOutTemp);
    float waterPrandtlNum = waterPrandtlNumbCalc(waterInTemp, waterOutTemp);

    if(waterReynoldNum < 2300){
        waterNusseltNum = laminarWaterFlowNusseltNum(waterReynoldNum, waterPrandtlNum);
    } else {
        waterNusseltNum = transientAndTurbulentWaterFlowNusseltNum(waterReynoldNum, waterPrandtlNum);
    }

    float avgWaterThermalConductCoef = (waterThermalConductCoefCalc(waterInTemp) + waterThermalConductCoefCalc(waterOutTemp))/2;
    float waterHtc = waterNusseltNum * avgWaterThermalConductCoef / DIM_INNER_TUBE;
    return waterHtc;
}

float ThermalCalculation::laminarWaterFlowNusseltNum(float waterReynoldNum, float waterPrandtlNum){
    float laminarWaterNusselt = 0.924 * (pow(waterPrandtlNum,0.3333)) * (pow(((waterReynoldNum*DIM_INNER_TUBE)/(AREA_TUBE_LENGTH)),0.5));
    return laminarWaterNusselt;
}

float ThermalCalculation::transientAndTurbulentWaterFlowNusseltNum(float waterReynoldNum, float waterPrandtlNum){
    float x1 = 1.008;
    float x2 = 1.08;
    float x3 = 12.39;
    float waterFricCoef = waterFricCoefCalc(waterReynoldNum);

    float transientAndTurbulentWaterNusselt = 4.36 + (((waterFricCoef/8)*(waterReynoldNum-2300)*(pow(waterPrandtlNum,x1))/((x2)+(x3*pow((waterFricCoef/8),0.5)*((pow(waterPrandtlNum,2/3))-1)))));
    return transientAndTurbulentWaterNusselt;
}

float ThermalCalculation::waterFricCoefCalc(float waterReynoldNum){
    float waterFricCoef = 1/(pow((1.2776*log(waterReynoldNum)-0.406),2.246));
    return waterFricCoef;
}

float ThermalCalculation::airHtcCalc(float airInTemp, float airOutTemp){ //h_a or //alfa_a
    //(A/A_t) - the ratio of the total surface area to the area of the bone tube
    float totHTArea = bareTubeBetweenFinsAreaCalc() + finAreaCalc(); // A - total heat transfer area
    float outBareTubeArea = outBareTubeAreaCalc(); // A_t - the area of the bare tubes without fins. A/At becomes 1.0 for a bare tube bank.
    //float hydarulicDim = airHydraulicDimCalc(); //equivalent diameter;
    float hydarulicDim = airHydraulicDimCalc();

    float reynoldsNumb = airReynoldsNumbCalc(airInTemp, airOutTemp);
    float prandtlNumb = airPrandtlNumbCalc(airInTemp, airOutTemp);

    float colburnParam = 0.0014 + ((2.618*pow(reynoldsNumb,-0.4))*(pow((totHTArea/outBareTubeArea),-0.15)));
    float avgAirThermalConductCoef = (airThermalConductCoefCalc(airInTemp) + airThermalConductCoefCalc(airOutTemp))/2;

    float airHtc = (colburnParam * reynoldsNumb * pow(prandtlNumb,0.3333) * avgAirThermalConductCoef) / hydarulicDim;
    return airHtc;
}

float ThermalCalculation::bareTubeBetweenFinsAreaCalc(){ //A_mf
    float bareTipeBetweenFinsArea = 2*3.14*(DIM_OUTER_TUBE/2)*(AREA_TUBE_LENGTH - FIN_THICK*FINS_PER_AREA);
    return bareTipeBetweenFinsArea;
}

float ThermalCalculation::finAreaCalc(){ //A_f
    //fin area for staggered pipe layout
    //calculation from "Rozwiązywanie prostych i odwrotnych zagadnień przewodzenia ciepła" - J.Taler; P.Duda - page 101

    float OD = pow(((pow((TUBE_PITCH/2),2))+(pow(ROW_PITCH,2))),0.5);
    float phi = asin(TUBE_PITCH/(2.0*OD));
    float gamma = (3.14/2.0) - 2.0*phi;
    float AB = TUBE_PITCH * tan(gamma);
    float h_oab = TUBE_PITCH/2;
    float A_oab = 0.5*AB*h_oab;

    float BC = OD * tan(phi);
    float A_obc = 0.25 * BC * OD; //one side fin area, without top fin, because continoues fin and symmetry

    float finsArea = 2 * (2.0*A_oab + 4.0*A_obc) * FINS_PER_AREA;
    return finsArea;
}

float ThermalCalculation::airReynoldsNumbCalc(float airInTemp, float airOutTemp){
    float areaOfControlArea = AREA_TUBE_LENGTH * TUBE_PITCH;
    float areaOfTubeAndFins = AREA_TUBE_LENGTH*DIM_OUTER_TUBE + (TUBE_PITCH-DIM_OUTER_TUBE)*FIN_THICK*FINS_PER_AREA;

    float airFlowArea = areaOfControlArea - areaOfTubeAndFins;
    float airHydraulicDim = airHydraulicDimCalc();

    float airVelocityBeforeHE = AIR_VELOCITY_BEFORE_HE;
    float airVelocity = (AIR_FLOW_PER_AREA/3600)/airFlowArea;
    float airMaxVelocity = airMaxVelocityCalc();
    float avgAirKinViscoCoef = (airKinViscoCoefCalc(airInTemp) + airKinViscoCoefCalc(airOutTemp))/2;

    float reynoldsNumb = (airMaxVelocity * airHydraulicDim) / avgAirKinViscoCoef;
    return reynoldsNumb;
}

float ThermalCalculation::airMaxVelocityCalc(){
    float airVelocityBeforeHE = AIR_VELOCITY_BEFORE_HE;

    float airMaxVelocity = ((FIN_PITCH*TUBE_PITCH)/((FIN_PITCH-FIN_THICK)*(TUBE_PITCH-DIM_OUTER_TUBE)))*airVelocityBeforeHE;
    return airMaxVelocity;
}

float ThermalCalculation::waterReynoldsNumbCalc(float waterInTemp, float waterOutTemp){
    float waterFlowArea = 3.14*pow((DIM_INNER_TUBE/2),2);
    float avgWaterDens = (waterDensCalc(waterInTemp) + waterDensCalc(waterOutTemp))/2;

    float waterVelocity = (WATER_FLOW_PER_TUBE/avgWaterDens)/waterFlowArea;
    float avgWaterKinViscoCoef = (waterKinViscoCoefCalc(waterInTemp) + waterKinViscoCoefCalc(waterOutTemp))/2;

    float reynoldsNumb = (waterVelocity * DIM_INNER_TUBE) / avgWaterKinViscoCoef;
    return reynoldsNumb;
}

float ThermalCalculation::airPrandtlNumbCalc(float airInTemp, float airOutTemp){
    float avgAirSpecHeat = (airSpecHeatCalc(airInTemp)+airSpecHeatCalc(airOutTemp))/2;
    float avgAirKinViscoCoef = (airKinViscoCoefCalc(airInTemp) + airKinViscoCoefCalc(airOutTemp))/2;
    float avgAirThermalConductCoef = (airThermalConductCoefCalc(airInTemp) + airThermalConductCoefCalc(airOutTemp))/2;

    //float avgAirPrandtlNumb = (airPrandtlNumbCalc(airInTemp) + airPrandtlNumbCalc(airOutTemp))/2;
    //it could be used also

    float airPrandtlNumb = avgAirSpecHeat * avgAirKinViscoCoef / avgAirThermalConductCoef;
    return airPrandtlNumb;
}

float ThermalCalculation::airPrandtlNumbCalc(float airTemp){ //Pr_a
    float a = 0.68191738;
    float b = 0.019203016;
    float c = 88.015832;

    float airPrandtlNumb = a + b*exp(-airTemp/c);
    return airPrandtlNumb; //[-]
}

float ThermalCalculation::waterPrandtlNumbCalc(float waterInTemp, float waterOutTemp){
    float avgWaterSpecHeat = (waterSpecHeatCalc(waterInTemp)+waterSpecHeatCalc(waterOutTemp))/2;
    float avgWaterKinViscoCoef = (waterKinViscoCoefCalc(waterInTemp) + waterKinViscoCoefCalc(waterOutTemp))/2;
    float avgWaterThermalConductCoef = (waterThermalConductCoefCalc(waterInTemp) + waterThermalConductCoefCalc(waterOutTemp))/2;

    float waterPrandtlNumb = avgWaterSpecHeat * avgWaterKinViscoCoef / avgWaterThermalConductCoef;
    return waterPrandtlNumb;
}

float ThermalCalculation::airThermalConductCoefCalc(float airTemp){ //lambda_a
    float a = 0.024491429;
    float b = 7.3827381* pow(10.0,-5.0);

    float airThermalConductCoef = a + b*airTemp;
    return airThermalConductCoef; //[W/mK]
}

float ThermalCalculation::airSpecHeatCalc(float airTemp){ //Cp_a
    float a = 1.0063571;
    float b = 2.3809524* pow(10.0,-5.0);
    float c = 2.9761905* pow(10.0,-7.0);

    float airSpecHeat = (a + b*airTemp + c*pow(airTemp, 2))*1000.0;
    return airSpecHeat; //[J/kgK]
}

float ThermalCalculation::airKinViscoCoefCalc(float airTemp){
    float a = 1.3355893 * pow(10,-5);
    float b = 8.5479167* pow(10,-8);
    float c = 1.2366071* pow(10,-10);

    float airKinViscoCoef = a + b*airTemp + c*pow(airTemp,2);
    return airKinViscoCoef; //m^2/s
}

float ThermalCalculation::airDensCalc(float airTemp){
    float a = 0.78403458;
    float b = 0.0028794417;

    float airDens = 1.0/(a + b*airTemp);
    return airDens; //kg/m3
}

float ThermalCalculation::waterSpecHeatCalc(float waterTemp){ //Cp_a
    float a = 4.217766;
    float b = -0.00070142333;
    float c = 0.00014167198;
    float d = -0.0074136286;

    float waterSpecHeat = (a + b*waterTemp + c*pow(waterTemp,1.5) + d*pow(waterTemp,0.5))*1000.0;
    return waterSpecHeat; //[J/kgK]
}

float ThermalCalculation::waterThermalConductCoefCalc(float waterTemp){ //lambda_a
    float a = 0.56207877;
    float b = 0.0021191195;
    float c = -1.4262616* pow(10.0,-5.0);
    float d = 4.6165931* pow(10.0,-7.0);

    float waterThermalConductCoef = a + b*waterTemp + c*pow(waterTemp,2) + d*pow(waterTemp,2.5);
    return waterThermalConductCoef; //[W/mK]
}

float ThermalCalculation::waterKinViscoCoefCalc(float waterTemp){
    float a = 1.0313821;
    float b = 20.22794;
    float c = 0.75470024;
    float d = 102.63772;

    float waterKinViscoCoef = (a*exp(-waterTemp/b) + c*exp(-waterTemp/d))*pow(10.0,-6);
    return waterKinViscoCoef; //m^2/s
}

float ThermalCalculation::waterDensCalc(float waterTemp){
    float a = 1000.4619;
    float b = -0.01151384;
    float c = 1.7844825;

    float waterDens = a + b*pow(waterTemp,c);
    return waterDens; //kg/m3
}

float ThermalCalculation::airHydraulicDimCalc(){
    float areaMin = (FIN_PITCH-FIN_THICK)*(TUBE_PITCH-DIM_OUTER_TUBE)*FINS_PER_AREA;
    //float hydraulicDim2 = (4*((AREA_TUBE_LENGTH*TUBE_PITCH)-((DIM_OUTER_TUBE*AREA_TUBE_LENGTH)+((TUBE_PITCH-DIM_OUTER_TUBE)*FIN_THICK*FINS_PER_AREA))))/(2*AREA_TUBE_LENGTH + 2*(AREA_TUBE_LENGTH-FIN_THICK*FINS_PER_AREA) + (2+2*FINS_PER_AREA)*(TUBE_PITCH-DIM_OUTER_TUBE));
    //float hydraulicDim1 = DIM_OUTER_TUBE + 2*FIN_PITCH;
    //float hydraulicDim = (4*areaMin)/(finAreaCalc()+bareTubeBetweenFinsAreaCalc());

    float bareTubeBet = 2*3.14*(DIM_OUTER_TUBE/2)*(FIN_PITCH - FIN_THICK);
    float hydraulicDim3 = (4*areaMin/FINS_PER_AREA)/((finAreaCalc()/FINS_PER_AREA) + bareTubeBet);
    // it should be changed;
    return hydraulicDim3;
}























