/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Program.h
Description : UI IO declarations for Gaussian/Gauss Jordan eliminator calculator program
Author : Chris, Shikomisen (Ayoub)
Mail : christopher.houdt@mds.ac.nz, ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once

#include "Calculations.h"

#include <fstream>

class Program
{
public:
    Program();
    ~Program();

    void run();

private:
    Calculations Matrix; // Input matrix
    Calculations RowEchelonMatrix; // Matrix to store automatic Row Echelon Form for comparison with overloaded == operator
    Calculations ReducedMatrix; // Matrix to store automatic Reduced Row Echelon Form for comparison with overloaded == operator

    void loadAugmentedMatrix(const std::string& Filename);
    void displayAugmentedMatrix() const;
    void performOperations();

    void autoStoreMatrix(); // Function to store auto solve matrices

    void detectResult(const Calculations& ResultMatrix) const; // Function to detect Row Echelon Form/Reduced Row Echelon Form
};
