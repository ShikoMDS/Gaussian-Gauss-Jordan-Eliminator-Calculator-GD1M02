/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Calculations.cpp
Description : Matrix calculation implementations for Gaussian/Gauss Jordan eliminator calculator program
Author : Chris, Shikomisen (Ayoub)
Mail : christopher.houdt@mds.ac.nz, ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "Calculations.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

Calculations::Calculations() = default;

Calculations::~Calculations() = default;

void Calculations::resize(const size_t Rows, const size_t Cols)
{
    AugmentedMatrix.resize(Rows, std::vector<double>(Cols));
}

std::vector<std::vector<double>>& Calculations::getMatrix()
{
    return AugmentedMatrix;
}

void Calculations::displayMatrix() const
{
	for (size_t I = 0; I < AugmentedMatrix.size(); ++I)
    {
        std::cout << "Row " << I << ": ";
        for (const double J : AugmentedMatrix[I])
        {
            if (constexpr double Threshold = 1e-10; std::abs(J) < Threshold)
                std::cout << std::setprecision(2) << 0 << " ";
            else
                std::cout << std::setprecision(2) << J << " ";
        }
        std::cout << std::endl;
    }
}

void Calculations::performRowOperation(const int Row1, const int Row2, const double Factor)
{
    // Check if the rows are within valid range
    if (Row1 < 0 || Row1 >= AugmentedMatrix.size() || Row2 < 0 || Row2 >= AugmentedMatrix.size())
    {
        std::cerr << "Invalid row indices." << std::endl;
        return;
    }

    // Multiply Row1 by Factor
    for (size_t Col = 0; Col < AugmentedMatrix[0].size(); ++Col)
    {
        AugmentedMatrix[Row1][Col] *= Factor;
    }

    // Add Factor * Row2 to Row1
    for (size_t Col = 0; Col < AugmentedMatrix[0].size(); ++Col)
    {
        AugmentedMatrix[Row1][Col] += Factor * AugmentedMatrix[Row2][Col];
    }
}

void Calculations::convertToRowEchelonForm()
{
    const size_t NumRows = AugmentedMatrix.size();
    if (NumRows == 0) return; // Handle empty matrix

    const size_t NumCols = AugmentedMatrix[0].size();
    for (size_t I = 0; I < NumRows; ++I)
    {
        if (AugmentedMatrix[I].size() != NumCols) return; // Handle non-rectangular matrix
    }

    for (size_t PivotRow = 0; PivotRow < NumRows; ++PivotRow)
    {
        // Implementing partial pivoting
        size_t MaxRow = PivotRow;
        double MaxElem = fabs(AugmentedMatrix[PivotRow][PivotRow]);
        for (size_t K = PivotRow + 1; K < NumRows; ++K)
        {
	        const double AbsVal = fabs(AugmentedMatrix[K][PivotRow]);
            if (AbsVal > MaxElem)
            {
                MaxElem = AbsVal;
                MaxRow = K;
            }
        }

        // Swap the rows if necessary
        if (MaxRow != PivotRow)
        {
            std::swap(AugmentedMatrix[MaxRow], AugmentedMatrix[PivotRow]);
        }

        // Check for zero pivot element
        if (AugmentedMatrix[PivotRow][PivotRow] == 0) continue;

        // Make the pivot element 1
        const double PivotElement = AugmentedMatrix[PivotRow][PivotRow];
        for (size_t J = PivotRow; J < NumCols; ++J)
        {
            AugmentedMatrix[PivotRow][J] /= PivotElement;
        }

        // Eliminate other entries in the pivot column
        for (size_t I = PivotRow + 1; I < NumRows; ++I)
        {
            const double Factor = AugmentedMatrix[I][PivotRow];
            for (size_t J = PivotRow; J < NumCols; ++J)
            {
                AugmentedMatrix[I][J] -= Factor * AugmentedMatrix[PivotRow][J];
            }
        }
    }
}

void Calculations::convertToReducedRowEchelonForm()
{
	const size_t NumRows = AugmentedMatrix.size();
	const size_t NumCols = AugmentedMatrix[0].size();

    for (size_t PivotRow = 0; PivotRow < NumRows; ++PivotRow)
    {
        // Find the pivot column for the current pivotRow
        size_t PivotCol = 0;
        while (PivotCol < NumCols && AugmentedMatrix[PivotRow][PivotCol] == 0)
        {
            ++PivotCol;
        }

        // If pivotCol is still less than NumCols, there is a non-zero entry in the pivot column
        if (PivotCol < NumCols)
        {
            // Make the pivot element in the current row equal to 1
            const double PivotElement = AugmentedMatrix[PivotRow][PivotCol];
            for (size_t Col = PivotCol; Col < NumCols; ++Col)
            {
                AugmentedMatrix[PivotRow][Col] /= PivotElement;
            }

            // Eliminate other entries in the pivot column
            for (size_t Row = 0; Row < NumRows; ++Row)
            {
                if (Row != PivotRow)
                {
	                const double Factor = -AugmentedMatrix[Row][PivotCol];
                    for (size_t Col = PivotCol; Col < NumCols; ++Col)
                    {
                        AugmentedMatrix[Row][Col] += Factor * AugmentedMatrix[PivotRow][Col];
                    }
                }
            }
        }
    }

    // Iterate through rows to make leading entries of each row equal to 1 and eliminate other entries in the column
    for (size_t Row = 0; Row < NumRows; ++Row)
    {
        size_t LeadingCol = 0;
        while (LeadingCol < NumCols && AugmentedMatrix[Row][LeadingCol] == 0)
        {
            ++LeadingCol;
        }

        if (LeadingCol < NumCols)
        {
            // Make the leading entry in the current row equal to 1
            const double LeadingElement = AugmentedMatrix[Row][LeadingCol];
            for (size_t Col = LeadingCol; Col < NumCols; ++Col)
            {
                AugmentedMatrix[Row][Col] /= LeadingElement;
            }
        }
    }
}

// Overload operator for "==" to explicitly compare 2 matrices
bool Calculations::operator==(const Calculations& Other) const
{
    if (this->AugmentedMatrix.size() != Other.AugmentedMatrix.size()) {
        return false;
    }

    for (size_t I = 0; I < this->AugmentedMatrix.size(); ++I) {
        if (this->AugmentedMatrix[I].size() != Other.AugmentedMatrix[I].size()) {
            return false;
        }

        for (size_t J = 0; J < this->AugmentedMatrix[I].size(); ++J) {
            if (std::abs(this->AugmentedMatrix[I][J] - Other.AugmentedMatrix[I][J]) > 1e-6) { // 1e-6 is the allowed margin of error
                return false;
            }
        }
    }

    return true;
}

bool Calculations::isZeroRow(const int Row) const
{
    // Check if a row is a zero row
    return std::ranges::all_of(AugmentedMatrix[Row], [](const double Value) { return Value == 0; });
}

void Calculations::swapRows(const int Row1, const int Row2)
{
    // Swap two rows in the matrix
    std::cout << "Before Swap:\n";
    displayMatrix(); // Add this line to display matrix before swap

    if (Row1 < AugmentedMatrix.size() && Row2 < AugmentedMatrix.size())
    {
        std::swap(AugmentedMatrix[Row1], AugmentedMatrix[Row2]);
    }
    else
    {
        std::cerr << "Error: Attempting to swap invalid rows.\n";
        // Add appropriate error handling or exit the program
    }

    std::cout << "After Swap:\n";
    displayMatrix(); // Add this line to display matrix after swap
}

void Calculations::multiplyRow(const int Row, const double Factor)
{
    // Multiply a row by a scalar factor
    for (double& Value : AugmentedMatrix[Row])
    {
        Value *= Factor;
    }
}

void Calculations::divideRow(const int Row, const double Factor)
{
    // Divide a row by a scalar factor
    for (double& Value : AugmentedMatrix[Row])
    {
        Value /= Factor;
    }
}

void Calculations::addRowsMult(const int Row1, const int Row2, const double Factor)
{
    // Add a multiple of Row2 to Row1
    for (size_t Col = 0; Col < AugmentedMatrix[0].size(); ++Col)
    {
        AugmentedMatrix[Row1][Col] += Factor * AugmentedMatrix[Row2][Col];
    }
}

void Calculations::subtractRowsMult(const int Row1, const int Row2, const double Factor)
{
    // Add a multiple of Row2 to Row1
    for (size_t Col = 0; Col < AugmentedMatrix[0].size(); ++Col)
    {
        AugmentedMatrix[Row1][Col] -= Factor * AugmentedMatrix[Row2][Col];
    }
}

void Calculations::addRowsDiv(const int Row1, const int Row2, const double Factor)
{
    // Add a division of Row2 to Row1
    for (size_t Col = 0; Col < AugmentedMatrix[0].size(); ++Col)
    {
        AugmentedMatrix[Row1][Col] += AugmentedMatrix[Row2][Col] / Factor;
    }
}

void Calculations::subtractRowsDiv(const int Row1, const int Row2, const double Factor)
{
    // Add a division of Row2 to Row1
    for (size_t Col = 0; Col < AugmentedMatrix[0].size(); ++Col)
    {
        AugmentedMatrix[Row1][Col] -= AugmentedMatrix[Row2][Col] / Factor;
    }
}
