#include "sirmodel.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

SIRModel::SIRModel(double beta, double gamma, double initialS, double initialI, double initialR, int gridSize, double DI, double DS, double DR, double h)
    : gridSize(gridSize), beta(beta), gamma(gamma), D_I(DI), D_S(DS), D_R(DR), h(h) {
    grid = std::vector<std::vector<Cell>>(gridSize, std::vector<Cell>(gridSize));

    int totalCells = gridSize * gridSize;
    double distributedS = initialS / totalCells;
    double distributedR = initialR / totalCells;

    double totalNoiseS = 0.0;
    double totalNoiseR = 0.0;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            double randomNoiseS = ((static_cast<double>(std::rand()) / RAND_MAX) - 0.5) * 0.1 * distributedS;
            double randomNoiseR = ((static_cast<double>(std::rand()) / RAND_MAX) - 0.5) * 0.1 * distributedR;

            totalNoiseS += randomNoiseS;
            totalNoiseR += randomNoiseR;

            grid[i][j].S = distributedS + randomNoiseS;
            grid[i][j].R = distributedR + randomNoiseR;
            grid[i][j].I = 0.0;

        }
    }

    double correctionS = -totalNoiseS / totalCells;
    double correctionR = -totalNoiseR / totalCells;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j].S = std::max(0.0, grid[i][j].S + correctionS);
            grid[i][j].R = std::max(0.0, grid[i][j].R + correctionR);
        }
    }



    int remainingInfected = static_cast<int>(initialI);
    while (remainingInfected > 0) {
        int randomX = std::rand() % gridSize;
        int randomY = std::rand() % gridSize;

        grid[randomX][randomY].I += 1.0;
        remainingInfected--;

    }

    // TODO Hotspots

    printGridState();
}

bool SIRModel::iterate(double dt) {
    std::vector<std::vector<Cell>> newGrid = grid;

    // Anpassen an die Skalierung des Grids

    // h tatsächlicher Abstand zwischen zwei Gitterpunkten
    // GridDimension = 10
    // km per unit 0.134164
    // Total 100x100
    // 0.134164 * 100 = 13.4164 km
    // 13.4164 / 10 = 1.34164 km
    // h = 1.34164 km
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            Cell &cell = grid[x][y];
            Cell &newCell = newGrid[x][y];

            double localN = cell.S + cell.I + cell.R;
            if (localN == 0) continue;

            double infectionPart = beta * cell.S * cell.I / localN;
            double recoveryPart = gamma * cell.I;

            double diffusionS = D_S * computeDiffusion(x, y, [](const Cell &c) { return c.S; }, this->h);
            double diffusionI = D_I * computeDiffusion(x, y, [](const Cell &c) { return c.I; }, this->h);
            double diffusionR = D_R * computeDiffusion(x, y, [](const Cell &c) { return c.R; }, this->h);

            double deltaS = (-infectionPart + diffusionS) * dt;
            double deltaI = (infectionPart - recoveryPart + diffusionI) * dt;
            double deltaR = (recoveryPart + diffusionR) * dt;

            newCell.S = std::max(0.0, cell.S + deltaS);
            newCell.I = std::max(0.0, cell.I + deltaI);
            newCell.R = std::max(0.0, cell.R + deltaR);

            // Normalisierung
            double total = newCell.S + newCell.I + newCell.R;
            if (total > 0) {
                newCell.S *= localN / total;
                newCell.I *= localN / total;
                newCell.R *= localN / total;
            }
        }
    }

    grid = newGrid;

    double totalS = this->getSusceptible();
    double totalI = this->getInfected();
    double totalR = this->getRecovered();

    // Änderungsrate zu klein -> break

    if (totalR / (totalS + totalI + totalR) >= 0.95) {
        return false; // > 95% der Bevölkerung ist immun
    }
    if (totalI < 0.5) {
        return false; // < 0.5% der Bevölkerung ist infiziert
    }

    return true; // Simulation fortsetzen
}

double SIRModel::computeDiffusion(int x, int y, std::function<double(const Cell &)> field, double h) const {
    double center = field(grid[x][y]);

    // TODO h in formel wieso nicht hier
    double left = (x > 0) ? field(grid[x - 1][y]) : 0;
    double right = (x < gridSize - 1) ? field(grid[x + 1][y]) : 0;
    double up = (y > 0) ? field(grid[x][y - 1]) : 0;
    double down = (y < gridSize - 1) ? field(grid[x][y + 1]) : 0;

    return (left + right + up + down - 4 * center) / (h * h);
}


void SIRModel::printGridState() const {
    std::cout << "Initial Grid State:\n";
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            const Cell& cell = grid[i][j];
            std::cout << "Cell (" << i << ", " << j << "): "
                      << "S=" << cell.S << ", "
                      << "I=" << cell.I << ", "
                      << "R=" << cell.R << "\n";
        }
    }
}

double SIRModel::getSusceptible() const {
    double totalS = 0.0;
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            totalS += grid[x][y].S;
        }
    }
    return totalS;
}

double SIRModel::getInfected() const {
    double totalI = 0.0;
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            totalI += grid[x][y].I;
        }
    }
    return totalI;
}

double SIRModel::getRecovered() const {
    double totalR = 0.0;
    for (int x = 0; x < gridSize; ++x) {
        for (int y = 0; y < gridSize; ++y) {
            totalR += grid[x][y].R;
        }
    }
    return totalR;
}

double SIRModel::getBeta() const {
    return beta;
}

double SIRModel::getGamma() const {
    return gamma;
}

int SIRModel::getGridSize() const {
    return gridSize;
}

const Cell& SIRModel::getCell(int x, int y) const {
    if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
        std::cerr << "Invalid cell index: (" << x << ", " << y << ")\n";
        return grid[0][0];
    }
    return grid[x][y];
}
