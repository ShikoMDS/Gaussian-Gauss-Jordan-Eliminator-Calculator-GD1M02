#pragma once

#include <fstream>
#include "Gaussian.h"

class Program
{
public:
    Program();
    ~Program();

    void run();

private:
    Gaussian Matrix;
    Gaussian RowEchelonMatrix;
    Gaussian ReducedMatrix;

    void loadAugmentedMatrix(const std::string& Filename);
    void displayAugmentedMatrix() const;
    void performOperations();

    void autoStoreMatrix();

    void detectResult(const Gaussian& ResultMatrix) const;
};
