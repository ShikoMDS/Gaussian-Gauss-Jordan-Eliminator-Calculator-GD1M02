/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) [Year] Media Design School
File Name : Program.cpp
Description : Main UI IO implementations for Gaussian/Gauss Jordan eliminator calculator program
Author : Chris, Shikomisen (Ayoub)
Mail : christopher.houdt@mds.ac.nz, ayoub.ahmad@mds.ac.nz
**************************************************************************/

#include "Program.h"

#include <iostream>

Program::Program() = default;

Program::~Program() = default;

void Program::run()
{
	const std::string Filename = "Gaussian.txt";
    loadAugmentedMatrix(Filename);

    std::cout << "Initial Augmented Matrix:" << std::endl;
    displayAugmentedMatrix();

    autoStoreMatrix();

    performOperations();
}

void Program::loadAugmentedMatrix(const std::string& Filename)
{
    std::ifstream InputFile(Filename);
    if (!InputFile)
    {
        std::cerr << "Error opening file." << std::endl;
        throw std::runtime_error("Failed to open file.");
    }
    
    Matrix.AugmentedMatrix.resize(3, std::vector<double>(4));

    // Read augmented matrix
    for (int I = 0; I < 3; ++I)
    {
        for (int J = 0; J < 4; ++J)
        {
            InputFile >> Matrix.AugmentedMatrix[I][J];
            // Check for negative components and adjust accordingly
            if (InputFile.peek() == '-')
            {
                InputFile.ignore(); // Ignore the '-' character
                Matrix.AugmentedMatrix[I][J] *= -1; // Negate the number
            }
        }
    }

    // Close the file
    InputFile.close();
}

void Program::displayAugmentedMatrix() const
{
    Matrix.displayMatrix();
}

void Program::performOperations()
{
    int Choice;

    do
    {
        std::cout << "\nChoose an operation:\n";
        std::cout << "1. Swap Rows\n";
        std::cout << "2. Multiply Row by a Scalar\n";
        std::cout << "3. Divide Row by a Scalar\n";
        std::cout << "4. Add a Multiple of Row to Another Row\n";
        std::cout << "5. Subtract a Multiple of Row to Another Row\n";
        std::cout << "6. Add a Division of Row to Another Row\n";
        std::cout << "7. Subtract a Division of Row to Another Row\n";
        std::cout << "8. Convert to Row Echelon Form\n";
        std::cout << "9. Convert to Reduced Row Echelon Form\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> Choice;

        switch (Choice)
        {
        case 1:
            int Row1, Row2;
            std::cout << "Enter the rows to swap (space-separated): ";
            std::cin >> Row1 >> Row2;
            Matrix.swapRows(Row1, Row2);
            std::cout << "\nRows swapped:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 2:
            int RowMult;
            double FactorMult;
            std::cout << "Enter the row and scalar factor (space-separated): ";
            std::cin >> RowMult >> FactorMult;
            Matrix.multiplyRow(RowMult, FactorMult);
            std::cout << "\nRow multiplied by scalar:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 3:
            int RowDiv;
            double FactorDiv;
            std::cout << "Enter the row and scalar factor (space-separated): ";
            std::cin >> RowDiv >> FactorDiv;
            Matrix.divideRow(RowDiv, FactorDiv);
            std::cout << "\nRow divided by scalar:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 4:
            int TargetRowAddMult, SourceRowAddMult;
            double AddFactorMult;
            std::cout << "Enter the target row, source row, and factor (space-separated): ";
            std::cin >> TargetRowAddMult >> SourceRowAddMult >> AddFactorMult;
            Matrix.addRowsMult(TargetRowAddMult, SourceRowAddMult, AddFactorMult);
            std::cout << "\nMultiple of source row added to target row:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 5:
            int TargetRowSubMult, SourceRowSubMult;
            double SubFactorMult;
            std::cout << "Enter the target row, source row, and factor (space-separated): ";
            std::cin >> TargetRowSubMult >> SourceRowSubMult >> SubFactorMult;
            Matrix.subtractRowsMult(TargetRowSubMult, SourceRowSubMult, SubFactorMult);
            std::cout << "\nMultiple of source row subtracted to target row:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 6:
            int TargetRowAddDiv, SourceRowAddDiv;
            double AddFactorDiv;
            std::cout << "Enter the target row, source row, and factor (space-separated): ";
            std::cin >> TargetRowAddDiv >> SourceRowAddDiv >> AddFactorDiv;
            Matrix.addRowsDiv(TargetRowAddDiv, SourceRowAddDiv, AddFactorDiv);
            std::cout << "\nDivision of source row added to target row:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 7:
            int TargetRowSubDiv, SourceRowSubDiv;
            double SubFactorDiv;
            std::cout << "Enter the target row, source row, and factor (space-separated): ";
            std::cin >> TargetRowSubDiv >> SourceRowSubDiv >> SubFactorDiv;
            Matrix.subtractRowsDiv(TargetRowSubDiv, SourceRowSubDiv, SubFactorDiv);
            std::cout << "\nDivision of source row subtracted to target row:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 8:
            Matrix.convertToRowEchelonForm();
            std::cout << "\nMatrix converted to Row Echelon Form:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 9:
            Matrix.convertToReducedRowEchelonForm();
            std::cout << "\nMatrix converted to Reduced Row Echelon Form:\n";
            Matrix.displayMatrix();
            detectResult(Matrix);
            break;
        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (Choice != 0);
}

void Program::autoStoreMatrix()
{
    RowEchelonMatrix = Matrix;
    ReducedMatrix = Matrix;

    RowEchelonMatrix.convertToRowEchelonForm();
    ReducedMatrix.convertToReducedRowEchelonForm();
}

void Program::detectResult(const Calculations& ResultMatrix) const
{
    if (ResultMatrix == RowEchelonMatrix)
    {
        std::cout << "\nMatrix is in Row Echelon form!\n";
    }
    if (ResultMatrix == ReducedMatrix)
    {
        std::cout << "\nMatrix is in Reduced Row Echelon form!\n";
    }
}

