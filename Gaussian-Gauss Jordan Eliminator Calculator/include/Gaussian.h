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
    [[nodiscard]] bool isZeroRow(int Row) const;
    void swapRows(int Row1, int Row2);
    void multiplyRow(int Row, double Factor);
    void addRows(int Row1, int Row2, double Factor);
};
