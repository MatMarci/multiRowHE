#include <Chart.h>

// class to create chart for further extension
Chart::Chart(SimulationData *simuData, Config *config)
{
    this->simuData = simuData;
    this->config = config;
}

void Chart::showChart(Ui::MainWindow *ui){
    QChart *chart = new QChart();

    QChartView *chartView = new QChartView(chart);


    QScatterSeries *series = new QScatterSeries();
    series->append(0, 6);
    series->append(2, 4);

    chart->addSeries(series);

    ui->chartArea->setWidget(chartView);
}
