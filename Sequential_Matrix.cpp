// Necessary libraries to execute the code
#include <iostream> // Input/output stream
#include <cstdlib> // Standard library definitions
#include <ctime> // Date and time functions
#include <chrono> // Time utilities
#include <fstream> // File stream

using namespace std::chrono; // Namespace for time utilities

// Global variable declaring size of matrix
const int MATRIX_SIZE = 500;

// Function to create matrix and save it with random values
void fillRandomMatrix(int matrix[][MATRIX_SIZE])
{
    for (int row = 0; row < MATRIX_SIZE; ++row) // Loop through rows
        for (int col = 0; col < MATRIX_SIZE; ++col) // Loop through columns
            matrix[row][col] = rand() % 100; // Assign random value (0-99) to each element
}

// Multiply two matrices and store the result in a third matrix
void multiplyMatricesAndStoreResult(const int matrixA[][MATRIX_SIZE], const int matrixB[][MATRIX_SIZE], int resultMatrix[][MATRIX_SIZE])
{
    for (int row = 0; row < MATRIX_SIZE; ++row) // Loop through rows of matrix A
    {
        for (int col = 0; col < MATRIX_SIZE; ++col) // Loop through columns of matrix B
        {
            resultMatrix[row][col] = 0; // Initialize result matrix element to 0
            for (int k = 0; k < MATRIX_SIZE; ++k) // Loop through elements of row k of matrix A and column k of matrix B
                resultMatrix[row][col] += matrixA[row][k] * matrixB[k][col]; // Multiply corresponding elements and add to result
        }
    }
}

int main()
{
    srand(time(nullptr)); // Seed random number generator with current time

    int matrixA[MATRIX_SIZE][MATRIX_SIZE]; // First matrix
    int matrixB[MATRIX_SIZE][MATRIX_SIZE]; // Second matrix
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]; // Result matrix

    // Fill matrices with random values
    fillRandomMatrix(matrixA); // Fill matrix A with random values
    fillRandomMatrix(matrixB); // Fill matrix B with random values

    auto startTime = high_resolution_clock::now(); // Start timing

    // Perform matrix multiplication
    multiplyMatricesAndStoreResult(matrixA, matrixB, resultMatrix);

    auto stopTime = high_resolution_clock::now(); // Stop timing

    // Calculate duration
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    std::cout << "Multiplication completed in: " << duration.count() << " microseconds" << std::endl; // Output duration

    // Write result to file
    std::ofstream outputFile("Sequential_Matrix.txt"); // Open file for writing
    for (int row = 0; row < MATRIX_SIZE; ++row) // Loop through rows
    {
        for (int col = 0; col < MATRIX_SIZE; ++col) // Loop through columns
            outputFile << resultMatrix[row][col] << "\t"; // Write element to file
        outputFile << std::endl; // Write newline character
    }
    outputFile << "Execution time: " << duration.count() << " microseconds"; // Write execution time to file
    outputFile.close(); // Close file

    return 0; // Return success
}
