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
    //void airPrandtlNumbCalc_test();
};
