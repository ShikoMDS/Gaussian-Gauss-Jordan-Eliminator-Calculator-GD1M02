/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Calculations.h
Description : Matrix calculation declarations for Gaussian/Gauss Jordan eliminator calculator program
Author : Chris, Shikomisen (Ayoub)
Mail : christopher.houdt@mds.ac.nz, ayoub.ahmad@mds.ac.nz
**************************************************************************/

#pragma once

#include <vector>

class Calculations
{
public:
    Calculations();
    ~Calculations();

    void resize(double Rows, double Cols);
	std::vector<std::vector<double>>& getMatrix();
    void displayMatrix() const;

    void performRowOperation(int Row1, int Row2, double Factor);
    void convertToRowEchelonForm();
    void convertToReducedRowEchelonForm();

    bool operator==(const Calculations& Other) const; // Overload operator

    [[nodiscard]] bool isZeroRow(int Row) const;

    void swapRows(int Row1, int Row2);
    void multiplyRow(int Row, double Factor);
    void divideRow(int Row, double Factor);
    void addRowsMult(int Row1, int Row2, double Factor);
    void subtractRowsMult(int Row1, int Row2, double Factor);
    void addRowsDiv(int Row1, int Row2, double Factor);
    void subtractRowsDiv(int Row1, int Row2, double Factor);

    // Has problems being private
    std::vector<std::vector<double>> AugmentedMatrix;
};
