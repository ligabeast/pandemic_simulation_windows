#ifndef SIRMODEL_H
#define SIRMODEL_H

#include <vector>
#include <functional>
class Cell {
public:
    double S;
    double I;
    double R;
};

class SIRModel {
private:
    std::vector<std::vector<Cell>> grid;
    int gridSize;
    double beta;
    double gamma;
    double D_S, D_I, D_R;
    double h;

public:
    SIRModel(double beta, double gamma, double initialS, double initialI, double initialR, int gridSize, double DI, double DS, double DR);

    bool iterate(double dt);

    double computeDiffusion(int x, int y, std::function<double(const Cell &)> field, double h) const;

    void printGridState() const;

    double getSusceptible() const;
    double getInfected() const;
    double getRecovered() const;
    double getBeta() const;
    double getGamma() const;
    int getGridSize() const;
    const Cell &getCell(int x, int y) const;
};

#endif
