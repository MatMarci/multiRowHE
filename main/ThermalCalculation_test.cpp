#include <ThermalCalculation.h>
#include <ThermalCalculation_test.h>

void ThermalCalculation_test::airThermalConductCoefCalc_test()
{
    float alfa0 = 2.45*pow(10,-2); //W/(m.K)
    float alfa50 = 2.82*pow(10,-2);
    float alfa100 = 3.19*pow(10,-2);

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float alfa0Calc = tc.airThermalConductCoefCalc(0);
    float alfa50Calc = tc.airThermalConductCoefCalc(50);
    float alfa100Calc = tc.airThermalConductCoefCalc(100);

    QCOMPARE(roundf(alfa0Calc * 10000) / 10000, alfa0);
    QCOMPARE(roundf(alfa50Calc * 10000) / 10000, alfa50);
    QCOMPARE(roundf(alfa100Calc * 10000) / 10000, alfa100);
}

void ThermalCalculation_test::airSpecHeatCalc_test()
{
    float cw0 = 1006; //J/(kg.K)
    float cw50 = 1008;
    float cw100 = 1012;

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float cw0Calc = tc.airSpecHeatCalc(0);
    float cw50Calc = tc.airSpecHeatCalc(50);
    float cw100Calc = tc.airSpecHeatCalc(100);

    QCOMPARE(roundf(cw0Calc * 1) / 1, cw0);
    QCOMPARE(roundf(cw50Calc * 1) / 1, cw50);
    QCOMPARE(roundf(cw100Calc * 1) / 1, cw100);
}

void ThermalCalculation_test::airKinViscoCoefCalc_test()
{
    float mi0 = 13.36*pow(10,-6); //m^2/s
    float mi50 = 17.94*pow(10,-6);
    float mi100 = 23.14*pow(10,-6);

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float mi0Calc = tc.airKinViscoCoefCalc(0);
    float mi50Calc = tc.airKinViscoCoefCalc(50);
    float mi100Calc = tc.airKinViscoCoefCalc(100);

    QCOMPARE(roundf(mi0Calc * 100000000) / 100000000, mi0);
    QCOMPARE(roundf(mi50Calc * 100000000) / 100000000, mi50);
    QCOMPARE(roundf(mi100Calc * 100000000) / 100000000, mi100);
}

void ThermalCalculation_test::airDensCalc_test()
{
    float ro0 = 1.275; //kg/m3
    float ro50 = 1.078;
    float ro100 = 0.933;

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float ro0Calc = tc.airDensCalc(0);
    float ro50Calc = tc.airDensCalc(50);
    float ro100Calc = tc.airDensCalc(100);

    QCOMPARE(roundf(ro0Calc * 1000) / 1000, ro0);
    QCOMPARE(roundf(ro50Calc * 1000) / 1000, ro50);
    QCOMPARE(roundf(ro100Calc * 1000) / 1000, ro100);
}

void ThermalCalculation_test::airPrandtlNumbCalc_test()
{
    float pr0 = 0.701; //-
    float pr50 = 0.693;
    float pr100 = 0.688;

    SimulationData sd;
    SimulationData *sdP = &sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sdP, cfP);

    float pr0Calc = tc.airPrandtlNumbCalc(0);
    float pr50Calc = tc.airPrandtlNumbCalc(50);
    float pr100Calc = tc.airPrandtlNumbCalc(100);

    QCOMPARE(roundf(pr0Calc * 1000) / 1000, pr0);
    QCOMPARE(roundf(pr50Calc * 1000) / 1000, pr50);
    QCOMPARE(roundf(pr100Calc * 1000) / 1000, pr100);
}

void ThermalCalculation_test::waterThermalConductCoefCalc_test()
{
    float alfa0 = 56.2*pow(10,-2); //W/(m.K)
    float alfa50 = 64.1*pow(10,-2);
    float alfa100 = 67.8*pow(10,-2);

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float alfa0Calc = tc.waterThermalConductCoefCalc(0);
    float alfa50Calc = tc.waterThermalConductCoefCalc(50);
    float alfa100Calc = tc.waterThermalConductCoefCalc(100);

    QCOMPARE(roundf(alfa0Calc * 1000) / 1000, alfa0);
    QCOMPARE(roundf(alfa50Calc * 1000) / 1000, alfa50);
    QCOMPARE(roundf(alfa100Calc * 1000) / 1000, alfa100);
}

void ThermalCalculation_test::waterSpecHeatCalc_test()
{
    float cw0 = 4218; //J/(kg.K)
    float cw50 = 4180;
    float cw100 = 4215;

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float cw0Calc = tc.waterSpecHeatCalc(0);
    float cw50Calc = tc.waterSpecHeatCalc(50);
    float cw100Calc = tc.waterSpecHeatCalc(100);

    QCOMPARE(roundf(cw0Calc * 1) / 1, cw0);
    QCOMPARE(roundf(cw50Calc * 1) / 1, cw50);
    QCOMPARE(roundf(cw100Calc * 1) / 1, cw100);
}

void ThermalCalculation_test::waterKinViscoCoefCalc_test()
{
    float mi0 = 1.786*pow(10,-6); //m^2/s
    float mi50 = 0.551*pow(10,-6);
    float mi100 = 0.292*pow(10,-6);

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float mi0Calc = tc.waterKinViscoCoefCalc(0);
    float mi50Calc = tc.waterKinViscoCoefCalc(50);
    float mi100Calc = tc.waterKinViscoCoefCalc(100);

    QCOMPARE(roundf(mi0Calc * 1000000000) / 1000000000, mi0);
    QCOMPARE(roundf(mi50Calc * 1000000000) / 1000000000, mi50);
    QCOMPARE(roundf(mi100Calc * 1000000000) / 1000000000, mi100);
}

void ThermalCalculation_test::waterDensCalc_test()
{
    float ro0 = 1000.5; //kg/m3
    float ro50 = 988.1;
    float ro100 = 957.8;

    SimulationData *sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sd, cfP);

    float ro0Calc = tc.waterDensCalc(0);
    float ro50Calc = tc.waterDensCalc(50);
    float ro100Calc = tc.waterDensCalc(100);

    QCOMPARE(roundf(ro0Calc * 10) / 10, ro0);
    QCOMPARE(roundf(ro50Calc * 10) / 10, ro50);
    QCOMPARE(roundf(ro100Calc * 10) / 10, ro100);
}

void ThermalCalculation_test::waterPrandtlNumbCalc_test()
{
    float pr0 = 13.38; //-
    float pr50 = 3.54;
    float pr100 = 1.74;

    SimulationData sd;
    SimulationData *sdP = &sd;
    Config cf;
    Config *cfP = &cf;
    ThermalCalculation tc(sdP, cfP);

    float pr0Calc = tc.waterPrandtlNumbCalc(0.01);
    float pr50Calc = tc.waterPrandtlNumbCalc(50);
    float pr100Calc = tc.waterPrandtlNumbCalc(100);

    QCOMPARE(roundf(pr0Calc * 100) / 100, pr0);
    QCOMPARE(roundf(pr50Calc * 100) / 100, pr50);
    QCOMPARE(roundf(pr100Calc * 100) / 100, pr100);
}


