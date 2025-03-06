#ifndef HEATMAPANIMATION_H
#define HEATMAPANIMATION_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <map>
#include <tuple>
#include <QPushButton>
#include <QSlider>

class HeatmapAnimation : public QObject {
    Q_OBJECT

public:
    HeatmapAnimation(QGraphicsView *view, QLabel* iterationLabel, QPushButton* playPause, QPushButton* restart, QSlider* speedSlider,  const QString &csvFile);

private slots:
    void updateHeatmap();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QLabel *iterationLabel;
    QPushButton* playPauseButton;
    QPushButton* restartButton;
    QSlider* speedSlider;
    QGraphicsPixmapItem *pixmapItem;
    QTimer *timer;
    int gridSize;
    int currentIteration;
    int maxIteration;
    std::map<int, std::map<std::pair<int, int>, std::tuple<double, double, double>>> cellData;

    void togglePlayPause();
    void restartAnimation();
    void setAnimationSpeed(int speed);


    bool loadCSV(const QString &filename);
};

#endif
