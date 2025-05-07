#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QDialog>
#include "ui_dialog.h"
#include "simulation.h"
#include <QtConcurrent>
#include <QDateTime>
#include <QElapsedTimer>
#include <QDir>
#include <QListWidgetItem>
#include "heatmapanimation.h"
#include <QtCharts>
#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("My Pandemic-Simulation");
    scene = new QGraphicsScene(this);
    ui->MapContainer->setScene(scene);
    loadMapImage("C:/Users/Baran/Documents/untitled1/Karte_Deutschland.png");
    placeMarker(52.513908554724104, 13.417826317730706);
    placeMarker(50.77549333064992, 6.085528008818414);

    ui->inputS->setValue(42'000);
    ui->inputI->setValue(8);
    ui->inputR->setValue(0);
    ui->inputGamma->setValue(0.1);
    ui->inputBeta->setValue(0.2);
    ui->inputDimension->setValue(10);
    ui->inputDiffusionS->setValue(1);
    ui->inputDiffusionI->setValue(1);
    ui->inputDiffusionR->setValue(1);

    ui->inputAgentCollisionRadius->setValue(5.00);
    ui->inputAgentArea->setValue(50.00);
    ui->inputAgentMoveToHotspot->setValue(0.01);
    ui->inputAgentMaxMobility->setValue(2.00);
    // Area 50km^2 => Seitenlänge 7km
    // Dimension = 10
    // => Seitenlänge pro Zelle 0.7km
    // Hotspotradius [0, 0.35km]

    // 42k / 10x10 Dimension = 420 pro Zelle
    // 1% * 420 = 42Personen im Hotspot

    // Gesucht : X (Radius vom Hotspot)
    // Gegeben :    42 Personen im Hotspot
    //              Y  Kollisionsradius
    //              Z  AVG Abstand zwischen zwei Personen im Hotspot
    // Z = 42Personen / Y
    // TODO sinnvollen radius ableiten

    ui->inputAgentHotspotRadius->setValue(0.1);

    setFixedSize(1000,1000);

    updateUI();

    connect(ui->startSimulation, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseSimulation);
    connect(ui->continueButton, &QPushButton::clicked, this, &MainWindow::continueSimulation);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(ui->selectModel, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onModelChanged);

    ui->selectModel->setCurrentIndex(0);
    ui->pagination->setCurrentWidget(ui->sirPage);

    this->averageDistanceChanged();


    // style
    ui->MapContainer->setStyleSheet("QFrame { background-color: #272838; }");
    ui->OptionsBackground->setStyleSheet("QFrame { background-color: #272838; }");
    ui->selectModel->setStyleSheet(
        "QComboBox { color: white; background-color: #272838; border: 1px solid white; padding: 5px; }"
        "QComboBox::drop-down { border: none; }"
        "QComboBox QAbstractItemView { background: white; color: black; selection-background-color: lightgray; border: 1px solid gray; }"
        "QComboBox::item { background-color: white; color: black; }"
        "QComboBox::item:hover { background-color: #007BFF; color: white; }"
        );

    ui->label1->setStyleSheet("QLabel { color: white; }");
    ui->label2->setStyleSheet("QLabel { color: white; }");
    ui->label3->setStyleSheet("QLabel { color: white; }");
    ui->label4->setStyleSheet("QLabel { color: white; }");
    ui->label5->setStyleSheet("QLabel { color: white; }");
    ui->label6->setStyleSheet("QLabel { color: white; }");
    ui->label7->setStyleSheet("QLabel { color: white; }");
    ui->label8->setStyleSheet("QLabel { color: white; }");
    ui->label9->setStyleSheet("QLabel { color: white; }");
    ui->label10->setStyleSheet("QLabel { color: white; }");
    ui->label11->setStyleSheet("QLabel { color: white; }");

    ui->label14->setStyleSheet("QLabel { color: white; }");
    ui->label15->setStyleSheet("QLabel { color: white; }");
    ui->averageDistanceText->setStyleSheet("QLabel { color: white; }");

    ui->label16->setStyleSheet("QLabel { color: white; }");
    ui->label17->setStyleSheet("QLabel { color: white; }");
    ui->label18->setStyleSheet("QLabel { color: white; }");
    ui->label19->setStyleSheet("QLabel { color: white; }");
    ui->label20->setStyleSheet("QLabel { color: white; }");
    ui->label21->setStyleSheet("QLabel { color: white; }");
    ui->labelIteration->setStyleSheet("QLabel { color: white; }");


    ui->startSimulation->setStyleSheet(
        "QPushButton { background-color: green; color: white; border-radius: 5px; padding: 5px; }"
        "QPushButton:hover { background-color: #008000; }"
        "QPushButton:pressed { background-color: #004d00; }"
        );

    ui->pauseButton->setStyleSheet(
        "QPushButton { background-color: #ffc107; color: white; border-radius: 5px; padding: 5px; }"
        "QPushButton:hover { background-color: #ffca2c; }"
        "QPushButton:pressed { background-color: #ffbf00; }"
        );

    ui->continueButton->setStyleSheet(
        "QPushButton { background-color: #007BFF; color: white; border-radius: 5px; padding: 5px; }"
        "QPushButton:hover { background-color: #0088FF; }"
        "QPushButton:pressed { background-color: #0069D9; }"
        );

    ui->stopButton->setStyleSheet(
        "QPushButton { background-color: red; color: white; border-radius: 5px; padding: 5px; }"
        "QPushButton:hover { background-color: #ff0000; }"
        "QPushButton:pressed { background-color: #cc0000; }"
        );

    connect(ui->inputAgentArea,QOverload<double>::of(&QDoubleSpinBox::valueChanged),this, &MainWindow::averageDistanceChanged);
    connect(ui->inputS, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::averageDistanceChanged);
    connect(ui->inputI, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::averageDistanceChanged);
    connect(ui->inputR, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::averageDistanceChanged);

    connect(ui->actionAnalytics, &QAction::triggered, [&]() {
        initializeFileList();
        ui->navigation->setCurrentWidget(ui->analyticsPage);
    });

    connect(ui->actionSimulation, &QAction::triggered, [&]() {
        ui->navigation->setCurrentWidget(ui->simulationPage);
    });

    connect(ui->actionCompare, &QAction::triggered, [&]() {
        initializeCompareList();
        ui->navigation->setCurrentWidget(ui->comparePage);
    });

    connect(ui->fileSelectButton, &QPushButton::clicked, [&]() {
        QListWidgetItem *selectedItem = ui->fileList->currentItem();

        if (selectedItem) {
            QString filePath = selectedItem->data(Qt::UserRole).toString();
            qDebug() << "Ausgewählte Datei:" << filePath;
            QVector tmp1 = loadCSVDataChart1(filePath);
            createChart1(tmp1);
            startHeatmapAnimation(filePath);

        } else {
            qDebug() << "Keine Datei ausgewählt!";
        }
    });

    ui->progressContainer->hide();
    ui->progressBarS->setStyleSheet(
        "QProgressBar::chunk {"
        "    background-color: green;"  // Farbe des Fortschrittsbalkens
        "    width: 1px;"             // Deaktiviert Ladeanimation
        "}"
        );
    ui->progressBarI->setStyleSheet(
        "QProgressBar::chunk {"
        "    background-color: red;"  // Farbe des Fortschrittsbalkens
        "    width: 1px;"             // Deaktiviert Ladeanimation
        "}"
        );
    ui->progressBarR->setStyleSheet(
        "QProgressBar::chunk {"
        "    background-color: blue;"  // Farbe des Fortschrittsbalkens
        "    width: 1px;"             // Deaktiviert Ladeanimation
        "}"
        );
    ui->compareButton->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    connect(ui->compareButton, &QPushButton::clicked, this, &MainWindow::createComparePlot);

}

double MainWindow::loadTotalPopulation(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File open Error" << file.errorString();
        return 0.0;
    }

    QTextStream in(&file);
    bool headerSkipped = false;
    double totalPopulation = 0.0;


    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // Header überspringen (erste zwei Zeilen)
        if (!headerSkipped) {
            if (line.startsWith("Iteration")) {
                headerSkipped = true;
            }
            continue;
        }

        QStringList values = line.split(",");

        if (values.size() < 6) {
            qDebug() << "CSV Format Error" << values.size();
            continue;
        }

        bool ok;
        int iteration = values[0].toInt(&ok);
        if (!ok) {
            qDebug() << "Iteration parse Error" << values[0];
            continue;
        }

        if (iteration != 0) {
            break;
        }

        double susceptible = values[3].trimmed().toDouble(&ok);
        if (!ok) {
            qDebug() << "Error susceptible" << values[3];
            continue;
        }

        double infected = values[4].trimmed().toDouble(&ok);
        if (!ok) {
            qDebug() << "Error infected" << values[4];
            continue;
        }

        double recovered = values[5].trimmed().toDouble(&ok);
        if (!ok) {
            qDebug() << "Error recovered" << values[5];
            continue;
        }

        totalPopulation += (susceptible + infected + recovered);
    }

    file.close();

    return totalPopulation;
}

QVector<QPointF> MainWindow::normalizeData(const QVector<QPointF> &data, double totalPopulation) {
    QVector<QPointF> normalizedData;
    if (data.isEmpty()) {
        return normalizedData;
    }

    for (const QPointF &point : data) {
        double normalizedValue = point.y() / totalPopulation; // relative
        normalizedData.append(QPointF(point.x(), normalizedValue));
    }
    return normalizedData;
}

void MainWindow::createComparePlot() {
    QListWidgetItem *selectedItem1 = ui->compareList1->currentItem();
    QListWidgetItem *selectedItem2 = ui->compareList2->currentItem();

    if (!selectedItem1 || !selectedItem2) {
        qDebug() << "Bitte zwei Dateien auswählen!";
        return;
    }

    QString filePath1 = selectedItem1->data(Qt::UserRole).toString();
    QString filePath2 = selectedItem2->data(Qt::UserRole).toString();

    QString fileName1 = QFileInfo(filePath1).fileName();
    QString fileName2 = QFileInfo(filePath2).fileName();

    QVector<QPointF> data1 = loadInfectionData(filePath1);
    QVector<QPointF> data2 = loadInfectionData(filePath2);

    double totalPopulation1 = loadTotalPopulation(filePath1);
    double totalPopulation2 = loadTotalPopulation(filePath2);

    QVector<QPointF> normalizedData1 = normalizeData(data1, totalPopulation1);
    QVector<QPointF> normalizedData2 = normalizeData(data2, totalPopulation2);

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();

    series1->setName(fileName1);
    series2->setName(fileName2);

    for (const QPointF &point : normalizedData1) {
        series1->append(point.x(), point.y());
    }
    for (const QPointF &point : normalizedData2) {
        series2->append(point.x(), point.y());
    }

    series1->setColor(Qt::red);
    series2->setColor(Qt::blue);

    // Linien, keine Punkte**
    series1->setPointsVisible(false);
    series2->setPointsVisible(false);

    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->legend()->setVisible(true);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Iteration");
    axisX->setLabelFormat("%.0f");  // Nur ganze Zahlen anzeigen
    chart->addAxis(axisX, Qt::AlignBottom);
    series1->attachAxis(axisX);
    series2->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Propotion of infected people");
    axisY->setRange(0, 0.5);
    chart->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisY);
    series2->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Layout ersetzen
    if (!ui->chartContainerCompare->layout()) {
        ui->chartContainerCompare->setLayout(new QVBoxLayout());
    }

    // Altes Diagramm entfernen
    QLayoutItem *child;
    while ((child = ui->chartContainerCompare->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    ui->chartContainerCompare->layout()->addWidget(chartView);
}

QVector<QPointF> MainWindow::loadInfectionData(const QString &filename) {
    QMap<int, double> infectionSums;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Fehler beim Öffnen der Datei: " << file.errorString();
        return {};
    }

    QTextStream in(&file);
    bool headerSkipped = false;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // Überspringe Header (erste zwei Zeilen)
        if (!headerSkipped) {
            if (line.startsWith("Iteration")) {
                headerSkipped = true;
            }
            continue;
        }

        QStringList values = line.split(",");

        if (values.size() < 6) {  // Iteration, CellX, CellY, S, I, R
            qDebug() << "Überspringe ungültige Zeile (zu wenig Spalten): " << line;
            continue;
        }

        bool ok;
        int iteration = values[0].toInt(&ok);
        if (!ok) {
            qDebug() << "Fehler beim Parsen der Iteration: " << values[0];
            continue;
        }

        double infected = values[4].toDouble(&ok);
        if (!ok) {
            qDebug() << "Fehler beim Parsen der Infizierten-Zahl: " << values[4];
            continue;
        }

        infectionSums[iteration] += infected;
    }

    file.close();

    QVector<QPointF> dataPoints;
    for (auto it = infectionSums.begin(); it != infectionSums.end(); ++it) {
        dataPoints.append(QPointF(it.key(), it.value()));
    }

    return dataPoints;
}



void MainWindow::startHeatmapAnimation(const QString file) {
    if(heatmap != nullptr){
        delete heatmap;
    }
    heatmap = new HeatmapAnimation(ui->chartContainer2, ui->iterationLabelChart2, ui->playPauseButton, ui->restartButton, ui->speedSlider, file);
}

QVector<QLineSeries*> MainWindow::loadCSVDataChart1(const QString &filename) {
    QLineSeries *seriesS = new QLineSeries();
    QLineSeries *seriesI = new QLineSeries();
    QLineSeries *seriesR = new QLineSeries();

    seriesS->setName("Susceptible (S)");
    seriesI->setName("Infected (I)");
    seriesR->setName("Recovered (R)");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Fehler beim Öffnen der Datei:" << file.errorString();
        return {};
    }

    QTextStream in(&file);
    bool headerSkipped = false;

    QMap<int, double> sumS, sumI, sumR;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        // Überspringe die ersten zwei Zeilen
        if (!headerSkipped) {
            if (line.startsWith("Iteration")) {
                headerSkipped = true;
            }
            continue;
        }

        QStringList values = line.split(",");

        if (values.size() < 6) continue;

        bool ok;
        int iteration = values[0].toInt(&ok);
        if (!ok) continue;

        double susceptible = values[3].toDouble(&ok);
        if (!ok) continue;
        double infected = values[4].toDouble(&ok);
        if (!ok) continue;
        double recovered = values[5].toDouble(&ok);
        if (!ok) continue;

        sumS[iteration] += susceptible;
        sumI[iteration] += infected;
        sumR[iteration] += recovered;
    }

    file.close();

    for (auto it = sumS.begin(); it != sumS.end(); ++it) {
        int iteration = it.key();
        seriesS->append(iteration, sumS[iteration]);
        seriesI->append(iteration, sumI[iteration]);
        seriesR->append(iteration, sumR[iteration]);
    }

    return {seriesS, seriesI, seriesR};
}


// Liniendiagramm S,I,R
void MainWindow::createChart1(QVector<QLineSeries*> data) {
    if (data.size() < 3) {
        qDebug() << "Fehler: Nicht genügend Datenserien übergeben!";
        return;
    }

    QLineSeries *seriesS = data[0];
    QLineSeries *seriesI = data[1];
    QLineSeries *seriesR = data[2];

    //qDebug() << "=== Susceptible (S) ===";
    //for (const QPointF &point : seriesS->points()) {
    //    qDebug() << "Iteration:" << point.x() << "Value:" << point.y();
    //}

    //qDebug() << "=== Infected (I) ===";
    //for (const QPointF &point : seriesI->points()) {
    //    qDebug() << "Iteration:" << point.x() << "Value:" << point.y();
    //}

    //qDebug() << "=== Recovered (R) ===";
    //for (const QPointF &point : seriesR->points()) {
    //    qDebug() << "Iteration:" << point.x() << "Value:" << point.y();
    //}

    seriesS->setColor(Qt::blue);   // S = Blau
    seriesI->setColor(Qt::red);    // I = Rot
    seriesR->setColor(Qt::green);  // R = Grün

    seriesS->setName("Susceptible (S)");
    seriesI->setName("Infected (I)");
    seriesR->setName("Recovered (R)");

    QChart *chart = new QChart();
    chart->addSeries(seriesS);
    chart->addSeries(seriesI);
    chart->addSeries(seriesR);
    chart->setTitle("SIR Model Over Time");

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Time in Days");
    axisX->setLabelFormat("%i");

    double xMin = seriesS->points().first().x();  // Erste Iteration
    double xMax = seriesS->points().last().x();   // Letzte Iteration

    axisX->setRange(xMin, xMax);
    axisX->setTickInterval(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    seriesS->attachAxis(axisX);
    seriesI->attachAxis(axisX);
    seriesR->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Number of People");
    axisY->setMin(0);

    double yMax = 0;
    for (const auto &point : seriesS->points()) yMax = qMax(yMax, point.y());
    for (const auto &point : seriesI->points()) yMax = qMax(yMax, point.y());
    for (const auto &point : seriesR->points()) yMax = qMax(yMax, point.y());

    axisY->setMax(yMax);
    chart->addAxis(axisY, Qt::AlignLeft);
    seriesS->attachAxis(axisY);
    seriesI->attachAxis(axisY);
    seriesR->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Altes Diagramm entfernen
    if (ui->chartContainer1->layout()) {
        QLayoutItem *child;
        while ((child = ui->chartContainer1->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
    } else {
        ui->chartContainer1->setLayout(new QVBoxLayout());
    }

    ui->chartContainer1->layout()->addWidget(chartView);
}


void MainWindow::initializeFileList() {
    QDir directory(QDir::currentPath());
    QStringList csvFiles = directory.entryList(QStringList() << "*.csv", QDir::Files);

    ui->fileList->clear();

    for (const QString &file : csvFiles) {
        if (file == "cellwise_simulation.csv") {
            continue;
        }
        QListWidgetItem *item = new QListWidgetItem(file, ui->fileList);
        item->setData(Qt::UserRole, directory.filePath(file));
    }
}


void MainWindow::initializeCompareList() {
    QDir directory(QDir::currentPath());
    QStringList csvFiles = directory.entryList(QStringList() << "*.csv", QDir::Files);

    ui->compareList1->clear();
    ui->compareList2->clear();

    for (const QString &file : csvFiles) {
        if (file == "cellwise_simulation.csv") {
            continue;
        }
        QListWidgetItem *item1 = new QListWidgetItem(file, ui->compareList1);
        QListWidgetItem *item2 = new QListWidgetItem(file, ui->compareList2);
        item1->setData(Qt::UserRole, directory.filePath(file));
        item2->setData(Qt::UserRole, directory.filePath(file));
    }
}

void MainWindow::openDialog(int durationSeconds, bool agentBased, int S, int I, int R, double beta, double gamma, int dimension, double area, double collisionRadius, double moveToHotspot, double maxMobilityPerDay, double ds, double di, double dr, int iterations, double hotspotRadius) {
    QDialog dialog(this);
    Ui::Dialog ui;
    ui.setupUi(&dialog);

    dialog.setWindowTitle("Simulation results");

    ui.savefile->setEnabled(false);

    QString currentTime = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm");
    ui.dialogTime->setText(currentTime);

    // Duration in hh:mm:ss format
    int hours = durationSeconds / 3600;
    int minutes = (durationSeconds % 3600) / 60;
    int seconds = durationSeconds % 60;

    QString formattedDuration = QString("%1:%2:%3")
                                    .arg(hours, 2, 10, QChar('0'))
                                    .arg(minutes, 2, 10, QChar('0'))
                                    .arg(seconds, 2, 10, QChar('0'));

    ui.dialogDuration->setText(QString("Duration: %1").arg(formattedDuration));

    QString model = (agentBased) ? "Agentbased" : "SIR Diffusion";
    ui.dialogSelectedModel->setText(QString("Selected Model: %1").arg(model));

    ui.dialogIterations->setText(QString("Iterations: %1").arg(iterations));

    ui.dialogInputS->setValue(S);
    ui.dialogInputI->setValue(I);
    ui.dialogInputR->setValue(R);
    ui.dialogInputBeta->setValue(beta);
    ui.dialogInputGamma->setValue(gamma);
    ui.dialogInputDimension->setValue(dimension);

    if (agentBased) {
        ui.paginationDialog->setCurrentWidget(ui.agentPageDialog);
        ui.dialogInputMaxMobilityPerDay->setValue(maxMobilityPerDay);
        ui.dialogInputMoveToHotspot->setValue(moveToHotspot);
        ui.dialogInputCollisionRadius->setValue(collisionRadius);
        ui.dialogHotspotRadius->setValue(hotspotRadius);
        ui.dialogInputArea->setValue(area);

    } else {
        ui.paginationDialog->setCurrentWidget(ui.sirPageDialog);
        ui.dialogInputDS->setValue(ds);
        ui.dialogInputDI->setValue(di);
        ui.dialogInputDR->setValue(dr);
    }

    connect(ui.filename, &QTextEdit::textChanged, [&]() {
        ui.savefile->setEnabled(!ui.filename->toPlainText().isEmpty());
    });

    connect(ui.savefile, &QPushButton::clicked, [&]() {
        QString newFilename = ui.filename->toPlainText().trimmed();

        QString oldFilePath = QDir::currentPath() + "/cellwise_simulation.csv";  // Relativer Pfad zur Datei
        QString newFilePath = QDir::currentPath() + "/" + newFilename + ".csv";  // Neuer relativer Pfad

        if (QFile::rename(oldFilePath, newFilePath)) {
            qDebug() << "Datei erfolgreich umbenannt: " << newFilePath;
            dialog.accept();
        } else {
            qDebug() << "Fehler beim Umbenennen der Datei!";
        }

    });


    dialog.exec();
}


void MainWindow::averageDistanceChanged(){
    int S = ui->inputS->value();
    int I = ui->inputI->value();
    int R = ui->inputR->value();
    int totalAgents = S + I + R;
    int areaKmSquare = ui->inputAgentArea->value();
    double density = totalAgents / areaKmSquare;
    // in Meter
    double averageDistance = sqrt(1 / density) * 1000;
    ui->averageDistanceText->setText(QString("Average Distance between two people: %1m").arg(averageDistance, 0, 'f', 2));
}

void MainWindow::updateUI() {
    if (isRunning && isPaused) {
        ui->continueButton->setVisible(true);
        ui->pauseButton->setVisible(false);
        ui->startSimulation->setVisible(false);
        ui->stopButton->setVisible(true);
    } else if (isRunning && !isPaused) {
        ui->continueButton->setVisible(false);
        ui->pauseButton->setVisible(true);
        ui->startSimulation->setVisible(false);
        ui->stopButton->setVisible(true);
    } else {
        ui->continueButton->setVisible(false);
        ui->pauseButton->setVisible(false);
        ui->startSimulation->setVisible(true);
        ui->stopButton->setVisible(false);
    }
}


void MainWindow::onModelChanged(int index) {
    QString selectedModel = ui->selectModel->currentText();
    qDebug() << "Ausgewähltes Modell: " << selectedModel;

    if (selectedModel == "SIR Diffusion") {
        ui->pagination->setCurrentWidget(ui->sirPage);
    } else if (selectedModel == "Agentbased") {
        ui->pagination->setCurrentWidget(ui->agentPage);
    }
}

void MainWindow::stopSimulation() {
    if (tmp) {
        QString selectedModel = ui->selectModel->currentText();
        bool agentBased = (selectedModel == "Agentbased");
        qDebug() << "Simulation wird gestoppt...";

        tmp->resume();
        tmp->stop();

        simulationFuture.waitForFinished();  // Stelle sicher, dass der Thread beendet ist

        qDebug() << "Simulation gestoppt!";
        isRunning = false;
        isPaused = false;
        updateUI();
        ui->progressContainer->hide();

        simulationWatcher.disconnect();  // Trenne alle alten Verbindungen
        simulationWatcher.setFuture(QFuture<void>());  // Setze auf leeren Zustand

        delete tmp;
        tmp = nullptr;
    }
}


void MainWindow::startSimulation() {
    if (tmp && !simulationFuture.isFinished()) {
        qDebug() << "CHECKKK";
        return;
    }

    isRunning = true;
    isPaused = false;
    updateUI();
    simulationTimer.start();

    qDebug() << "Simulation gestartet!";
    int S = ui->inputS->value();
    int I = ui->inputI->value();
    int R = ui->inputR->value();
    double gamma = ui->inputGamma->value();
    double beta = ui->inputBeta->value();
    int dimension = ui->inputDimension->value();
    double diffusionS = ui->inputDiffusionS->value();
    double diffusionI = ui->inputDiffusionI->value();
    double diffusionR = ui->inputDiffusionR->value();
    double collisionRadius = ui->inputAgentCollisionRadius->value();
    double moveToHotspot = ui->inputAgentMoveToHotspot->value();
    double area = ui->inputAgentArea->value();
    double maxMobility = ui->inputAgentMaxMobility->value();
    double hotspotRadius = ui->inputAgentHotspotRadius->value();

    double total = S + I + R;
    int percentS = static_cast<int>((S / total) * 100);
    int percentI = static_cast<int>((I / total) * 100);
    int percentR = static_cast<int>((R / total) * 100);

    ui->progressBarS->setValue(percentS);
    ui->progressBarI->setValue(percentI);
    ui->progressBarR->setValue(percentR);
    ui->labelIteration->setText(QString("Iteration: 0"));
    ui->progressContainer->show();

    tmp = new Simulation(beta, gamma, S, I, R, diffusionS, diffusionI, diffusionR, dimension, collisionRadius, area, moveToHotspot, maxMobility, hotspotRadius);
    bool agentBased = (ui->selectModel->currentText() == "Agentbased");

    simulationFuture = QtConcurrent::run([this, agentBased]() {
        tmp->run(agentBased, ui->labelIteration, ui->progressBarS, ui->progressBarI, ui->progressBarR);
    });

    // Überwachung
    connect(&simulationWatcher, &QFutureWatcher<void>::finished, this, [this,agentBased, S, I, R, beta, gamma, dimension, diffusionS, diffusionI, diffusionR, collisionRadius, moveToHotspot, area, maxMobility, hotspotRadius]() {
        qDebug() << "Simulation beendet!";
        this->stopSimulation();
        qint64 elapsedSeconds = simulationTimer.elapsed() / 1000;
        int iterations = ui->labelIteration->text().split(" ").last().toInt();
        this->openDialog(elapsedSeconds,agentBased, S, I, R, beta, gamma, dimension, area, collisionRadius, moveToHotspot, maxMobility, diffusionS, diffusionI, diffusionR, iterations, hotspotRadius);
    });
    simulationWatcher.setFuture(simulationFuture);
}

void MainWindow::continueSimulation(){
    if (tmp) {
        qDebug() << "Simulation wird fortgesetzt...";
        tmp->resume();
        qDebug() << "Simulation fortgesetzt!";

        isRunning = true;
        isPaused = false;
        updateUI();
    }
}

void MainWindow::pauseSimulation() {
    if (tmp) {
        qDebug() << "Simulation wird gestoppt...";
        tmp->pause();
        qDebug() << "Simulation gestoppt!";

        isRunning = true;
        isPaused = true;
        updateUI();
    }
}


void MainWindow::loadMapImage(std::string filepath)
{
    QString qFilePath = QString::fromStdString(filepath);
    QPixmap mapPixmap(qFilePath);

    if (mapPixmap.isNull()) {
        return;
    }

    scene->clear();
    scene->addPixmap(mapPixmap);

    ui->MapContainer->setFrameShape(QFrame::NoFrame);
    ui->MapContainer->setScene(scene);

    qreal scaleX = static_cast<qreal>(ui->MapContainer->width()) / mapPixmap.width();
    qreal scaleY = static_cast<qreal>(ui->MapContainer->height()) / mapPixmap.height();
    qreal scale = qMin(scaleX, scaleY);

    ui->MapContainer->scale(scale, scale);
}

QPointF MainWindow::geoToPixel(double latitude, double longitude)
{
    // Referenzpunkt 1 (oben links)
    double lat1 = 53.52745619424504;
    double lon1 = 8.231327728016332;
    double x1 = 160;
    double y1 = 158;

    // Referenzpunkt 2 (unten rechts)
    double lat2 = 47.471278757942834;
    double lon2 = 13.006414344891146;
    double x2 = 476;
    double y2 = 775;

    // Berechne die geografische Ausdehnung
    double latitude_range = lat1 - lat2;   // Breitengradbereich
    double longitude_range = lon2 - lon1;  // Längengradbereich

    // Berechne die Pixelanzahl zwischen den Referenzpunkten
    double pixel_width = x2 - x1;
    double pixel_height = y2 - y1;

    // Berechne Pixel pro Grad
    double pixels_per_lat = pixel_height / latitude_range;  // Pixel pro Breitengrad
    double pixels_per_lon = pixel_width / longitude_range;  // Pixel pro Längengrad

    // Umrechnung der geografischen Koordinaten in Pixelkoordinaten
    double x = x1 + (longitude - lon1) * pixels_per_lon;
    double y = y1 + (lat1 - latitude) * pixels_per_lat;  // Invertiere die y-Richtung

    return QPointF(x, y);
}

void MainWindow::placeMarker(double latitude, double longitude)
{
    QPointF pixelCoords = geoToPixel(latitude, longitude);

    QGraphicsEllipseItem* marker = new QGraphicsEllipseItem(pixelCoords.x(), pixelCoords.y(), 5, 5);
    marker->setBrush(QBrush(Qt::red));

    scene->addItem(marker);
}

MainWindow::~MainWindow()
{
    delete ui;
}
