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

/*void ThermalCalculation_test::airPrandtlNumbCalc_test()
{
    float pr0 = 0.701; //-
    //float pr50 = 0.693;
    //float pr100 = 0.688;

    SimulationData *sd;
    ThermalCalculation tc(sd);

    float pr0Calc = tc.airPrandtlNumbCalc(0);
    //float pr50Calc = tc.airPrandtlNumbCalc(50);
    //float pr100Calc = tc.airPrandtlNumbCalc(100);

    QCOMPARE(roundf(pr0Calc * 1000) / 1000, pr0);
    //QCOMPARE(roundf(pr50Calc * 1000) / 1000, pr50);
    //QCOMPARE(roundf(pr100Calc * 1000) / 1000, pr100);
}*/


