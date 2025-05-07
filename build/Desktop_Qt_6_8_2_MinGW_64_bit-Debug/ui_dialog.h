/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *dialogTime;
    QLabel *dialogDuration;
    QLabel *dialogSelectedModel;
    QDoubleSpinBox *dialogInputBeta;
    QLabel *label5_2;
    QLabel *label6_2;
    QDoubleSpinBox *dialogInputGamma;
    QLabel *label7_2;
    QDoubleSpinBox *dialogInputDimension;
    QLabel *label2_2;
    QSpinBox *dialogInputS;
    QLabel *label4_2;
    QSpinBox *dialogInputI;
    QLabel *label3_2;
    QSpinBox *dialogInputR;
    QStackedWidget *paginationDialog;
    QWidget *sirPageDialog;
    QLabel *label8_2;
    QLabel *label9_2;
    QDoubleSpinBox *dialogInputDS;
    QDoubleSpinBox *dialogInputDI;
    QDoubleSpinBox *dialogInputDR;
    QLabel *label10_2;
    QLabel *label11_2;
    QWidget *agentPageDialog;
    QLabel *label14_2;
    QDoubleSpinBox *dialogInputMoveToHotspot;
    QLabel *label15_2;
    QDoubleSpinBox *dialogInputArea;
    QDoubleSpinBox *dialogInputCollisionRadius;
    QLabel *label16_2;
    QDoubleSpinBox *dialogInputMaxMobilityPerDay;
    QLabel *label17_2;
    QLabel *label22;
    QDoubleSpinBox *dialogHotspotRadius;
    QTextEdit *filename;
    QLabel *label_5;
    QPushButton *savefile;
    QLabel *dialogIterations;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(400, 475);
        Dialog->setMinimumSize(QSize(400, 475));
        Dialog->setMaximumSize(QSize(400, 475));
        buttonBox = new QDialogButtonBox(Dialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setStandardButtons(QDialogButtonBox::NoButton);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 381, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);
        dialogTime = new QLabel(Dialog);
        dialogTime->setObjectName("dialogTime");
        dialogTime->setGeometry(QRect(10, 40, 121, 21));
        dialogDuration = new QLabel(Dialog);
        dialogDuration->setObjectName("dialogDuration");
        dialogDuration->setGeometry(QRect(10, 70, 131, 16));
        dialogSelectedModel = new QLabel(Dialog);
        dialogSelectedModel->setObjectName("dialogSelectedModel");
        dialogSelectedModel->setGeometry(QRect(10, 110, 191, 16));
        QFont font1;
        font1.setPointSize(9);
        dialogSelectedModel->setFont(font1);
        dialogInputBeta = new QDoubleSpinBox(Dialog);
        dialogInputBeta->setObjectName("dialogInputBeta");
        dialogInputBeta->setEnabled(false);
        dialogInputBeta->setGeometry(QRect(10, 210, 91, 30));
        dialogInputBeta->setMaximum(1.000000000000000);
        dialogInputBeta->setSingleStep(0.010000000000000);
        label5_2 = new QLabel(Dialog);
        label5_2->setObjectName("label5_2");
        label5_2->setGeometry(QRect(10, 180, 101, 30));
        label6_2 = new QLabel(Dialog);
        label6_2->setObjectName("label6_2");
        label6_2->setGeometry(QRect(120, 180, 91, 30));
        dialogInputGamma = new QDoubleSpinBox(Dialog);
        dialogInputGamma->setObjectName("dialogInputGamma");
        dialogInputGamma->setEnabled(false);
        dialogInputGamma->setGeometry(QRect(120, 210, 91, 30));
        dialogInputGamma->setMaximum(1.000000000000000);
        dialogInputGamma->setSingleStep(0.010000000000000);
        label7_2 = new QLabel(Dialog);
        label7_2->setObjectName("label7_2");
        label7_2->setGeometry(QRect(230, 190, 111, 16));
        dialogInputDimension = new QDoubleSpinBox(Dialog);
        dialogInputDimension->setObjectName("dialogInputDimension");
        dialogInputDimension->setEnabled(false);
        dialogInputDimension->setGeometry(QRect(230, 210, 91, 30));
        QFont font2;
        font2.setStyleStrategy(QFont::PreferDefault);
        dialogInputDimension->setFont(font2);
        dialogInputDimension->setDecimals(0);
        dialogInputDimension->setMinimum(1.000000000000000);
        dialogInputDimension->setMaximum(100.000000000000000);
        dialogInputDimension->setSingleStep(1.000000000000000);
        label2_2 = new QLabel(Dialog);
        label2_2->setObjectName("label2_2");
        label2_2->setGeometry(QRect(10, 140, 21, 30));
        dialogInputS = new QSpinBox(Dialog);
        dialogInputS->setObjectName("dialogInputS");
        dialogInputS->setEnabled(false);
        dialogInputS->setGeometry(QRect(20, 140, 101, 30));
        dialogInputS->setMaximum(100000000);
        label4_2 = new QLabel(Dialog);
        label4_2->setObjectName("label4_2");
        label4_2->setGeometry(QRect(140, 140, 21, 30));
        dialogInputI = new QSpinBox(Dialog);
        dialogInputI->setObjectName("dialogInputI");
        dialogInputI->setEnabled(false);
        dialogInputI->setGeometry(QRect(150, 140, 101, 30));
        dialogInputI->setMaximum(100000002);
        label3_2 = new QLabel(Dialog);
        label3_2->setObjectName("label3_2");
        label3_2->setGeometry(QRect(270, 140, 21, 30));
        dialogInputR = new QSpinBox(Dialog);
        dialogInputR->setObjectName("dialogInputR");
        dialogInputR->setEnabled(false);
        dialogInputR->setGeometry(QRect(280, 140, 101, 30));
        dialogInputR->setMaximum(100000000);
        paginationDialog = new QStackedWidget(Dialog);
        paginationDialog->setObjectName("paginationDialog");
        paginationDialog->setGeometry(QRect(10, 260, 371, 161));
        sirPageDialog = new QWidget();
        sirPageDialog->setObjectName("sirPageDialog");
        label8_2 = new QLabel(sirPageDialog);
        label8_2->setObjectName("label8_2");
        label8_2->setGeometry(QRect(120, 20, 151, 16));
        label9_2 = new QLabel(sirPageDialog);
        label9_2->setObjectName("label9_2");
        label9_2->setGeometry(QRect(0, 40, 31, 16));
        dialogInputDS = new QDoubleSpinBox(sirPageDialog);
        dialogInputDS->setObjectName("dialogInputDS");
        dialogInputDS->setEnabled(false);
        dialogInputDS->setGeometry(QRect(0, 60, 71, 30));
        dialogInputDS->setMaximum(1.000000000000000);
        dialogInputDS->setSingleStep(0.010000000000000);
        dialogInputDI = new QDoubleSpinBox(sirPageDialog);
        dialogInputDI->setObjectName("dialogInputDI");
        dialogInputDI->setEnabled(false);
        dialogInputDI->setGeometry(QRect(100, 60, 71, 30));
        dialogInputDI->setMaximum(10.000000000000000);
        dialogInputDI->setSingleStep(0.010000000000000);
        dialogInputDR = new QDoubleSpinBox(sirPageDialog);
        dialogInputDR->setObjectName("dialogInputDR");
        dialogInputDR->setEnabled(false);
        dialogInputDR->setGeometry(QRect(200, 60, 71, 30));
        dialogInputDR->setMaximum(10.000000000000000);
        dialogInputDR->setSingleStep(0.010000000000000);
        label10_2 = new QLabel(sirPageDialog);
        label10_2->setObjectName("label10_2");
        label10_2->setGeometry(QRect(100, 40, 31, 16));
        label11_2 = new QLabel(sirPageDialog);
        label11_2->setObjectName("label11_2");
        label11_2->setGeometry(QRect(200, 40, 31, 16));
        paginationDialog->addWidget(sirPageDialog);
        agentPageDialog = new QWidget();
        agentPageDialog->setObjectName("agentPageDialog");
        label14_2 = new QLabel(agentPageDialog);
        label14_2->setObjectName("label14_2");
        label14_2->setGeometry(QRect(0, 80, 101, 30));
        dialogInputMoveToHotspot = new QDoubleSpinBox(agentPageDialog);
        dialogInputMoveToHotspot->setObjectName("dialogInputMoveToHotspot");
        dialogInputMoveToHotspot->setEnabled(false);
        dialogInputMoveToHotspot->setGeometry(QRect(0, 110, 91, 30));
        dialogInputMoveToHotspot->setMinimum(0.000000000000000);
        dialogInputMoveToHotspot->setMaximum(1.000000000000000);
        dialogInputMoveToHotspot->setSingleStep(0.010000000000000);
        label15_2 = new QLabel(agentPageDialog);
        label15_2->setObjectName("label15_2");
        label15_2->setGeometry(QRect(0, 10, 101, 30));
        dialogInputArea = new QDoubleSpinBox(agentPageDialog);
        dialogInputArea->setObjectName("dialogInputArea");
        dialogInputArea->setEnabled(false);
        dialogInputArea->setGeometry(QRect(0, 40, 91, 31));
        dialogInputArea->setMinimum(1.000000000000000);
        dialogInputArea->setMaximum(10000.000000000000000);
        dialogInputArea->setSingleStep(1.000000000000000);
        dialogInputArea->setValue(1.000000000000000);
        dialogInputCollisionRadius = new QDoubleSpinBox(agentPageDialog);
        dialogInputCollisionRadius->setObjectName("dialogInputCollisionRadius");
        dialogInputCollisionRadius->setEnabled(false);
        dialogInputCollisionRadius->setGeometry(QRect(120, 40, 91, 31));
        dialogInputCollisionRadius->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        dialogInputCollisionRadius->setMinimum(1.000000000000000);
        dialogInputCollisionRadius->setMaximum(10000.000000000000000);
        dialogInputCollisionRadius->setSingleStep(1.000000000000000);
        dialogInputCollisionRadius->setValue(1.000000000000000);
        label16_2 = new QLabel(agentPageDialog);
        label16_2->setObjectName("label16_2");
        label16_2->setGeometry(QRect(120, 10, 111, 30));
        dialogInputMaxMobilityPerDay = new QDoubleSpinBox(agentPageDialog);
        dialogInputMaxMobilityPerDay->setObjectName("dialogInputMaxMobilityPerDay");
        dialogInputMaxMobilityPerDay->setEnabled(false);
        dialogInputMaxMobilityPerDay->setGeometry(QRect(120, 110, 91, 30));
        dialogInputMaxMobilityPerDay->setFocusPolicy(Qt::NoFocus);
        dialogInputMaxMobilityPerDay->setLocale(QLocale(QLocale::German, QLocale::Belgium));
        dialogInputMaxMobilityPerDay->setMinimum(1.000000000000000);
        dialogInputMaxMobilityPerDay->setMaximum(100.000000000000000);
        dialogInputMaxMobilityPerDay->setSingleStep(0.100000000000000);
        label17_2 = new QLabel(agentPageDialog);
        label17_2->setObjectName("label17_2");
        label17_2->setGeometry(QRect(120, 80, 131, 30));
        label22 = new QLabel(agentPageDialog);
        label22->setObjectName("label22");
        label22->setGeometry(QRect(240, 10, 111, 30));
        dialogHotspotRadius = new QDoubleSpinBox(agentPageDialog);
        dialogHotspotRadius->setObjectName("dialogHotspotRadius");
        dialogHotspotRadius->setEnabled(false);
        dialogHotspotRadius->setGeometry(QRect(240, 40, 91, 31));
        dialogHotspotRadius->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        dialogHotspotRadius->setMinimum(0.010000000000000);
        dialogHotspotRadius->setMaximum(10000.000000000000000);
        dialogHotspotRadius->setSingleStep(0.100000000000000);
        dialogHotspotRadius->setValue(1.000000000000000);
        paginationDialog->addWidget(agentPageDialog);
        filename = new QTextEdit(Dialog);
        filename->setObjectName("filename");
        filename->setGeometry(QRect(10, 430, 151, 31));
        label_5 = new QLabel(Dialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(170, 440, 47, 13));
        QFont font3;
        font3.setPointSize(10);
        label_5->setFont(font3);
        savefile = new QPushButton(Dialog);
        savefile->setObjectName("savefile");
        savefile->setGeometry(QRect(230, 430, 131, 31));
        dialogIterations = new QLabel(Dialog);
        dialogIterations->setObjectName("dialogIterations");
        dialogIterations->setGeometry(QRect(10, 90, 131, 16));

        retranslateUi(Dialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Dialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Dialog, qOverload<>(&QDialog::reject));

        paginationDialog->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Simulation Results", nullptr));
        dialogTime->setText(QCoreApplication::translate("Dialog", "02.03.2025 18:59", nullptr));
        dialogDuration->setText(QCoreApplication::translate("Dialog", "Duration: 00:34 ", nullptr));
        dialogSelectedModel->setText(QCoreApplication::translate("Dialog", "Selected Model: SIR Diffusion", nullptr));
        label5_2->setText(QCoreApplication::translate("Dialog", "\316\262 (infection)", nullptr));
        label6_2->setText(QCoreApplication::translate("Dialog", "\316\263 (recovery)", nullptr));
        label7_2->setText(QCoreApplication::translate("Dialog", "Grid Dimension", nullptr));
        label2_2->setText(QCoreApplication::translate("Dialog", "S", nullptr));
        label4_2->setText(QCoreApplication::translate("Dialog", "I", nullptr));
        label3_2->setText(QCoreApplication::translate("Dialog", "R", nullptr));
        label8_2->setText(QCoreApplication::translate("Dialog", "Diffusion coefficients", nullptr));
        label9_2->setText(QCoreApplication::translate("Dialog", "DS", nullptr));
        label10_2->setText(QCoreApplication::translate("Dialog", "DI", nullptr));
        label11_2->setText(QCoreApplication::translate("Dialog", "DR", nullptr));
        label14_2->setText(QCoreApplication::translate("Dialog", "moveToHotspot", nullptr));
        label15_2->setText(QCoreApplication::translate("Dialog", "Area (km\302\262)", nullptr));
        label16_2->setText(QCoreApplication::translate("Dialog", "Collision radius (m)", nullptr));
        label17_2->setText(QCoreApplication::translate("Dialog", "maxMobilityPerDay (km)", nullptr));
        label22->setText(QCoreApplication::translate("Dialog", "Hotspot radius (km)", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", ".csv", nullptr));
        savefile->setText(QCoreApplication::translate("Dialog", "save", nullptr));
        dialogIterations->setText(QCoreApplication::translate("Dialog", "Iterations: 103", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
