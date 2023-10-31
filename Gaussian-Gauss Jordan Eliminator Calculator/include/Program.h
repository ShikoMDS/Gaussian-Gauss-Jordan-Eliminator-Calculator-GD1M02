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

    void loadAugmentedMatrix(const std::string& Filename);
    void displayAugmentedMatrix() const;
    void performOperations();
};
