#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFrame>
#include <QFuture>
#include "simulation.h"
#include <QFutureWatcher>
#include <QtCharts>
#include "heatmapanimation.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadMapImage(std::string filepath);
    QPointF geoToPixel(double latitude, double longitude);
    void placeMarker(double latitude, double longitude);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    HeatmapAnimation* heatmap;

    void startSimulation();
    void pauseSimulation();
    void continueSimulation();
    void stopSimulation();
    void openDialog(int durationMinutes, bool agentBased, int S, int I, int R, double beta, double gamma, int dimension, double area, double collisionRadius, double moveToHotspot, double maxMobilityPerDay, double ds, double di, double dr, int iterations, double hotspotRadius);
    void averageDistanceChanged();
    void updateUI();

    void initializeFileList();

    void startHeatmapAnimation(const QString file);

    void createChart1(QVector<QLineSeries*> data);
    QVector<QLineSeries*> loadCSVDataChart1(const QString &filename);

    void initializeCompareList();
    QVector<QPointF> normalizeData(const QVector<QPointF> &data, double totalPopulation);
    double loadTotalPopulation(const QString &filename);
    QVector<QPointF> loadInfectionData(const QString &filename);
    void createComparePlot();

    void onModelChanged(int index);

    QFuture<void> simulationFuture;
    QFutureWatcher<void> simulationWatcher;
    QElapsedTimer simulationTimer;


    Simulation* tmp = nullptr;
    bool isPaused = false;
    bool isRunning = false;
};
#endif
