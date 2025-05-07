#ifndef AGENT_H
#define AGENT_H

enum AgentState {
    Susceptible,
    Infected,
    Recovered
};

class Agent {
private:
    float x;
    float y;
    // bool isMobile; -> unused yet. Could be used if one Agent should stay at the same position
    float mobilityFactor;
    AgentState state;
    float scale;
    const float maxDistance;

    // Tag der Erkrankung erfassen und daraus die Genesung ableiten -> Bsp. nach 14 Tagen
public:
    Agent(float startX, float startY, float mobility, AgentState state, float scale, float maxMobility);

    float getX() const;
    float getY() const;
    void setX(float newX);
    void setY(float newY);

    void move(float maxX, float maxY);

    void printDetails() const;

    AgentState getState() const;
    void setState(AgentState newState);
};

#endif
