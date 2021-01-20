#pragma once
#include <QtTest/QtTest>

class ThermalCalculation_test: public QObject
{
    Q_OBJECT
private slots:
    void airThermalConductCoefCalc_test();
    void airSpecHeatCalc_test();
    void airKinViscoCoefCalc_test();
    void airDensCalc_test();
    void airPrandtlNumbCalc_test();

    void waterThermalConductCoefCalc_test();
    void waterSpecHeatCalc_test();
    void waterKinViscoCoefCalc_test();
    void waterDensCalc_test();
    void waterPrandtlNumbCalc_test();
};
