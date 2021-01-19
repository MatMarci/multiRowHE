/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *params;
    QSplitter *splitter_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QLabel *label_38;
    QLabel *label_17;
    QLineEdit *Air_Temp_In;
    QLabel *label_15;
    QLineEdit *Air_Flows;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_6;
    QLabel *label_40;
    QLabel *label_41;
    QLineEdit *Water_Temp_In;
    QLabel *label_42;
    QLineEdit *Water_Flows;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_4;
    QLabel *label_16;
    QLabel *label;
    QLineEdit *HE_Lenght;
    QLabel *label_2;
    QLineEdit *HE_Height;
    QLabel *label_3;
    QLineEdit *Tube_Pitch;
    QLabel *label_4;
    QLineEdit *Row_Pitch;
    QLabel *label_5;
    QLineEdit *Rows;
    QLabel *label_13;
    QLineEdit *Control_Areas;
    QSplitter *splitter;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *label_19;
    QLabel *label_12;
    QComboBox *comboBox;
    QLabel *label_14;
    QLineEdit *Tube_Outer_Diameter;
    QLabel *label_18;
    QLineEdit *Tube_Wall_Thickness;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_3;
    QLabel *label_34;
    QLabel *label_36;
    QComboBox *comboBox_5;
    QLabel *label_37;
    QLineEdit *Fin_Pitch;
    QLabel *label_35;
    QLineEdit *Fin_Thickness;
    QLabel *label_39;
    QLineEdit *Fin_Efficiency;
    QWidget *general_results;
    QTableWidget *tempResults;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1016, 606);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(900, 20, 93, 28));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 40, 991, 511));
        params = new QWidget();
        params->setObjectName(QString::fromUtf8("params"));
        splitter_2 = new QSplitter(params);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(540, 10, 252, 160));
        splitter_2->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_38 = new QLabel(layoutWidget);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout_5->addWidget(label_38, 0, 0, 1, 2);

        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_5->addWidget(label_17, 1, 0, 1, 1);

        Air_Temp_In = new QLineEdit(layoutWidget);
        Air_Temp_In->setObjectName(QString::fromUtf8("Air_Temp_In"));

        gridLayout_5->addWidget(Air_Temp_In, 1, 1, 1, 1);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_5->addWidget(label_15, 2, 0, 1, 1);

        Air_Flows = new QLineEdit(layoutWidget);
        Air_Flows->setObjectName(QString::fromUtf8("Air_Flows"));

        gridLayout_5->addWidget(Air_Flows, 2, 1, 1, 1);

        splitter_2->addWidget(layoutWidget);
        layoutWidget_2 = new QWidget(splitter_2);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        gridLayout_6 = new QGridLayout(layoutWidget_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        label_40 = new QLabel(layoutWidget_2);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        gridLayout_6->addWidget(label_40, 0, 0, 1, 2);

        label_41 = new QLabel(layoutWidget_2);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_6->addWidget(label_41, 1, 0, 1, 1);

        Water_Temp_In = new QLineEdit(layoutWidget_2);
        Water_Temp_In->setObjectName(QString::fromUtf8("Water_Temp_In"));

        gridLayout_6->addWidget(Water_Temp_In, 1, 1, 1, 1);

        label_42 = new QLabel(layoutWidget_2);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_6->addWidget(label_42, 2, 0, 1, 1);

        Water_Flows = new QLineEdit(layoutWidget_2);
        Water_Flows->setObjectName(QString::fromUtf8("Water_Flows"));

        gridLayout_6->addWidget(Water_Flows, 2, 1, 1, 1);

        splitter_2->addWidget(layoutWidget_2);
        layoutWidget1 = new QWidget(params);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(21, 11, 237, 204));
        gridLayout_4 = new QGridLayout(layoutWidget1);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_16 = new QLabel(layoutWidget1);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_4->addWidget(label_16, 0, 0, 1, 2);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_4->addWidget(label, 1, 0, 1, 1);

        HE_Lenght = new QLineEdit(layoutWidget1);
        HE_Lenght->setObjectName(QString::fromUtf8("HE_Lenght"));

        gridLayout_4->addWidget(HE_Lenght, 1, 1, 1, 1);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 2, 0, 1, 1);

        HE_Height = new QLineEdit(layoutWidget1);
        HE_Height->setObjectName(QString::fromUtf8("HE_Height"));

        gridLayout_4->addWidget(HE_Height, 2, 1, 1, 1);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 3, 0, 1, 1);

        Tube_Pitch = new QLineEdit(layoutWidget1);
        Tube_Pitch->setObjectName(QString::fromUtf8("Tube_Pitch"));

        gridLayout_4->addWidget(Tube_Pitch, 3, 1, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 4, 0, 1, 1);

        Row_Pitch = new QLineEdit(layoutWidget1);
        Row_Pitch->setObjectName(QString::fromUtf8("Row_Pitch"));

        gridLayout_4->addWidget(Row_Pitch, 4, 1, 1, 1);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 5, 0, 1, 1);

        Rows = new QLineEdit(layoutWidget1);
        Rows->setObjectName(QString::fromUtf8("Rows"));

        gridLayout_4->addWidget(Rows, 5, 1, 1, 1);

        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 6, 0, 1, 1);

        Control_Areas = new QLineEdit(layoutWidget1);
        Control_Areas->setObjectName(QString::fromUtf8("Control_Areas"));

        gridLayout_4->addWidget(Control_Areas, 6, 1, 1, 1);

        splitter = new QSplitter(params);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(280, 10, 241, 253));
        splitter->setOrientation(Qt::Vertical);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(layoutWidget2);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 0, 0, 1, 2);

        label_12 = new QLabel(layoutWidget2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout->addWidget(label_12, 1, 0, 1, 1);

        comboBox = new QComboBox(layoutWidget2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 1, 1, 1, 1);

        label_14 = new QLabel(layoutWidget2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 2, 0, 1, 1);

        Tube_Outer_Diameter = new QLineEdit(layoutWidget2);
        Tube_Outer_Diameter->setObjectName(QString::fromUtf8("Tube_Outer_Diameter"));

        gridLayout->addWidget(Tube_Outer_Diameter, 2, 1, 1, 1);

        label_18 = new QLabel(layoutWidget2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout->addWidget(label_18, 3, 0, 1, 1);

        Tube_Wall_Thickness = new QLineEdit(layoutWidget2);
        Tube_Wall_Thickness->setObjectName(QString::fromUtf8("Tube_Wall_Thickness"));

        gridLayout->addWidget(Tube_Wall_Thickness, 3, 1, 1, 1);

        splitter->addWidget(layoutWidget2);
        layoutWidget3 = new QWidget(splitter);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        gridLayout_3 = new QGridLayout(layoutWidget3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_34 = new QLabel(layoutWidget3);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_3->addWidget(label_34, 0, 0, 1, 1);

        label_36 = new QLabel(layoutWidget3);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_3->addWidget(label_36, 1, 0, 1, 1);

        comboBox_5 = new QComboBox(layoutWidget3);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));

        gridLayout_3->addWidget(comboBox_5, 1, 1, 1, 1);

        label_37 = new QLabel(layoutWidget3);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_3->addWidget(label_37, 2, 0, 1, 1);

        Fin_Pitch = new QLineEdit(layoutWidget3);
        Fin_Pitch->setObjectName(QString::fromUtf8("Fin_Pitch"));

        gridLayout_3->addWidget(Fin_Pitch, 2, 1, 1, 1);

        label_35 = new QLabel(layoutWidget3);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_3->addWidget(label_35, 3, 0, 1, 1);

        Fin_Thickness = new QLineEdit(layoutWidget3);
        Fin_Thickness->setObjectName(QString::fromUtf8("Fin_Thickness"));
        Fin_Thickness->setMaxLength(32766);

        gridLayout_3->addWidget(Fin_Thickness, 3, 1, 1, 1);

        label_39 = new QLabel(layoutWidget3);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        gridLayout_3->addWidget(label_39, 4, 0, 1, 1);

        Fin_Efficiency = new QLineEdit(layoutWidget3);
        Fin_Efficiency->setObjectName(QString::fromUtf8("Fin_Efficiency"));

        gridLayout_3->addWidget(Fin_Efficiency, 4, 1, 1, 1);

        splitter->addWidget(layoutWidget3);
        tabWidget->addTab(params, QString());
        general_results = new QWidget();
        general_results->setObjectName(QString::fromUtf8("general_results"));
        tempResults = new QTableWidget(general_results);
        tempResults->setObjectName(QString::fromUtf8("tempResults"));
        tempResults->setGeometry(QRect(10, 10, 961, 461));
        tabWidget->addTab(general_results, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1016, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Calculate", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Air parameters:", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Temperature - Inlet [C]", nullptr));
        Air_Temp_In->setText(QCoreApplication::translate("MainWindow", "85", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Air Flow(s) [m3/h]", nullptr));
        Air_Flows->setText(QCoreApplication::translate("MainWindow", "80", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "Water parameters:", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "Temperature - Inlet [C]", nullptr));
        Water_Temp_In->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "Water Flow(s) [kg/s]", nullptr));
        Water_Flows->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Heat Exchanger geometrical parameters:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Length [m]", nullptr));
        HE_Lenght->setText(QCoreApplication::translate("MainWindow", "0.3", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Height [m]", nullptr));
        HE_Height->setText(QCoreApplication::translate("MainWindow", "0.3", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Tube Pitch [mm]", nullptr));
        Tube_Pitch->setText(QCoreApplication::translate("MainWindow", "25", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Row Pitch [mm]", nullptr));
        Row_Pitch->setText(QCoreApplication::translate("MainWindow", "21.56", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Rows [-]", nullptr));
        Rows->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Control Areas [-]", nullptr));
        Control_Areas->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Tube parameters:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Material", nullptr));
        comboBox->setCurrentText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Outer Diameter [mm]", nullptr));
        Tube_Outer_Diameter->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Wall Thickness [mm]", nullptr));
        Tube_Wall_Thickness->setText(QCoreApplication::translate("MainWindow", "0.8", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Fins parameters:", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "Material", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Fin Pitch [mm]", nullptr));
        Fin_Pitch->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Fin Thickness [mm]", nullptr));
        Fin_Thickness->setText(QCoreApplication::translate("MainWindow", "0.14", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Fin Efficiency [-]", nullptr));
        Fin_Efficiency->setText(QCoreApplication::translate("MainWindow", "0.8765", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(params), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(general_results), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
