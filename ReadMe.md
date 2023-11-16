# Gaussian / Gauss Jordan Eliminator Calculator  
  
Repository created by Chris and Ayoub for GD1M02 Mathematics for Graphical Games Assessment 4 - Final Project.  
  
  
## Table of Contents  
  
- [Description](#Description)  
- [Features](#Features)  
- [Requirements](#Requirements)  
- [Installation](#Installation)  
- [Controls](#Controls)  
- [Disclaimer](#Disclaimer)  
- [Credits](#Credits)  
  
  
## Description  
  
Gaussian / Gauss Jordan Eliminator calculator implemented in C++.  
This program reads from a given text file providing an input augmented matrix with spaces in between the matrix values.  
A Visual Studio 2022 solution is provided, however "main.cpp" and individual source files "/src/" and include files "/include/" can be accessed individually in their respective folders.  
  
  
## Features  
### File Loading  
To load an augmented matrix, the program will load a .txt file named "Gaussian.txt" in the format  
x1 y1 z1 p  
x2 y2 z2 q  
x3 y3 z3 r  
where each value is a whole positive or negative real number value.  
This file should be placed in the projectt folder.  
  
### Implementations  
The output of the following operations have been implemented.  
  
- Swap Rows
- Multiply Row by a Scalar
- Divide Row by a Scalar
- Add a Multiple of Row to Another Row
- Subtract a Multiple of Row to Another Row
- Add a Division of Row to Another Row
- Subtract a Division of Row to Another Row
- Convert to Row Echelon Form
- Convert to Reduced Row Echelon Form
  
- Detection of Row Echelon Form*  
- Detection of Reduced Row Echelon Form*  
  
*There is an issue with precision for the detection of Row Echelon Form and Reduced Row Echelon Form.  
This feature should work for the implemented automatic solver, but most likely will break with manual calculation inputs.  
  
  
## Requirements  
  
- Visual Studio 2022 (v143)  
- Windows SDK 10.0  
- C++ Language Standard: ISO C++20 Standard (/std:c++20)  
- C Language Standard: ISO C17 (2018) Standard (/std:c17)  
- Windows x64  
  
  
## Installation  
  
Download and extract from the .zip file.  
This calculator can be run by opening the "Gaussian-Gauss Jordan Eliminator Calculator.sln" file and built in Debug or Release mode with x64.  
  
  
## Controls  
  
The program has been designed to be operated with standard keyboard and mouse controls.  
  
  
## Disclaimer  
  
All code was written by Chris and Ayoub based off our own knowledge from classes with lecturers and self driven research of the C++ coding language.  
This program is complete for submission. Most issues have been searched for and fixed. While this program is complete, unknown bugs may still be present.  
There have been no input checking methods implemented. This program was designed solely for the computation of matrix calculations and there was no reason to add input error checking. As long as the user follows the instructions provided, the program will work as intended.  
No clear functions have been implemented either, see line above.  
.vs/Gaussian-Gauss Jordan Eliminator Calculator/v17/.suo is included for ease of solution loadup purposes since the solution has been manually configured. The solution should start with x64 Release, on main.cpp and Gaussian.txt in side by side docks.  
  
  
## Credits  
  
2023  
- Chris  
- Shikomisen (Ayoub)  
  
Media Design School  
GD1M02 - Mathematics for Graphical Games  
Written for Assignment 4  
