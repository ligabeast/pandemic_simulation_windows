#ifndef SIMULATION_H
#define SIMULATION_H

#include "Agents.h"
#include "sirmodel.h"
#include <vector>
#include <tuple>
#include <atomic>
#include <QLabel>
#include <QProgressBar>

class Simulation {
private:
    SIRModel sirmodel;
    Agents* agents;

    int initialS;
    int initialI;
    int initialR;
    double beta;
    double gamma;
    int iteration = 0;

    std::vector<std::vector<std::vector<std::tuple<float, float, float>>>> cellIterationData;

    std::atomic<bool> stopFlag = false;
    std::atomic<bool> pauseFlag = false;

public:
    Simulation(double beta, double gamma, int initialS, int initialI, int initialR, double DI, double DS, double DR, int gridSize, double collisionRadius, double area, double moveToHotspot, double maxMobility, double hotspotRadius);
    ~Simulation();

    void run(bool agentBased, QLabel* t, QProgressBar* s, QProgressBar* i, QProgressBar* r);
    void printState() const;
    void createCellwiseCSV(bool agentBased) const;
    void pause();
    void stop();
    void resume();

};

#endif
