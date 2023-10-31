#include "Gaussian.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

Gaussian::Gaussian() = default;

Gaussian::~Gaussian() = default;

void Gaussian::resize(const double Rows, const double Cols)
{
    AugmentedMatrix.resize(Rows, std::vector<double>(Cols));
}

std::vector<std::vector<double>>& Gaussian::getMatrix()
{
    return AugmentedMatrix;
}

void Gaussian::displayMatrix() const
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

void Gaussian::performRowOperation(const int Row1, const int Row2, const double Factor)
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

void Gaussian::convertToRowEchelonForm()
{
	const size_t NumRows = AugmentedMatrix.size();
	const size_t NumCols = AugmentedMatrix[0].size();

    for (size_t PivotRow = 0; PivotRow < NumRows; ++PivotRow)
    {
        // Find the pivot element in the current row
        const double PivotElement = AugmentedMatrix[PivotRow][PivotRow];

        // Make the pivot element 1
        for (size_t J = PivotRow; J < NumCols; ++J)
        {
            AugmentedMatrix[PivotRow][J] /= PivotElement;
        }

        // Eliminate other entries in the pivot column
        for (size_t I = 0; I < NumRows; ++I)
        {
            if (I != PivotRow)
            {
	            const double Factor = AugmentedMatrix[I][PivotRow];
                for (size_t j = PivotRow; j < NumCols; ++j)
                {
                    AugmentedMatrix[I][j] -= Factor * AugmentedMatrix[PivotRow][j];
                }
            }
        }
    }
}

void Gaussian::convertToReducedRowEchelonForm()
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

        // If pivotCol is still less than numCols, there is a non-zero entry in the pivot column
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

bool Gaussian::isZeroRow(const int Row) const
{
    // Check if a row is a zero row
    return std::ranges::all_of(AugmentedMatrix[Row], [](const double Value) { return Value == 0; });
}

void Gaussian::swapRows(const int Row1, const int Row2)
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

void Gaussian::multiplyRow(const int Row, const double Factor)
{
    // Multiply a row by a scalar factor
    for (double& Value : AugmentedMatrix[Row])
    {
        Value *= Factor;
    }
}

void Gaussian::addRows(const int Row1, const int Row2, const double Factor)
{
    // Add a multiple of Row2 to Row1
    for (size_t Col = 0; Col < AugmentedMatrix[0].size(); ++Col)
    {
        AugmentedMatrix[Row1][Col] += Factor * AugmentedMatrix[Row2][Col];
    }
}
