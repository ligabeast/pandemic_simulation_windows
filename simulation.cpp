#include "simulation.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <QThread>
#include <QLabel>

Simulation::Simulation(double beta, double gamma, int initialS, int initialI, int initialR, double DI, double DS, double DR, int gridSize, int h, double collisionRadius, double area, double moveToHotspot, double maxMobility, double hotspotRadius)
    : sirmodel(beta, gamma, initialS, initialI, initialR, gridSize, DI, DS, DR, h),
    initialS(initialS), initialI(initialI), initialR(initialR), beta(beta), gamma(gamma), iteration(0) {
    const int totalAgents = initialS + initialI + initialR;
    // Reale Fläche Deutschlands: ca. 360.000 km²
    // Die Seitenlänge des Quadrats: sqrt(360,000) = 600 km

    // Skaliere Area jenach Anzahl Personen

    const float realArea = area;
    // Optimieren -> sqrt ist teuer
    const float realSide = std::sqrt(realArea);
    const int maxX = 100;
    const int maxY = 100;

    // km pro Einheit
    const float scale = realSide / 100.0f;

    const int numCells = static_cast<int>(std::ceil(totalAgents / 1000));
    const int gridDimension = 3;

    std::cout << "km per unit " << scale << std::endl;

    agents = new Agents(totalAgents, maxX, maxY, scale, gridSize, initialS, initialI, initialR, collisionRadius, moveToHotspot, maxMobility, hotspotRadius);
}

Simulation::~Simulation() {
    delete agents;
}

void Simulation::run(bool agentBased, QLabel* iterationLabel, QProgressBar* s, QProgressBar* i, QProgressBar* r) {
    if (agentBased) {
        std::cout << "Agent-based simulation\n";

        std::vector<std::vector<std::tuple<float, float, float>>> currentIterationData = agents->getAgentStatesByCell();
        cellIterationData.push_back(currentIterationData);
        this->iteration = 1;

        int susceptibleCount = initialS;
        int infectedCount = initialI;
        int recoveredCount = initialR;

        for (; ; ++this->iteration) {

            if (stopFlag) {
                std::cout << "Simulation wird gestoppt." << std::endl;
                break;
            }

            while (pauseFlag) {
                std::cout << "Simulation pausiert..." << std::endl;
                QThread::sleep(1);  // 1 Sekunde warten, dann erneut prüfen
            }

            agents->moveAgents(beta, 0.1, susceptibleCount, infectedCount, recoveredCount);

            agents->checkCollisions(susceptibleCount, infectedCount, recoveredCount, beta);
            // Genesung
            // Alternativ: Tag der Erkrankung speichern und nach 14 Tagen genesen

            for (auto& agent : agents->getAgents()) {
                if (agent->getState() == AgentState::Infected &&
                    ((float)rand() / RAND_MAX) < gamma) {
                    agent->setState(AgentState::Recovered);
                    infectedCount--;
                    recoveredCount++;
                }
            }

            std::vector<std::vector<std::tuple<float, float, float>>> currentIterationData = agents->getAgentStatesByCell();
            cellIterationData.push_back(currentIterationData);

            std::cout << "Iteration: " << this->iteration << std::endl;
            std::cout << "Susceptible: " << susceptibleCount << std::endl;
            std::cout << "Infected: " << infectedCount << std::endl;
            std::cout << "Recovered: " << recoveredCount << std::endl << std::endl;

            double total = susceptibleCount + infectedCount + recoveredCount;
            int percentS = static_cast<int>((susceptibleCount / total) * 100);
            int percentI = static_cast<int>((infectedCount / total) * 100);
            int percentR = static_cast<int>((recoveredCount / total) * 100);

            QMetaObject::invokeMethod(s, "setValue", Qt::QueuedConnection, Q_ARG(int, percentS));
            QMetaObject::invokeMethod(i, "setValue", Qt::QueuedConnection, Q_ARG(int, percentI));
            QMetaObject::invokeMethod(r, "setValue", Qt::QueuedConnection, Q_ARG(int, percentR));
            QMetaObject::invokeMethod(iterationLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, QString("Iteration: %1").arg(this->iteration)));


            if (infectedCount == 0) {
                std::cout << "No more infected individuals. Simulation ends." << std::endl;
                agents->printAgentStates(this->iteration);
                break;
            }
        }
    } else {
        int counter = 0;
        std::cout << "Grid-based sir simulation" << std::endl;

        std::vector<std::vector<std::tuple<float, float, float>>> currentIterationData;
        for (int x = 0; x < sirmodel.getGridSize(); ++x) {
            std::vector<std::tuple<float, float, float>> row;
            for (int y = 0; y < sirmodel.getGridSize(); ++y) {
                const auto& cell = sirmodel.getCell(x, y);
                row.push_back(std::make_tuple(cell.S, cell.I, cell.R));
            }
            currentIterationData.push_back(row);
        }
        cellIterationData.push_back(currentIterationData);
        this->iteration = 1;

        while (true) {

            if (stopFlag) {
                std::cout << "Simulation wird gestoppt." << std::endl;
                break;
            }

            while (pauseFlag) {
                std::cout << "Simulation pausiert..." << std::endl;
                QThread::sleep(1);  // 1 Sekunde warten, dann erneut prüfen
            }

            const bool result = this->sirmodel.iterate(0.01);
            if (!result) {
                std::cout << "No significant change -> break" << std::endl;
                break;
            }

            if (this->sirmodel.getSusceptible() == 0 && this->sirmodel.getInfected() == 0) {
                std::cout << "Everyone is recovered -> break" << std::endl;
                break;
            }

            counter++;
            if (counter == 100) {
                counter = 0;
                std::vector<std::vector<std::tuple<float, float, float>>> currentIterationData;
                for (int x = 0; x < sirmodel.getGridSize(); ++x) {
                    std::vector<std::tuple<float, float, float>> row;
                    for (int y = 0; y < sirmodel.getGridSize(); ++y) {
                        const auto& cell = sirmodel.getCell(x, y);
                        row.push_back(std::make_tuple(cell.S, cell.I, cell.R));
                    }
                    currentIterationData.push_back(row);
                }
                cellIterationData.push_back(currentIterationData);
                this->printState();
                double total = this->sirmodel.getSusceptible() + this->sirmodel.getInfected() + this->sirmodel.getRecovered();
                int percentS = static_cast<int>((this->sirmodel.getSusceptible() / total) * 100);
                int percentI = static_cast<int>((this->sirmodel.getInfected() / total) * 100);
                int percentR = static_cast<int>((this->sirmodel.getRecovered() / total) * 100);

                QMetaObject::invokeMethod(s, "setValue", Qt::QueuedConnection, Q_ARG(int, percentS));
                QMetaObject::invokeMethod(i, "setValue", Qt::QueuedConnection, Q_ARG(int, percentI));
                QMetaObject::invokeMethod(r, "setValue", Qt::QueuedConnection, Q_ARG(int, percentR));
                QMetaObject::invokeMethod(iterationLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, QString("Iteration: %1").arg(this->iteration)));

                this->iteration++;
            }
        }
    }
    this->createCellwiseCSV(agentBased);
}

void Simulation::printState() const {
    int n = this->sirmodel.getSusceptible() + this->sirmodel.getInfected() + this->sirmodel.getRecovered();

    std::cout << "Iteration: " << this->iteration << std::endl
              << "Number of people: " << n << std::endl
              << "Susceptible: " << (this->sirmodel.getSusceptible() / n) * 100 << "% - " << this->sirmodel.getSusceptible() << std::endl
              << "Infected: " << (this->sirmodel.getInfected() / n) * 100 << "% - " << this->sirmodel.getInfected() << std::endl
              << "Recovered: " << (this->sirmodel.getRecovered() / n) * 100 << "% - " << this->sirmodel.getRecovered() << std::endl
              << std::endl;
}

void Simulation::createCellwiseCSV(bool agentBased) const {
    const std::string filename = "cellwise_simulation.csv";
    std::ofstream file(filename);

    int gridDimension = agentBased ? agents->getGridDimension() : sirmodel.getGridSize();

    file << "GridDimension: " << gridDimension << "x" << gridDimension << "\n";
    file << "Iteration,CellX,CellY,Susceptible,Infected,Recovered\n";

    std::cout << "Size of cellIterationData: " << cellIterationData.size() << std::endl;

    for (size_t iteration = 0; iteration < cellIterationData.size(); ++iteration) {
        for (size_t x = 0; x < cellIterationData[iteration].size(); ++x) {
            for (size_t y = 0; y < cellIterationData[iteration][x].size(); ++y) {
                const auto& cellData = cellIterationData[iteration][x][y];
                file << iteration << ", "
                     << x << ", "
                     << y << ", "
                     << std::get<0>(cellData) << ", "
                     << std::get<1>(cellData) << ", "
                     << std::get<2>(cellData) << "\n";
            }
        }
    }

    file.close();
}

void Simulation::pause() {
    pauseFlag = true;
}

void Simulation::resume() {
    pauseFlag = false;
}

void Simulation::stop() {
    stopFlag = true;
}
