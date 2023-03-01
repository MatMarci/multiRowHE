#include <ThermalCalculation.h>

#include <math.h>

ThermalCalculation::ThermalCalculation(SimulationData *simuData, Config *config)
{
    this->simuData = simuData;
    this->config = config;
}

void ThermalCalculation::airAndWaterOutTempCalc(bool isFlowAlternately, int iteration)
{
    this->simuData->airFlow = this->config->AIR_FLOW[0];
    this->simuData->waterFlowBeforeHE = this->config->WATER_FLOW[0];
    this->simuData->airVelocityInFrontHE = this->config->AIR_VELOCITY_BEFORE_HE;

    for(auto row=0; row < (int)(this->simuData->areas.size()); row++){
       this->config->CURRENT_ROWS = row;
       for(auto area=0; area < (int)(this->simuData->areas[row].size()); area++){
           outTempCalc((this->simuData->areas[row])[area], iteration, row, area);
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
    if(row < this->config->ROWS-1){
        area.nextAirAreaPointer->setTempsAirIn(airOutTemp);
    }
    if(cArea < this->config->CONTROL_AREAS-1){
        area.nextWaterAreaPointer->setTempsWaterIn(waterOutTemp);
    }
}

float ThermalCalculation::airOutTempCalc(ControlArea &area, int iteration){
    float airInTemp = area.m_tempsAirIn[iteration];
    float airOutTemp = area.m_tempsAirOut[iteration];
    float waterInTemp = area.m_tempsWaterIn[iteration];
    float waterOutTemp = area.m_tempsWaterOut[iteration];

    float avgWaterTemp = avgWaterTempCalc(waterInTemp, waterOutTemp);
    float airParamN = airParamNCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);

    float newAirOutTemp = avgWaterTemp - ((avgWaterTemp - airInTemp)*exp(-airParamN));
    return newAirOutTemp;
}

float ThermalCalculation::waterOutTempCalc(ControlArea &area, int iteration){
    float airInTemp = area.m_tempsAirIn[iteration];
    float airOutTemp = area.m_tempsAirOut[iteration];
    float waterInTemp = area.m_tempsWaterIn[iteration];
    float waterOutTemp = area.m_tempsWaterOut[iteration];

    float internalAvgAirTemp = internalAvgAirTempCalc(area, iteration);
    float avgWaterTemp = avgWaterTempCalc(waterInTemp, waterOutTemp);
    float waterParamN = waterParamNCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);

    float newWaterOutTemp = ((1.0)/(1.0+(waterParamN/2.0)))*(((1.0-(waterParamN/2.0))*waterInTemp)+(waterParamN*internalAvgAirTemp));
    //float newWaterOutTemp = waterInTemp+waterParamN*(internalAvgAirTemp-avgWaterTemp);
    return newWaterOutTemp;
}

float ThermalCalculation::internalAvgAirTempCalc(ControlArea &area, int iteration){  //avgT_a
    float airInTemp = area.m_tempsAirIn[iteration];
    float airOutTemp = area.m_tempsAirOut[iteration];
    float waterInTemp = area.m_tempsWaterIn[iteration];
    float waterOutTemp = area.m_tempsWaterOut[iteration];

    float avgWaterTemp = avgWaterTempCalc(waterInTemp, waterOutTemp);
    float airParamN = airParamNCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);

    float avgAirTemp = avgWaterTemp - ((1.0/airParamN)*(avgWaterTemp-airInTemp)*(1.0-exp(-airParamN)));
    return avgAirTemp;
}

float ThermalCalculation::avgWaterTempCalc(float waterInTemp, float waterOutTemp){  //T_w
    return (waterInTemp+waterOutTemp)/2;
}

float ThermalCalculation::airParamNCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp){  //delta N_a
    float UCoef = UCoefCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);
    float outBareTubeArea = outBareTubeAreaCalc();
    float airMassFlow = airMassFlowCalc(airInTemp, airOutTemp);
    float avgSpecHeat = (airSpecHeatCalc(airInTemp)+airSpecHeatCalc(airOutTemp))/2.0;

    float airParamN = (UCoef * outBareTubeArea)/(airMassFlow * avgSpecHeat);
    return airParamN;
}

float ThermalCalculation::waterParamNCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp){  //delta N_w
    float UCoef = UCoefCalc(airInTemp, airOutTemp, waterInTemp, waterOutTemp);
    float outBareTubeArea = outBareTubeAreaCalc();
    float waterMassFlow = this->config->WATER_FLOW_PER_TUBE;
    float avgWaterSpecHeat = (waterSpecHeatCalc(waterInTemp)+waterSpecHeatCalc(waterOutTemp))/2.0;

    float airParamN = (UCoef * outBareTubeArea)/(waterMassFlow * avgWaterSpecHeat);
    return airParamN;
}

float ThermalCalculation::UCoefCalc(float airInTemp, float airOutTemp, float waterInTemp, float waterOutTemp){
    float reductAirHtc = reductAirHtcCalc(airInTemp, airOutTemp);
    float outBareTubeArea = outBareTubeAreaCalc();  //A_o
    float inBareTubeArea = inBareTubeAreaCalc();  //A_in
    float avgTubeArea = (inBareTubeArea+outBareTubeArea)/2.0; //A_m
    float waterHtc = waterHtcCalc(waterInTemp, waterOutTemp);

    float airUCoef = 1.0/((1.0/reductAirHtc)+((avgTubeArea/inBareTubeArea)*(this->config->TUBE_WALL_THICK/this->config->FIN_THERMAL_CONDUCT_COEF))+((outBareTubeArea/inBareTubeArea)*(1.0/waterHtc)));
    return airUCoef;
}

float ThermalCalculation::airMassFlowCalc(float airInTemp, float airOutTemp){ //delta m_a
    float avgAirDens = (airDensCalc(airInTemp)+airDensCalc(airOutTemp))/2.0;
    float airMassFlow = (this->config->AIR_FLOW_PER_AREA/3600.0) * avgAirDens;
    return airMassFlow;
}

float ThermalCalculation::reductAirHtcCalc(float airInTemp, float airOutTemp){ //h_o or alfa_o
    float airHtc = airHtcCalc(airInTemp, airOutTemp);
    float bareTubeBetweenFinsArea = bareTubeBetweenFinsAreaCalc();   // A_mf
    float finsArea = finAreaCalc(); //A_f
    float outBareTubeArea = outBareTubeAreaCalc();  //A_o
    //float finEff = this->config->FIN_EFF;
    float finEff = (-1.0*pow(10,-8)*pow(airHtc,3))+(1.0*pow(10,-5)*pow(airHtc,2))-(0.004*airHtc) + 0.9939;
    this->config->FIN_EFF = finEff;

    float reductAirHtc = airHtc * ((bareTubeBetweenFinsArea/outBareTubeArea)+(finEff*finsArea/outBareTubeArea));
    this->simuData->airReducedHTCANalPerRow[this->config->CURRENT_ROWS].push_back(reductAirHtc);
    return reductAirHtc;
}

float ThermalCalculation::outBareTubeAreaCalc(){ //A_o /A_g /A
    float outBareTubeArea = 2.0*3.14*(this->config->OUTER_TUBE_DIAM/2)*this->config->AREA_TUBE_LENGTH;
    this->simuData->airBareTubeArea = outBareTubeArea;
    return outBareTubeArea;
}

float ThermalCalculation::inBareTubeAreaCalc(){ //A_in
    float inBareTubeArea = 2*3.14*(this->config->INNER_TUBE_DIAM/2)*this->config->AREA_TUBE_LENGTH;
    return inBareTubeArea;
}

float ThermalCalculation::waterHtcCalc(float waterInTemp, float waterOutTemp){ //h_w or //alfa_w
    float waterNusseltNum;
    float waterReynoldNum = waterReynoldsNumbCalc(waterInTemp, waterOutTemp);
    float avgWaterPrandtlNum = (waterPrandtlNumbCalc(waterInTemp, waterOutTemp));

    if(waterReynoldNum < 2300){
        waterNusseltNum = laminarWaterFlowNusseltNum(waterReynoldNum, avgWaterPrandtlNum);
    } else {
        waterNusseltNum = transientAndTurbulentWaterFlowNusseltNum(waterReynoldNum, avgWaterPrandtlNum);
    }

    float avgWaterThermalConductCoef = (waterThermalConductCoefCalc(waterInTemp) + waterThermalConductCoefCalc(waterOutTemp))/2;
    //float waterHtc = waterNusseltNum * avgWaterThermalConductCoef / this->config->INNER_TUBE_DIAM;
    float waterHtc = 737;
    this->simuData->waterHTC[this->config->CURRENT_ROWS].push_back(waterHtc);
    return waterHtc;
}

float ThermalCalculation::laminarWaterFlowNusseltNum(float waterReynoldNum, float waterPrandtlNum){
    //float laminarWaterNusselt = 0.924 * (pow(waterPrandtlNum,0.3333)) * (pow(((waterReynoldNum*this->config->INNER_TUBE_DIAM)/(this->config->AREA_TUBE_LENGTH)),0.5));
    //float laminarWaterNusselt = 0.924 * (pow(waterReynoldNum,0.5))*(pow(waterPrandtlNum,0.3333));

    float lengthHE = this->config->HE_LENGTH;
    float interDim = this->config->INNER_TUBE_DIAM;

    //--------//D.Taler, Obliczenia i Badania experymentalne WC str.93 (Table 3.3)---------
     float xMax = 4.0*(0.6/interDim)*(1/(waterPrandtlNum*waterReynoldNum));
    float laminarWaterNusselt1 = -64.83*xMax + 15.8;
    //-------------------------------------------------------------------------------------

    //VDI Heat Atlas str. 694 eq(11)
    float laminarWaterNusselt2 = 0.664*(pow(waterPrandtlNum, 1/3.0))*pow(waterReynoldNum*interDim,1/2.0);

    //VDI Heat Atlas str. 694 eq(11)
    float diL = interDim/lengthHE;
    float RePrdiL = waterReynoldNum*waterPrandtlNum*diL;

    float Nu1 = 3.66;
    float Nu2 = 1.615*pow(RePrdiL,1/3.0);

    float Nu3_11 = 2.0/(1.0+(22.0*waterPrandtlNum));
    float Nu3_1 = pow(Nu3_11,1/6.0);
    float Nu3_2 = pow(RePrdiL,1/2.0);
    float Nu3 = Nu3_1*Nu3_2;

    float NuAll = pow(Nu1,3)+pow(0.7,3)+pow((Nu2-0.7),3)+pow(Nu3,3);
    float laminarWaterNusselt3 = (pow(NuAll, 1/3.0));

    float laminarWaterNusselt = laminarWaterNusselt3;

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
    this->simuData->totHeatTransferArea = totHTArea * this->config->CONTROL_AREAS * this->config->TUBES_IN_ROW * this->config->ROWS;

    float outBareTubeArea = outBareTubeAreaCalc(); // A_t - the area of the bare tubes without fins. A/At becomes 1.0 for a bare tube bank.
    //float hydarulicDim = airHydraulicDimCalc(); //equivalent diameter;
    float areaMin = (this->config->FIN_PITCH-this->config->FIN_THICK)*(this->config->TUBE_PITCH-this->config->OUTER_TUBE_DIAM)*this->config->FINS_PER_AREA;
    float hydarulicDim = airHydraulicDimCalc();
    float airMassFlow = airMassFlowCalc(airInTemp, airOutTemp);

    float reynoldsNumb_dout = airReynoldsNumb_doutCalc(airInTemp, airOutTemp);
    float reynoldsNumb_dhydr = airReynoldsNumb_dhydrCalc(airInTemp, airOutTemp);
    float prandtlNumb = (airPrandtlNumbCalc(airInTemp)+airPrandtlNumbCalc(airOutTemp))/2;

    //colburn factor
    float colburnParamMcQu = 0.0014 + ((0.2618*pow(reynoldsNumb_dout,-0.4))*(pow((totHTArea/outBareTubeArea),-0.15)));

    float a_at = (4*this->config->ROW_PITCH*this->config->TUBE_PITCH*areaMin)/(3.14*hydarulicDim*this->config->OUTER_TUBE_DIAM*(this->config->TUBE_PITCH*this->config->AREA_TUBE_LENGTH));
    float colburnParamMcQu_aAt = 0.0014 + ((0.2618*pow(reynoldsNumb_dhydr,-0.4))*(pow(a_at,-0.15)));

    float colburnParamGayWebb = 0.14 * (pow(reynoldsNumb_dout,-0.328))*(pow((this->config->TUBE_PITCH/this->config->ROW_PITCH),-0.502))*(pow((this->config->FIN_PITCH/this->config->OUTER_TUBE_DIAM),0.0312));
    this->simuData->colburnParam = colburnParamMcQu;

    float avgAirThermalCondCoef = (airThermalConductCoefCalc(airInTemp)+airThermalConductCoefCalc(airOutTemp))/2;
    float avgAirSpecHeat = (airSpecHeatCalc(airInTemp)+airSpecHeatCalc(airOutTemp))/2;

    float airHTC;
    float a;
    float b;
    //float airHtcMcQu = (colburnParamMcQu * avgAirSpecHeat *(airMassFlow/areaMin))/(pow(prandtlNumb,0.66667));
    //float airHtcMcQu_aAt = (colburnParamMcQu_aAt * avgAirSpecHeat *(airMassFlow/areaMin))/(pow(prandtlNumb,0.66667));
    //float airHtcGayWebb = (colburnParamGayWebb * avgAirSpecHeat *(airMassFlow/areaMin))/(pow(prandtlNumb,0.66667)); // Gay and Webb meet all requirements in whole range of air flow
    //airHTC = airHtcGayWebb;

    if(reynoldsNumb_dhydr < 1400){
        if(this->config->CURRENT_ROWS == 0){
            a = 1.4001;
            b = 0.3053;
        } else if(this->config->CURRENT_ROWS == 1){
            a = 0.9478;
            b = 0.3386;
        } else if(this->config->CURRENT_ROWS == 2){
            a = 1.0403;
            b = 0.3025;
        } else {
            a = 0.523;
            b = 0.4156;
        }
    } else {
        if(this->config->CURRENT_ROWS == 0){
            a = 0.4217;
            b = 0.47;
        } else if(this->config->CURRENT_ROWS == 1){
            a = 0.1305;
            b = 0.6118;
        } else if(this->config->CURRENT_ROWS == 2){
            a = 0.0923;
            b = 0.6307;
        } else {
            a = 0.1282;
            b = 0.6145;
        }
    }

    float airNuNumb = a * pow(reynoldsNumb_dhydr,b) * pow(0.7,(1/3.0));
    airHTC = (airNuNumb * avgAirThermalCondCoef)/hydarulicDim;

    this->simuData->airBasicHTCAnalPerRow[this->config->CURRENT_ROWS].push_back(airHTC);

    //air Nusselt
    this->simuData->airNusseltAnalPerRow[this->config->CURRENT_ROWS].push_back(airNuNumb);
    return airHTC;
}

float ThermalCalculation::bareTubeBetweenFinsAreaCalc(){ //A_mf
    float bareTipeBetweenFinsArea = 2*3.14*(this->config->OUTER_TUBE_DIAM/2.0)*(this->config->AREA_TUBE_LENGTH - this->config->FIN_THICK*this->config->FINS_PER_AREA);
    this->simuData->airTubeBetweenFinsArea = bareTipeBetweenFinsArea;
    return bareTipeBetweenFinsArea;
}

float ThermalCalculation::finAreaCalc(){ //A_f
    //fin area for staggered pipe layout
    //calculation from "Rozwiązywanie prostych i odwrotnych zagadnień przewodzenia ciepła" - J.Taler; P.Duda - page 101

    float OD = pow(((pow((this->config->TUBE_PITCH/2.0),2))+(pow(this->config->ROW_PITCH,2))),0.5);
    float phi = asin(this->config->TUBE_PITCH/(2*OD));
    float gamma = (3.14/2.0) - 2.0*phi;
    float AB = this->config->TUBE_PITCH * tan(gamma);
    float h_oab = this->config->TUBE_PITCH/2.0;
    float A_oab = 0.5*AB*h_oab;

    float BC = OD * tan(phi);
    float A_obc = 0.25 * BC * OD; //one side fin area, without top fin, because continoues fin and symmetry

    float oneSideFinArea = 2.0*A_oab + 4.0*A_obc;
    float finsArea = 2.0 * oneSideFinArea * this->config->FINS_PER_AREA;
    this->simuData->airFinsArea = finsArea;
    this->simuData->pipesInRow = this->config->TUBES_IN_ROW;
    return finsArea;
}

float ThermalCalculation::airReynoldsNumb_doutCalc(float airInTemp, float airOutTemp){
    float areaMin = (this->config->FIN_PITCH-this->config->FIN_THICK)*(this->config->TUBE_PITCH-this->config->OUTER_TUBE_DIAM)*this->config->FINS_PER_AREA;
    float airMassFlow = airMassFlowCalc(airInTemp, airOutTemp);
    //float airMaxVelocity = airMaxVelocityCalc(airInTemp, airOutTemp);

    float avgAirDensity = (airDensCalc(airInTemp)+airDensCalc(airOutTemp))/2;
    float avgAirKinViscoCoef = (airKinViscoCoefCalc(airInTemp) + airKinViscoCoefCalc(airOutTemp))/2;
    float avgAirDynViscoCoef = avgAirKinViscoCoef * avgAirDensity;

    float reynoldsNumb = ((airMassFlow/areaMin) * this->config->OUTER_TUBE_DIAM) / avgAirDynViscoCoef;
    this->simuData->airReynoldsNumb = reynoldsNumb;
    return reynoldsNumb;
}

float ThermalCalculation::airReynoldsNumb_dhydrCalc(float airInTemp, float airOutTemp){
    float airHydraulicDim = airHydraulicDimCalc();
    float airMaxVelocity = airMaxVelocityCalc(airInTemp, airOutTemp);
    float avgAirKinViscoCoef = (airKinViscoCoefCalc(airInTemp) + airKinViscoCoefCalc(airOutTemp))/2;

    float reynoldsNumb = (airMaxVelocity * airHydraulicDim) / avgAirKinViscoCoef;
    this->simuData->airReynoldsNumb = reynoldsNumb;
    return reynoldsNumb;
}

float ThermalCalculation::airHydraulicDimCalc(){
    float bareTubeLength = this->config->FIN_PITCH-this->config->FIN_THICK;
    float rowPitch = this->config->ROW_PITCH;
    float tubePitch = this->config->TUBE_PITCH;
    float tubeDiam = this->config->OUTER_TUBE_DIAM;

    float areaMin = bareTubeLength*(tubePitch-tubeDiam);
    float bareTubeBetweenArea = 2*3.14*(tubeDiam/2.0)*(bareTubeLength);
    float finArea = finAreaCalc()/this->config->FINS_PER_AREA;
    float volumeForOnePipe = (finArea/2)*(bareTubeLength);

    float hydraulicDim = (4*volumeForOnePipe)/(finArea + bareTubeBetweenArea);
    //float hydraulicDim2 = (4*(areaMin)*2*TUBE_PITCH)/((finAreaCalc()) + bareTubeBetweenFinsAreaCalc());
    this->simuData->airHydraulicDiam = hydraulicDim;
    return hydraulicDim;
}

float ThermalCalculation::airMaxVelocityCalc(float airInTemp, float airOutTemp){
    float minDim = airMinDimensionCalc();
    float airVelocityBeforeHE = this->config->AIR_VELOCITY_BEFORE_HE;

    float airMaxVelocity = ((this->config->FIN_PITCH*minDim)/((this->config->FIN_PITCH-this->config->FIN_THICK)*(minDim-this->config->OUTER_TUBE_DIAM)))*((((airInTemp+airOutTemp)/2)+273)/(airInTemp+273))*airVelocityBeforeHE;
    this->simuData->airMaxVelocity = airMaxVelocity;
    return airMaxVelocity;
}

float ThermalCalculation::airMinDimensionCalc(){
    float minDim = this->config->TUBE_PITCH;
    float crossRowDim = pow(((pow((this->config->TUBE_PITCH/2),2))+(pow(this->config->ROW_PITCH,2))),0.5);

    if(crossRowDim < this->config->TUBE_PITCH){
        minDim = crossRowDim;
    }
    return minDim;
}

float ThermalCalculation::waterReynoldsNumbCalc(float waterInTemp, float waterOutTemp){
    float waterFlowArea = 3.14*pow((this->config->INNER_TUBE_DIAM/2),2);
    float avgWaterDens = (waterDensCalc(waterInTemp) + waterDensCalc(waterOutTemp))/2;

    float waterVelocity = (this->config->WATER_FLOW_PER_TUBE/avgWaterDens)/waterFlowArea;
    this->simuData->waterVelocity = waterVelocity;

    float avgWaterKinViscoCoef = (waterKinViscoCoefCalc(waterInTemp) + waterKinViscoCoefCalc(waterOutTemp))/2;

    float reynoldsNumb = (waterVelocity * this->config->INNER_TUBE_DIAM) / avgWaterKinViscoCoef;
    this->simuData->waterReynoldsNumb = reynoldsNumb;
    return reynoldsNumb;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalCalculation::airHeatPowerCalc(){
    float sumTotAirHeatPower = 0;
    float sumRowAirHeatPower = 0;
    float airAreaHeatPower;
    float airTempIn;
    float airMassFlow;
    float avgAirSpecHeat;
    float airTempOut;

    for(auto row = 0; row < (int)(this->simuData->areas.size()); row++){
        sumRowAirHeatPower = 0;
        for(auto area = 0; area < (int)(this->simuData->areas[row].size()); area++){
            airAreaHeatPower = 0;
            airTempIn = this->simuData->areas[row][area].m_tempsAirIn.back();
            airTempOut = this->simuData->areas[row][area].m_tempsAirOut.back();
            airMassFlow = airMassFlowCalc(airTempIn, airTempOut);
            avgAirSpecHeat = (airSpecHeatCalc(airTempIn)+airSpecHeatCalc(airTempOut))/2;

            airAreaHeatPower = airMassFlow * avgAirSpecHeat * (airTempOut - airTempIn);

            if(this->simuData->airAreaHeatPower.find(row) == this->simuData->airAreaHeatPower.end()){
                vector<float> rowAreasHeatPower;
                rowAreasHeatPower.push_back(airAreaHeatPower);
                (this->simuData->airAreaHeatPower)[row] = rowAreasHeatPower;
            } else {
                (this->simuData->airAreaHeatPower[row]).push_back(airAreaHeatPower);
            }

            sumRowAirHeatPower += airAreaHeatPower;
        }
        this->simuData->sumRowAirHeatPower.push_back(sumRowAirHeatPower * this->config->TUBES_IN_ROW);
        sumTotAirHeatPower += sumRowAirHeatPower;
    }
    this->simuData->sumTotalAirHeatPower = sumTotAirHeatPower * this->config->TUBES_IN_ROW;
}

void ThermalCalculation::waterHeatPowerCalc(){
    float waterHeatPower = 0;
    float waterHeatPowerSum = 0;
    float avgWaterSpecHeat;
    float waterTempIn;
    float waterTempOut;
    float waterMassFlow = this->config->WATER_FLOW_PER_TUBE;

    for(int i=0; i<this->config->ROWS; i++){
        waterTempIn = this->simuData->areas[i][0].m_tempsWaterIn.back();
        waterTempOut = this->simuData->areas[i][this->config->CONTROL_AREAS-1].m_tempsWaterOut[0];
        avgWaterSpecHeat = (waterSpecHeatCalc(waterTempIn)+waterSpecHeatCalc(waterTempOut))/2;
        waterHeatPower = waterMassFlow * avgWaterSpecHeat * (waterTempIn - waterTempOut);

        if(waterHeatPower < 0){
            waterHeatPower = -waterHeatPower;
        }
        waterHeatPowerSum += waterHeatPower;
    }
    this->simuData->waterHeatPower = waterHeatPowerSum * this->config->TUBES_IN_ROW;
}

//// param calc/////////////////////////////////////////////////////////////////////////////////////////
float ThermalCalculation::airPrandtlNumbCalc(float airTemp){ //Pr_a
    float a = 0.68191738;
    float b = 0.019203016;
    float c = 88.015832;

    float airPrandtlNumb = a + b*exp(-airTemp/c);
    this->simuData->airPrandtlNumb = airPrandtlNumb;
    return airPrandtlNumb; //[-]
}

float ThermalCalculation::waterPrandtlNumbCalc(float waterTemp){ //Pr_w
    float a = 8.3767426;
    float b = 19.294246;
    float c = 5.003316;
    float d = 92.381401;

    float waterPrandtlNumb = a*exp(-waterTemp/b) + c*exp(-waterTemp/d);
    this->simuData->waterPrandtlNumb = waterPrandtlNumb;
    return waterPrandtlNumb; //[-]
}

float ThermalCalculation::waterPrandtlNumbCalc(float waterTempIn, float waterTempOut){ //Pr_w
    float avgTemp = (waterTempIn+waterTempOut)/2.0;
    float specHeat = waterSpecHeatCalc(avgTemp);
    float dynamicViscosity = waterKinViscoCoefCalc(avgTemp)*waterDensCalc(avgTemp);
    float thermalConduct = waterThermalConductCoefCalc(avgTemp);

    float waterPrandtlNumb = specHeat*dynamicViscosity/thermalConduct;
    this->simuData->waterPrandtlNumb = waterPrandtlNumb;
    return waterPrandtlNumb; //[-]
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























