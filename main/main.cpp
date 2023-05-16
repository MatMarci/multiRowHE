#include "ThermalCalculation_test.cpp"
#include "mainwindow.h"
#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    ThermalCalculation_test test1;
    QTest::qExec(&test1, argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
