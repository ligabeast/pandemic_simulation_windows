#include "Agent.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <QDebug>

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
    // Random number between -0.5 and 0.5 and multiply it with mobilityFactor
    // Normalverteilt

    // max 5km pro Tag
    // scale km / einheit
    float deltaX = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.0f * maxDistance * mobilityFactor;
    float deltaY = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.0f * maxDistance * mobilityFactor;

    x += deltaX;
    y += deltaY;

    // Reflektieren vom Rand
    if (x < 0.0f) { x = -x; }
    else if (x > maxX) { x = 2 * maxX - x; }

    if (y < 0.0f) { y = -y; }
    else if (y > maxY) { y = 2 * maxY - y; }
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
