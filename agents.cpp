#include "Agents.h"
#include <cstdlib>
#include <omp.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <omp.h>
#include <unordered_map>
#include <random>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Mittlerer Abstand zwischen zwei Personen
// 1.800km² -> 1.800.000m²
// 420.000 Personen
// Dichte = 420.000 / 1.800 = 233.33 pro km²
// Mittlerer Abstand = sqrt(1 / 233.33) = 0.065km = 65m

Agents::Agents(float maxX, float maxY, float scale, int gridDimension, int initialS, int initialI, int initialR, float collisionRadius, float avgDistance)
    : maxX(maxX), maxY(maxY), gridDimension(gridDimension), collisionDistance(collisionRadius / (scale * 1000.0f)) {
    cellSize = maxX / gridDimension;
    std::cout << "Cell Size: " << cellSize << std::endl;
    initializeAgents(initialS, initialI, initialR, scale, avgDistance, gridDimension);
    //debugAgentDistribution();
    updateGrid();
    printAgentGrid();
    // printHotspots();
    std::cout << "Scale "<< scale << std::endl;
    std::cout << "Collision Distance: " << collisionDistance << std::endl;
    //printAgentsPerCell();
}

Agents::~Agents() {
    for (auto agent : agents) {
        delete agent;
    }
}

void Agents::debugAgentDistribution() const {
    int borderCount = 0;
    int centerCount = 0;

    for (const auto& agent : agents) {
        if (agent->getX() < cellSize || agent->getX() > maxX - cellSize ||
            agent->getY() < cellSize || agent->getY() > maxY - cellSize) {
            borderCount++;
        } else {
            centerCount++;
        }
    }

    std::cout << "Agents near borders: " << borderCount << "\n";
    std::cout << "Agents in center: " << centerCount << "\n";
}

void Agents::initializeAgents(int initialS, int initialI, int initialR, float scale, float avgDistance, int gridDimension) {
    float cellWidth = maxX / gridDimension;
    float cellHeight = maxY / gridDimension;

    int centerIndex = gridDimension / 2 - 1;
    float cellX = centerIndex * cellWidth;
    float cellY = centerIndex * cellHeight;

    for (int i = 0; i < initialS + initialR; ++i) {
        float startX = static_cast<float>(rand()) / RAND_MAX * maxX;
        float startY = static_cast<float>(rand()) / RAND_MAX * maxY;

        AgentState state = (i < initialS) ? AgentState::Susceptible : AgentState::Recovered;
        agents.push_back(new Agent(startX, startY, state, scale, avgDistance));
    }

    for (int i = 0; i < initialI; ++i) {
        float startX = cellX + static_cast<float>(rand()) / RAND_MAX * cellWidth;
        float startY = cellY + static_cast<float>(rand()) / RAND_MAX * cellHeight;
        agents.push_back(new Agent(startX, startY, AgentState::Infected, scale, avgDistance));
    }
}

void Agents::printAgentGrid() const {

    for (const auto& entry : agentGrid) {
        int cellIndex = entry.first;
        const auto& agentsInCell = entry.second;

        // Berechne die Gitterkoordinaten aus dem Index
        int gridX = cellIndex / gridDimension;
        int gridY = cellIndex % gridDimension;

        std::cout << "Cell (" << gridX << ", " << gridY << "): " << agentsInCell.size() << " agents\n";
    }
}

void Agents::moveAgents(float beta, int& susceptibleCount, int& infectedCount, int& recoveredCount) {
#pragma omp parallel for
    for (auto& agent : agents) {
        agent->move(maxX, maxY);
    }
    updateGrid();
}


void Agents::checkCollisions(int& susceptibleCount, int& infectedCount, int& recoveredCount, float beta) {
    for (const auto& cell : agentGrid) {
        const auto& cellAgents = cell.second;
        for (size_t i = 0; i < cellAgents.size(); ++i) {
            if(cellAgents[i]->getState() == AgentState::Recovered) continue;
            for (size_t j = i + 1; j < cellAgents.size(); ++j) {
                if (cellAgents[j]->getState() == AgentState::Recovered) continue;
                float dx = cellAgents[i]->getX() - cellAgents[j]->getX();
                float dy = cellAgents[i]->getY() - cellAgents[j]->getY();
                float distance = std::sqrt(dx * dx + dy * dy);

                if (distance < collisionDistance) {
                    if (cellAgents[i]->getState() == AgentState::Infected &&
                        cellAgents[j]->getState() == AgentState::Susceptible) {
                        if (static_cast<float>(rand()) / RAND_MAX < beta) {
                            cellAgents[j]->setState(AgentState::Infected);
                            susceptibleCount--;
                            infectedCount++;
                        }
                    } else if (cellAgents[j]->getState() == AgentState::Infected &&
                               cellAgents[i]->getState() == AgentState::Susceptible) {
                        if (static_cast<float>(rand()) / RAND_MAX < beta) {
                            cellAgents[i]->setState(AgentState::Infected);
                            susceptibleCount--;
                            infectedCount++;
                        }
                    }
                }
            }
        }
    }
}

void Agents::printAgents() const {
    for (const auto& agent : agents) {
        std::cout << "Agent at (" << agent->getX() << ", " << agent->getY() << ")\n";
    }
}

void Agents::printAgentStates(int iteration) const {
    int susceptible = 0, infected = 0, recovered = 0;
    for (const auto& agent : agents) {
        switch (agent->getState()) {
        case AgentState::Susceptible: susceptible++; break;
        case AgentState::Infected: infected++; break;
        case AgentState::Recovered: recovered++; break;
        }
    }
    int total = susceptible + infected + recovered;

    std::cout << "Iteration: " << iteration << "\n"
              << "Susceptible: " << susceptible << "\n"
              << "Infected: " << infected << "\n"
              << "Recovered: " << recovered << "\n";
}

int Agents::getCellIndex(float x, float y) const {
    int gridX = std::clamp(static_cast<int>(x / cellSize), 0, gridDimension - 1);
    int gridY = std::clamp(static_cast<int>(y / cellSize), 0, gridDimension - 1);

    return gridX * gridDimension + gridY;
}

void Agents::updateGrid() {
    agentGrid.clear();
    for (auto& agent : agents) {
        int cellIndex = getCellIndex(agent->getX(), agent->getY());
        agentGrid[cellIndex].push_back(agent);
    }
}

const std::vector<Agent*>& Agents::getAgents() const {
    return agents;
}

int Agents::getGridDimension() const {
    return gridDimension;
}

std::vector<Agent*> Agents::getAgentsInCell(int x, int y) const {
    int gridX = std::clamp(static_cast<int>(x / cellSize), 0, gridDimension - 1);
    int gridY = std::clamp(static_cast<int>(y / cellSize), 0, gridDimension - 1);

    int cellIndex = gridX * gridDimension + gridY;
    if (agentGrid.find(cellIndex) != agentGrid.end()) {
        return agentGrid.at(cellIndex);
    } else {
        std::cout << "No agents in cell (" << x << ", " << y << ")\n";
        return std::vector<Agent*>();
    }
}

void Agents::printAgentsPerCell() const {
    std::cout << "Agents per cell:\n";

    for (const auto& entry : agentGrid) {
        int cellIndex = entry.first;
        const auto& agentsInCell = entry.second;

        int gridX = cellIndex / gridDimension;
        int gridY = cellIndex % gridDimension;

        if (!agentsInCell.empty()) {
            std::cout << "Cell (" << gridX << ", " << gridY << "): " << agentsInCell.size() << " agents\n";
        }
        else {
            std::cout << "Cell (" << gridX << ", " << gridY << "): No agents\n";
        }
    }
}

std::vector<std::vector<std::tuple<float, float, float>>> Agents::getAgentStatesByCell() const {
    std::vector<std::vector<std::tuple<float, float, float>>> result(gridDimension, std::vector<std::tuple<float, float, float>>(gridDimension, {0, 0, 0}));

    for (const auto& entry : agentGrid) {
        int cellIndex = entry.first;
        const auto& agentsInCell = entry.second;

        int gridX = cellIndex / gridDimension;
        int gridY = cellIndex % gridDimension;

        int numS = 0, numI = 0, numR = 0;
        for (const auto& agent : agentsInCell) {
            switch (agent->getState()) {
            case AgentState::Susceptible: numS++; break;
            case AgentState::Infected: numI++; break;
            case AgentState::Recovered: numR++; break;
            }
        }

        result[gridX][gridY] = std::make_tuple(numS, numI, numR);
    }

    return result;
}
