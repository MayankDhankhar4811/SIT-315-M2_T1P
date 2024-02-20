#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <omp.h>

using namespace std::chrono;

const int MATRIX_SIZE = 100; // Define the size of the matrices

int matrixA[MATRIX_SIZE][MATRIX_SIZE]; // Declare the first matrix
int matrixB[MATRIX_SIZE][MATRIX_SIZE]; // Declare the second matrix
int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]; // Declare the result matrix

// Function to fill a matrix with random values
void fillRandomMatrix(int matrix[][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 100; // Assign a random value (0-99) to each element
        }
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    fillRandomMatrix(matrixA); // Fill the first matrix with random values
    fillRandomMatrix(matrixB); // Fill the second matrix with random values

    auto start = high_resolution_clock::now(); // Start the timer

    #pragma omp parallel for // Use OpenMP to parallelize the loop
    for (int i = 0; i < MATRIX_SIZE; ++i) { // Loop through rows of the result matrix
        for (int j = 0; j < MATRIX_SIZE; ++j) { // Loop through columns of the result matrix
            resultMatrix[i][j] = 0; // Initialize the result element to 0
            for (int k = 0; k < MATRIX_SIZE; ++k) { // Loop through elements of row k of matrix A and column k of matrix B
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j]; // Multiply corresponding elements and add to result
            }
        }
    }

    auto stop = high_resolution_clock::now(); // Stop the timer
    auto duration = duration_cast<microseconds>(stop - start); // Calculate the duration

    printf("Execution time: %ld microseconds\n", duration.count()); // Print the execution time

    std::ofstream outputFileStream("Open_Matrix.txt"); // Open a file stream for writing

    // Write the result matrix to the file
    for (int i = 0; i < MATRIX_SIZE; ++i) { // Loop through rows
        for (int j = 0; j < MATRIX_SIZE; ++j) { // Loop through columns
            outputFileStream << resultMatrix[i][j] << "\t"; // Write element to file
        }
        outputFileStream << std::endl; // Write newline character
    }

    // Write the execution time to the file
    outputFileStream << "Execution time: " << duration.count() << " microseconds";
    outputFileStream.close(); // Close the file stream

    return 0; // Return success
}
