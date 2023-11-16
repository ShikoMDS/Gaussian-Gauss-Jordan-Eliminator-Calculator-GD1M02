#pragma once

#include <vector>

class Gaussian
{
public:
    Gaussian();
    ~Gaussian();

    void resize(double Rows, double Cols);
	std::vector<std::vector<double>>& getMatrix();
    void displayMatrix() const;
    void performRowOperation(int Row1, int Row2, double Factor);
    void convertToRowEchelonForm();
    void convertToReducedRowEchelonForm();


    // Has problems being private
    std::vector<std::vector<double>> AugmentedMatrix;
    std::vector<std::vector<double>> AutoSolveMatrix;

    bool operator==(const Gaussian& Other) const;

    [[nodiscard]] bool isZeroRow(int Row) const;
    void swapRows(int Row1, int Row2);
    void multiplyRow(int Row, double Factor);
    void divideRow(int Row, double Factor);
    void addRowsMult(int Row1, int Row2, double Factor);
    void subtractRowsMult(int Row1, int Row2, double Factor);
    void addRowsDiv(int Row1, int Row2, double Factor);
    void subtractRowsDiv(int Row1, int Row2, double Factor);
};
