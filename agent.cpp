#include "Agent.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <QDebug>
#include <random>
#include <cmath>

Agent::Agent(float startX, float startY, AgentState state, float scale, float avgDistance)
    : x(std::max(0.0f, static_cast<float>(startX))), y(std::max(0.0f, static_cast<float>(startY))), state(state), avgDistance(avgDistance) {
}

float Agent::getX() const {
    return x;
}

float Agent::getY() const {
    return y;
}


void Agent::move(float maxX, float maxY) {
    // ------------------------------------------------------------
    // Bewegung erfolgt über eine Normalverteilung:
    //
    //     f(d) = (1 / (σ * sqrt(2π))) * exp( -0.5 * ((d - μ)/σ)^2 )
    //
    // Gegeben:
    //     - avgDistance = μ = gewünschter Mittelwert, z.B. 10 km
    //     - 99 % der Bewegungen sollen im Bereich [μ ± 50 %] liegen,
    //       also in [0.5 × μ, 1.5 × μ] → z.B. [5 km, 15 km]
    //
    // Für Normalverteilungen gilt:
    //     [μ - 2.576σ, μ + 2.576σ] ≈ 99 %
    //
    // Um σ zu berechnen:
    //     μ - 2.576σ = 0.5 × μ
    //     ⇒ 2.576σ = μ - 0.5μ = 0.5μ
    //     ⇒ σ = 0.5μ / 2.576 ≈ 0.194 × μ

    float sigma = 0.194f * avgDistance;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> angleDist(0.0f, 2.0f * M_PI);
    std::normal_distribution<float> distanceDist(avgDistance, sigma);

    float angle = angleDist(gen);
    float distance = distanceDist(gen);

    // Bewegung auf realistische Werte begrenzen max. 3σ
    distance = std::clamp(distance, 0.0f, avgDistance + 3 * sigma);

    float deltaX = std::cos(angle) * avgDistance;
    float deltaY = std::sin(angle) * avgDistance;

    x += deltaX;
    y += deltaY;

    // Reflexion
    if (x < 0)     x = -x;
    if (x > maxX)  x = 2 * maxX - x;
    if (y < 0)     y = -y;
    if (y > maxY)  y = 2 * maxY - y;
}



void Agent::printDetails() const {
    std::cout << "Position: (" << x << ", " << y << ")" << std::endl;
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
