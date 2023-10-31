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
        std::cout << "3. Add a Multiple of Row to Another Row\n";
        std::cout << "4. Convert to Row Echelon Form\n";
        std::cout << "5. Convert to Reduced Row Echelon Form\n";
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
            break;
        case 2:
            int Row;
            double Factor;
            std::cout << "Enter the row and scalar factor (space-separated): ";
            std::cin >> Row >> Factor;
            Matrix.multiplyRow(Row, Factor);
            std::cout << "\nRow multiplied by scalar:\n";
            Matrix.displayMatrix();
            break;
        case 3:
            int TargetRow, SourceRow;
            double AddFactor;
            std::cout << "Enter the target row, source row, and factor (space-separated): ";
            std::cin >> TargetRow >> SourceRow >> AddFactor;
            Matrix.addRows(TargetRow, SourceRow, AddFactor);
            std::cout << "\nMultiple of source row added to target row:\n";
            Matrix.displayMatrix();
            break;
        case 4:
            Matrix.convertToRowEchelonForm();
            std::cout << "\nMatrix converted to Row Echelon Form:\n";
            Matrix.displayMatrix();
            break;
        case 5:
            Matrix.convertToReducedRowEchelonForm();
            std::cout << "\nMatrix converted to Reduced Row Echelon Form:\n";
            Matrix.displayMatrix();
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
