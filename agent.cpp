#include "Agent.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <QDebug>
#include <random>
#include <cmath>

Agent::Agent(float startX, float startY, float mobility, AgentState state, float scale, float maxMobility)
    : x(std::max(0.0f, static_cast<float>(startX))), y(std::max(0.0f, static_cast<float>(startY))), mobilityFactor(mobility), state(state), scale(scale), maxMobility(maxMobility), maxDistance(maxMobility / scale) {
}

float Agent::getX() const {
    return x;
}

float Agent::getY() const {
    return y;
}


void Agent::move(float maxX, float maxY) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * M_PI);  // Zufallswinkel von 0° bis 360°
    static std::uniform_real_distribution<float> radiusDist(0.0f, maxDistance); // Zufälliger Abstand im Kreis

    float angle = angleDist(gen);
    float distance = radiusDist(gen) * mobilityFactor;

    float deltaX = std::cos(angle) * distance;
    float deltaY = std::sin(angle) * distance;

    x += deltaX;
    y += deltaY;

    // Reflexion
    if (x < 0) { x = -x; }
    if (x > maxX) { x = 2 * maxX - x; }

    if (y < 0) { y = -y; }
    if (y > maxY) { y = 2 * maxY - y; }
}


void Agent::printDetails() const {
    std::cout << "Position: (" << x << ", " << y << "), Mobilität: "
              << mobilityFactor << "\n";
}

AgentState Agent::getState() const {
    return state;
}

void Agent::setState(AgentState newState) {
    // std::cout << "Changing state from " << static_cast<int>(state)
    //           << " to " << static_cast<int>(newState) << std::endl;
    state = newState;
}


void Agent::setX(float newX) {
    x = newX;
}

void Agent::setY(float newY) {
    y = newY;
}
