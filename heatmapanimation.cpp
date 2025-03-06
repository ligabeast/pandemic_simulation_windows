#include "heatmapanimation.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

HeatmapAnimation::HeatmapAnimation(QGraphicsView *view, QLabel* iterationLabel, QPushButton* playPause, QPushButton* restart, QSlider* speedSlider,  const QString &csvFile)
    : view(view), iterationLabel(iterationLabel), playPauseButton(playPause), restartButton(restart), speedSlider(speedSlider), currentIteration(0), maxIteration(0) {

    scene = new QGraphicsScene();
    view->setScene(scene);
    pixmapItem = new QGraphicsPixmapItem();
    scene->addItem(pixmapItem);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HeatmapAnimation::updateHeatmap);

    playPauseButton->setIcon(QIcon::fromTheme("media-playback-start"));
    connect(playPauseButton, &QPushButton::clicked, this, &HeatmapAnimation::togglePlayPause);

    restartButton->setIcon(QIcon::fromTheme("view-refresh"));
    connect(restartButton, &QPushButton::clicked, this, &HeatmapAnimation::restartAnimation);

    speedSlider->setRange(50, 500);
    speedSlider->setValue(200);
    timer->setInterval(200);
    speedSlider->setInvertedAppearance(true);  // Slider umkehren
    connect(speedSlider, &QSlider::valueChanged, this, &HeatmapAnimation::setAnimationSpeed);

    if (!loadCSV(csvFile)) {
        qDebug() << "Fehler beim Laden der CSV-Datei!";
        return;
    }
    updateHeatmap();
}

void HeatmapAnimation::setAnimationSpeed(int speed) {
    timer->setInterval(speed);
}


void HeatmapAnimation::togglePlayPause() {
    if (timer->isActive()) {
        timer->stop();
        playPauseButton->setIcon(QIcon::fromTheme("media-playback-start"));
    } else {
        timer->start();
        playPauseButton->setIcon(QIcon::fromTheme("media-playback-pause"));
    }
}

void HeatmapAnimation::restartAnimation() {
    timer->stop();
    currentIteration = 0;
    updateHeatmap();
    timer->start();
}

bool HeatmapAnimation::loadCSV(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    QString header = in.readLine();

    if (header.startsWith("GridDimension:")) {
        QStringList parts = header.split(":");
        if (parts.size() == 2) {
            QStringList gridParts = parts[1].trimmed().split("x");
            if (gridParts.size() == 2) {
                gridSize = gridParts[0].toInt();
            }
        }
    } else {
        return false;  // abbrechen
    }

    while (!in.atEnd()) {
        QStringList values = in.readLine().split(',');
        if (values.size() < 6) continue;

        int iteration = values[0].toInt();
        int x = values[1].toInt();
        int y = values[2].toInt();
        double susceptible = values[3].toDouble();
        double infected = values[4].toDouble();
        double recovered = values[3].toDouble();

        maxIteration = qMax(maxIteration, iteration);
        cellData[iteration][{x, y}] = std::make_tuple(susceptible, infected, recovered);
    }

    file.close();
    return true;
}

void HeatmapAnimation::updateHeatmap() {
    if (currentIteration > maxIteration) {
        timer->stop();
        return;
    }

    int containerSize = 400;
    int scale = containerSize / gridSize;

    QImage image(containerSize, containerSize, QImage::Format_RGB32);
    image.fill(Qt::white);  // Hintergrund

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, false);

    // Schwarzer Rand
    QPen borderPen(Qt::black, 1);

    for (auto it = cellData[currentIteration].begin(); it != cellData[currentIteration].end(); ++it) {
        int x = it->first.first;
        int y = it->first.second;

        auto [s, i, r] = it->second;
        double totalPopulation = s + i + r;
        if (totalPopulation == 0) continue; // division 0

        double infectedRatio = i / totalPopulation;
        infectedRatio = std::clamp(infectedRatio / 0.2, 0.0, 1.0);

        QColor color = QColor::fromHsvF(0, infectedRatio, 1.0);

        painter.fillRect(x * scale, y * scale, scale, scale, color);
    }

    QPen gridPen(Qt::black, 1);
    painter.setPen(gridPen);

    for (int x = 1; x < gridSize; ++x) {
        painter.drawLine(x * scale, 0, x * scale, containerSize);
    }
    for (int y = 1; y < gridSize; ++y) {
        painter.drawLine(0, y * scale, containerSize, y * scale);
    }

    painter.end();
    pixmapItem->setPixmap(QPixmap::fromImage(image));

    iterationLabel->setText(QString("Iteration: %1").arg(currentIteration));

    currentIteration++;
}


