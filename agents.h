#ifndef AGENTS_H
#define AGENTS_H

#include "Agent.h"
#include <vector>
#include <unordered_map>
#include <cmath>

struct Hotspot {
    float centerX;
    float centerY;
    float radius;
};

class Agents {
private:
    std::vector<Agent*> agents;
    std::unordered_map<int, std::vector<Agent*>> agentGrid;
    float cellSize; // Size of each cell in the grid
    int gridDimension;
    float maxX;
    float maxY;
    float collisionDistance;
    float moveToHotspot;

    int getCellIndex(float x, float y) const;

    std::unordered_map<int, Hotspot*> hotspotGrid;
    void initializeHotspots(float scale, float radiusKm);
    void printHotspots() const;
    void checkCollisionsInCell(Agent* movingAgent, int& susceptibleCount, int& infectedCount, int& recoveredCount, float beta);
    void printAgentGrid() const;

public:
    Agents(int totalAgents, float maxX, float maxY, float scale, int gridDimension, int initialS, int initialI, int initialR, float collisionRadius, float moveToHotspot, float maxMobility, float hotspotRadius);
    ~Agents();
    void initializeAgents(int initialS, int initialI, int initialR, float scale, float maxMobility);
    void moveAgents(float beta, int& susceptibleCount, int& infectedCount, int& recoveredCount);
    void checkCollisions(int& susceptibleCount, int& infectedCount, int& recoveredCount, float beta);
    void printAgents() const;
    void printAgentStates(int iteration) const;
    void updateGrid();
    int getGridDimension() const;
    std::vector<Agent*> getAgentsInCell(int x, int y) const;
    void printAgentsPerCell() const;
    const std::vector<Agent*>& getAgents() const;
    void debugAgentDistribution() const;
    std::vector<std::vector<std::tuple<float, float, float>>> getAgentStatesByCell() const;
};

#endif
