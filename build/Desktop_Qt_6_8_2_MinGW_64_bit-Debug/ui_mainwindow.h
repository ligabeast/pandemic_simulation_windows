/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAnalytics;
    QAction *actionSimulation;
    QAction *actionCompare;
    QWidget *centralwidget;
    QStackedWidget *navigation;
    QWidget *simulationPage;
    QGraphicsView *MapContainer;
    QFrame *OptionsBackground;
    QComboBox *selectModel;
    QLabel *label1;
    QLabel *label2;
    QSpinBox *inputS;
    QLabel *label3;
    QSpinBox *inputR;
    QSpinBox *inputI;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QDoubleSpinBox *inputBeta;
    QDoubleSpinBox *inputGamma;
    QPushButton *startSimulation;
    QStackedWidget *pagination;
    QWidget *sirPage;
    QLabel *label8;
    QLabel *label9;
    QDoubleSpinBox *inputDiffusionS;
    QDoubleSpinBox *inputDiffusionI;
    QDoubleSpinBox *inputDiffusionR;
    QLabel *label10;
    QLabel *label11;
    QWidget *agentPage;
    QLabel *label14;
    QDoubleSpinBox *inputAgentMoveToHotspot;
    QLabel *label15;
    QDoubleSpinBox *inputAgentArea;
    QLabel *averageDistanceText;
    QDoubleSpinBox *inputAgentCollisionRadius;
    QLabel *label16;
    QDoubleSpinBox *inputAgentMaxMobility;
    QLabel *label17;
    QDoubleSpinBox *inputAgentHotspotRadius;
    QLabel *label21;
    QPushButton *pauseButton;
    QPushButton *continueButton;
    QPushButton *stopButton;
    QDoubleSpinBox *inputDimension;
    QLabel *label7;
    QLabel *label_2;
    QWidget *progressContainer;
    QLabel *label18;
    QLabel *label19;
    QLabel *label20;
    QLabel *labelIteration;
    QProgressBar *progressBarS;
    QProgressBar *progressBarI;
    QProgressBar *progressBarR;
    QWidget *comparePage;
    QListWidget *compareList1;
    QPushButton *compareButton;
    QListWidget *compareList2;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QWidget *chartContainerCompare;
    QWidget *analyticsPage;
    QListWidget *fileList;
    QPushButton *fileSelectButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *chartContainer1;
    QGraphicsView *chartContainer2;
    QLabel *iterationLabelChart2;
    QPushButton *playPauseButton;
    QPushButton *restartButton;
    QSlider *speedSlider;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuNavigation;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1009, 1112);
        MainWindow->setMinimumSize(QSize(0, 0));
        actionAnalytics = new QAction(MainWindow);
        actionAnalytics->setObjectName("actionAnalytics");
        actionSimulation = new QAction(MainWindow);
        actionSimulation->setObjectName("actionSimulation");
        actionCompare = new QAction(MainWindow);
        actionCompare->setObjectName("actionCompare");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(1000, 1000));
        navigation = new QStackedWidget(centralwidget);
        navigation->setObjectName("navigation");
        navigation->setGeometry(QRect(0, 0, 1011, 1081));
        simulationPage = new QWidget();
        simulationPage->setObjectName("simulationPage");
        MapContainer = new QGraphicsView(simulationPage);
        MapContainer->setObjectName("MapContainer");
        MapContainer->setEnabled(true);
        MapContainer->setGeometry(QRect(0, 0, 570, 1000));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MapContainer->sizePolicy().hasHeightForWidth());
        MapContainer->setSizePolicy(sizePolicy);
        MapContainer->setMinimumSize(QSize(100, 1000));
        OptionsBackground = new QFrame(simulationPage);
        OptionsBackground->setObjectName("OptionsBackground");
        OptionsBackground->setGeometry(QRect(570, 0, 431, 1001));
        OptionsBackground->setFrameShape(QFrame::StyledPanel);
        OptionsBackground->setFrameShadow(QFrame::Raised);
        selectModel = new QComboBox(OptionsBackground);
        selectModel->addItem(QString());
        selectModel->addItem(QString());
        selectModel->setObjectName("selectModel");
        selectModel->setGeometry(QRect(40, 62, 371, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(selectModel->sizePolicy().hasHeightForWidth());
        selectModel->setSizePolicy(sizePolicy1);
        selectModel->setBaseSize(QSize(20, 20));
        selectModel->setMouseTracking(true);
        selectModel->setTabletTracking(false);
        selectModel->setContextMenuPolicy(Qt::NoContextMenu);
        selectModel->setToolTipDuration(8);
        selectModel->setLayoutDirection(Qt::LeftToRight);
        selectModel->setLocale(QLocale(QLocale::Fulah, QLocale::Senegal));
        label1 = new QLabel(OptionsBackground);
        label1->setObjectName("label1");
        label1->setGeometry(QRect(40, 30, 361, 20));
        label1->setAlignment(Qt::AlignCenter);
        label2 = new QLabel(OptionsBackground);
        label2->setObjectName("label2");
        label2->setGeometry(QRect(40, 120, 21, 30));
        inputS = new QSpinBox(OptionsBackground);
        inputS->setObjectName("inputS");
        inputS->setGeometry(QRect(60, 120, 351, 30));
        inputS->setMaximum(100000000);
        label3 = new QLabel(OptionsBackground);
        label3->setObjectName("label3");
        label3->setGeometry(QRect(40, 220, 21, 30));
        inputR = new QSpinBox(OptionsBackground);
        inputR->setObjectName("inputR");
        inputR->setGeometry(QRect(60, 220, 351, 30));
        inputR->setMaximum(100000000);
        inputI = new QSpinBox(OptionsBackground);
        inputI->setObjectName("inputI");
        inputI->setGeometry(QRect(60, 168, 351, 30));
        inputI->setMaximum(100000002);
        label4 = new QLabel(OptionsBackground);
        label4->setObjectName("label4");
        label4->setGeometry(QRect(40, 170, 21, 30));
        label5 = new QLabel(OptionsBackground);
        label5->setObjectName("label5");
        label5->setGeometry(QRect(40, 270, 101, 30));
        label6 = new QLabel(OptionsBackground);
        label6->setObjectName("label6");
        label6->setGeometry(QRect(170, 270, 91, 30));
        inputBeta = new QDoubleSpinBox(OptionsBackground);
        inputBeta->setObjectName("inputBeta");
        inputBeta->setGeometry(QRect(40, 310, 91, 30));
        inputBeta->setMaximum(1.000000000000000);
        inputBeta->setSingleStep(0.010000000000000);
        inputGamma = new QDoubleSpinBox(OptionsBackground);
        inputGamma->setObjectName("inputGamma");
        inputGamma->setGeometry(QRect(170, 310, 91, 30));
        inputGamma->setMaximum(1.000000000000000);
        inputGamma->setSingleStep(0.010000000000000);
        startSimulation = new QPushButton(OptionsBackground);
        startSimulation->setObjectName("startSimulation");
        startSimulation->setGeometry(QRect(50, 880, 321, 61));
        QFont font;
        font.setPointSize(9);
        startSimulation->setFont(font);
        pagination = new QStackedWidget(OptionsBackground);
        pagination->setObjectName("pagination");
        pagination->setGeometry(QRect(40, 430, 371, 271));
        sirPage = new QWidget();
        sirPage->setObjectName("sirPage");
        label8 = new QLabel(sirPage);
        label8->setObjectName("label8");
        label8->setGeometry(QRect(120, 10, 151, 16));
        label9 = new QLabel(sirPage);
        label9->setObjectName("label9");
        label9->setGeometry(QRect(0, 40, 31, 16));
        inputDiffusionS = new QDoubleSpinBox(sirPage);
        inputDiffusionS->setObjectName("inputDiffusionS");
        inputDiffusionS->setGeometry(QRect(0, 60, 71, 30));
        inputDiffusionS->setMaximum(100.000000000000000);
        inputDiffusionS->setSingleStep(1.000000000000000);
        inputDiffusionI = new QDoubleSpinBox(sirPage);
        inputDiffusionI->setObjectName("inputDiffusionI");
        inputDiffusionI->setGeometry(QRect(100, 60, 71, 30));
        inputDiffusionI->setMaximum(100.000000000000000);
        inputDiffusionI->setSingleStep(1.000000000000000);
        inputDiffusionR = new QDoubleSpinBox(sirPage);
        inputDiffusionR->setObjectName("inputDiffusionR");
        inputDiffusionR->setGeometry(QRect(200, 60, 71, 30));
        inputDiffusionR->setMaximum(100.000000000000000);
        inputDiffusionR->setSingleStep(1.000000000000000);
        label10 = new QLabel(sirPage);
        label10->setObjectName("label10");
        label10->setGeometry(QRect(100, 40, 31, 16));
        label11 = new QLabel(sirPage);
        label11->setObjectName("label11");
        label11->setGeometry(QRect(200, 40, 31, 16));
        pagination->addWidget(sirPage);
        agentPage = new QWidget();
        agentPage->setObjectName("agentPage");
        label14 = new QLabel(agentPage);
        label14->setObjectName("label14");
        label14->setGeometry(QRect(120, 80, 101, 30));
        inputAgentMoveToHotspot = new QDoubleSpinBox(agentPage);
        inputAgentMoveToHotspot->setObjectName("inputAgentMoveToHotspot");
        inputAgentMoveToHotspot->setGeometry(QRect(120, 110, 91, 30));
        inputAgentMoveToHotspot->setMinimum(0.000000000000000);
        inputAgentMoveToHotspot->setMaximum(1.000000000000000);
        inputAgentMoveToHotspot->setSingleStep(0.010000000000000);
        label15 = new QLabel(agentPage);
        label15->setObjectName("label15");
        label15->setGeometry(QRect(0, 10, 101, 30));
        inputAgentArea = new QDoubleSpinBox(agentPage);
        inputAgentArea->setObjectName("inputAgentArea");
        inputAgentArea->setGeometry(QRect(0, 40, 91, 31));
        inputAgentArea->setMinimum(1.000000000000000);
        inputAgentArea->setMaximum(10000.000000000000000);
        inputAgentArea->setSingleStep(1.000000000000000);
        inputAgentArea->setValue(1.000000000000000);
        averageDistanceText = new QLabel(agentPage);
        averageDistanceText->setObjectName("averageDistanceText");
        averageDistanceText->setGeometry(QRect(120, 30, 261, 41));
        averageDistanceText->setWordWrap(true);
        inputAgentCollisionRadius = new QDoubleSpinBox(agentPage);
        inputAgentCollisionRadius->setObjectName("inputAgentCollisionRadius");
        inputAgentCollisionRadius->setGeometry(QRect(0, 110, 91, 31));
        inputAgentCollisionRadius->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        inputAgentCollisionRadius->setMinimum(1.000000000000000);
        inputAgentCollisionRadius->setMaximum(10000.000000000000000);
        inputAgentCollisionRadius->setSingleStep(1.000000000000000);
        inputAgentCollisionRadius->setValue(1.000000000000000);
        label16 = new QLabel(agentPage);
        label16->setObjectName("label16");
        label16->setGeometry(QRect(0, 80, 111, 30));
        inputAgentMaxMobility = new QDoubleSpinBox(agentPage);
        inputAgentMaxMobility->setObjectName("inputAgentMaxMobility");
        inputAgentMaxMobility->setGeometry(QRect(240, 110, 91, 30));
        inputAgentMaxMobility->setFocusPolicy(Qt::WheelFocus);
        inputAgentMaxMobility->setLocale(QLocale(QLocale::German, QLocale::Belgium));
        inputAgentMaxMobility->setMinimum(0.010000000000000);
        inputAgentMaxMobility->setMaximum(100.000000000000000);
        inputAgentMaxMobility->setSingleStep(0.100000000000000);
        label17 = new QLabel(agentPage);
        label17->setObjectName("label17");
        label17->setGeometry(QRect(240, 80, 131, 30));
        label17->setFocusPolicy(Qt::WheelFocus);
        inputAgentHotspotRadius = new QDoubleSpinBox(agentPage);
        inputAgentHotspotRadius->setObjectName("inputAgentHotspotRadius");
        inputAgentHotspotRadius->setGeometry(QRect(0, 180, 91, 31));
        inputAgentHotspotRadius->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        inputAgentHotspotRadius->setDecimals(3);
        inputAgentHotspotRadius->setMinimum(0.001000000000000);
        inputAgentHotspotRadius->setMaximum(10000.000000000000000);
        inputAgentHotspotRadius->setSingleStep(0.100000000000000);
        inputAgentHotspotRadius->setValue(1.000000000000000);
        label21 = new QLabel(agentPage);
        label21->setObjectName("label21");
        label21->setGeometry(QRect(0, 150, 111, 30));
        pagination->addWidget(agentPage);
        pauseButton = new QPushButton(OptionsBackground);
        pauseButton->setObjectName("pauseButton");
        pauseButton->setGeometry(QRect(50, 880, 261, 61));
        pauseButton->setFont(font);
        continueButton = new QPushButton(OptionsBackground);
        continueButton->setObjectName("continueButton");
        continueButton->setGeometry(QRect(50, 880, 261, 61));
        continueButton->setFont(font);
        stopButton = new QPushButton(OptionsBackground);
        stopButton->setObjectName("stopButton");
        stopButton->setGeometry(QRect(310, 880, 61, 61));
        stopButton->setFont(font);
        inputDimension = new QDoubleSpinBox(OptionsBackground);
        inputDimension->setObjectName("inputDimension");
        inputDimension->setGeometry(QRect(40, 380, 91, 30));
        inputDimension->setDecimals(0);
        inputDimension->setMinimum(1.000000000000000);
        inputDimension->setMaximum(100.000000000000000);
        inputDimension->setSingleStep(1.000000000000000);
        label7 = new QLabel(OptionsBackground);
        label7->setObjectName("label7");
        label7->setGeometry(QRect(40, 360, 111, 16));
        label_2 = new QLabel(OptionsBackground);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 850, 47, 13));
        progressContainer = new QWidget(OptionsBackground);
        progressContainer->setObjectName("progressContainer");
        progressContainer->setEnabled(true);
        progressContainer->setGeometry(QRect(50, 700, 311, 161));
        label18 = new QLabel(progressContainer);
        label18->setObjectName("label18");
        label18->setGeometry(QRect(10, 30, 31, 31));
        QFont font1;
        font1.setPointSize(12);
        label18->setFont(font1);
        label18->setAlignment(Qt::AlignCenter);
        label19 = new QLabel(progressContainer);
        label19->setObjectName("label19");
        label19->setGeometry(QRect(10, 70, 31, 31));
        label19->setFont(font1);
        label19->setAlignment(Qt::AlignCenter);
        label20 = new QLabel(progressContainer);
        label20->setObjectName("label20");
        label20->setGeometry(QRect(10, 110, 31, 31));
        label20->setFont(font1);
        label20->setAlignment(Qt::AlignCenter);
        labelIteration = new QLabel(progressContainer);
        labelIteration->setObjectName("labelIteration");
        labelIteration->setGeometry(QRect(0, -1, 311, 21));
        labelIteration->setFont(font);
        labelIteration->setAlignment(Qt::AlignCenter);
        progressBarS = new QProgressBar(progressContainer);
        progressBarS->setObjectName("progressBarS");
        progressBarS->setGeometry(QRect(50, 30, 241, 31));
        progressBarS->setValue(24);
        progressBarS->setTextVisible(false);
        progressBarI = new QProgressBar(progressContainer);
        progressBarI->setObjectName("progressBarI");
        progressBarI->setGeometry(QRect(50, 70, 241, 31));
        progressBarI->setValue(24);
        progressBarI->setTextVisible(false);
        progressBarR = new QProgressBar(progressContainer);
        progressBarR->setObjectName("progressBarR");
        progressBarR->setGeometry(QRect(50, 110, 241, 31));
        progressBarR->setValue(24);
        progressBarR->setTextVisible(false);
        navigation->addWidget(simulationPage);
        comparePage = new QWidget();
        comparePage->setObjectName("comparePage");
        compareList1 = new QListWidget(comparePage);
        compareList1->setObjectName("compareList1");
        compareList1->setGeometry(QRect(20, 40, 256, 400));
        compareButton = new QPushButton(comparePage);
        compareButton->setObjectName("compareButton");
        compareButton->setGeometry(QRect(330, 440, 41, 41));
        compareList2 = new QListWidget(comparePage);
        compareList2->setObjectName("compareList2");
        compareList2->setGeometry(QRect(20, 470, 256, 400));
        scrollArea_2 = new QScrollArea(comparePage);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setGeometry(QRect(400, 40, 591, 831));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 589, 829));
        chartContainerCompare = new QWidget(scrollAreaWidgetContents_2);
        chartContainerCompare->setObjectName("chartContainerCompare");
        chartContainerCompare->setGeometry(QRect(0, 0, 581, 441));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
        navigation->addWidget(comparePage);
        analyticsPage = new QWidget();
        analyticsPage->setObjectName("analyticsPage");
        fileList = new QListWidget(analyticsPage);
        fileList->setObjectName("fileList");
        fileList->setGeometry(QRect(20, 20, 256, 911));
        QFont font2;
        font2.setPointSize(10);
        fileList->setFont(font2);
        fileSelectButton = new QPushButton(analyticsPage);
        fileSelectButton->setObjectName("fileSelectButton");
        fileSelectButton->setGeometry(QRect(320, 462, 75, 41));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        fileSelectButton->setFont(font3);
        scrollArea = new QScrollArea(analyticsPage);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(430, 20, 551, 911));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 549, 909));
        chartContainer1 = new QWidget(scrollAreaWidgetContents);
        chartContainer1->setObjectName("chartContainer1");
        chartContainer1->setGeometry(QRect(0, 0, 551, 381));
        chartContainer2 = new QGraphicsView(scrollAreaWidgetContents);
        chartContainer2->setObjectName("chartContainer2");
        chartContainer2->setGeometry(QRect(20, 460, 410, 410));
        iterationLabelChart2 = new QLabel(scrollAreaWidgetContents);
        iterationLabelChart2->setObjectName("iterationLabelChart2");
        iterationLabelChart2->setGeometry(QRect(0, 399, 551, 31));
        QFont font4;
        font4.setPointSize(11);
        iterationLabelChart2->setFont(font4);
        iterationLabelChart2->setAlignment(Qt::AlignCenter);
        playPauseButton = new QPushButton(scrollAreaWidgetContents);
        playPauseButton->setObjectName("playPauseButton");
        playPauseButton->setGeometry(QRect(460, 460, 41, 41));
        restartButton = new QPushButton(scrollAreaWidgetContents);
        restartButton->setObjectName("restartButton");
        restartButton->setGeometry(QRect(460, 540, 41, 41));
        speedSlider = new QSlider(scrollAreaWidgetContents);
        speedSlider->setObjectName("speedSlider");
        speedSlider->setGeometry(QRect(450, 640, 81, 20));
        speedSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName("label");
        label->setGeometry(QRect(450, 620, 47, 13));
        scrollArea->setWidget(scrollAreaWidgetContents);
        navigation->addWidget(analyticsPage);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1009, 21));
        menuNavigation = new QMenu(menubar);
        menuNavigation->setObjectName("menuNavigation");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNavigation->menuAction());
        menuNavigation->addAction(actionAnalytics);
        menuNavigation->addAction(actionSimulation);
        menuNavigation->addAction(actionCompare);

        retranslateUi(MainWindow);

        pagination->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAnalytics->setText(QCoreApplication::translate("MainWindow", "Analytics", nullptr));
        actionSimulation->setText(QCoreApplication::translate("MainWindow", "Simulation", nullptr));
        actionCompare->setText(QCoreApplication::translate("MainWindow", "Compare", nullptr));
        selectModel->setItemText(0, QCoreApplication::translate("MainWindow", "SIR Diffusion", nullptr));
        selectModel->setItemText(1, QCoreApplication::translate("MainWindow", "Agentbased", nullptr));

        label1->setText(QCoreApplication::translate("MainWindow", "Select Model", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "\316\262 (infection)", nullptr));
        label6->setText(QCoreApplication::translate("MainWindow", "\316\263 (recovery)", nullptr));
        startSimulation->setText(QCoreApplication::translate("MainWindow", "start Simulation", nullptr));
        label8->setText(QCoreApplication::translate("MainWindow", "Diffusion coefficients", nullptr));
        label9->setText(QCoreApplication::translate("MainWindow", "DS", nullptr));
        label10->setText(QCoreApplication::translate("MainWindow", "DI", nullptr));
        label11->setText(QCoreApplication::translate("MainWindow", "DR", nullptr));
        label14->setText(QCoreApplication::translate("MainWindow", "moveToHotspot", nullptr));
        label15->setText(QCoreApplication::translate("MainWindow", "Area (km\302\262)", nullptr));
        averageDistanceText->setText(QCoreApplication::translate("MainWindow", "Average Distance between two people: 50m", nullptr));
        label16->setText(QCoreApplication::translate("MainWindow", "Collision radius (m)", nullptr));
        label17->setText(QCoreApplication::translate("MainWindow", "maxMobilityPerDay (km)", nullptr));
        label21->setText(QCoreApplication::translate("MainWindow", "Hotspot radius (km)", nullptr));
        pauseButton->setText(QCoreApplication::translate("MainWindow", "pause", nullptr));
        continueButton->setText(QCoreApplication::translate("MainWindow", "continue", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        label7->setText(QCoreApplication::translate("MainWindow", "Grid Dimension", nullptr));
        label_2->setText(QString());
        label18->setText(QCoreApplication::translate("MainWindow", "S", nullptr));
        label19->setText(QCoreApplication::translate("MainWindow", "I", nullptr));
        label20->setText(QCoreApplication::translate("MainWindow", "R", nullptr));
        labelIteration->setText(QCoreApplication::translate("MainWindow", "Iteration: 0", nullptr));
        compareButton->setText(QString());
        fileSelectButton->setText(QCoreApplication::translate("MainWindow", "Select", nullptr));
        iterationLabelChart2->setText(QCoreApplication::translate("MainWindow", "Iteration: 0", nullptr));
        playPauseButton->setText(QString());
        restartButton->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        menuNavigation->setTitle(QCoreApplication::translate("MainWindow", "Navigation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
