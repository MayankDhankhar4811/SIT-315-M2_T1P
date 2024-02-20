#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <pthread.h>

using namespace std::chrono;

const int MATRIX_SIZE = 500; // Define the size of the matrices
#define MAX_THREADS 20 // Define the maximum number of threads

int matrixA[MATRIX_SIZE][MATRIX_SIZE]; // Declare the first matrix
int matrixB[MATRIX_SIZE][MATRIX_SIZE]; // Declare the second matrix
int resultMatrix[MATRIX_SIZE][MATRIX_SIZE]; // Declare the result matrix
int threadCounter = 0; // Initialize a counter for the threads
int partitionSize = MATRIX_SIZE / MAX_THREADS; // Calculate the partition size for each thread

// Function to fill a matrix with random values
void fillRandomMatrix(int matrix[][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 100;
        }
    }
}

// Function to multiply matrices in a thread
void *multiplyMatricesThread(void *args) {
    int threadID = threadCounter++; // Get the thread ID

    // Iterate over the rows assigned to this thread
    for (int i = threadID * partitionSize; i < (threadID + 1) * partitionSize; ++i) {
        // Iterate over the columns of the result matrix
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            resultMatrix[i][j] = 0; // Initialize the result element to 0
            // Iterate over the columns of the first matrix or the rows of the second matrix
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                // Multiply the corresponding elements and add to the result
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    srand(time(0)); // Seed the random number generator

    fillRandomMatrix(matrixA); // Fill the first matrix with random values
    fillRandomMatrix(matrixB); // Fill the second matrix with random values

    auto start = high_resolution_clock::now(); // Start the timer

    pthread_t threadArray[MAX_THREADS]; // Declare an array to hold thread IDs

    // Create threads to multiply matrices
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_create(&threadArray[i], NULL, &multiplyMatricesThread, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_THREADS; ++i) {
        pthread_join(threadArray[i], NULL);
    }

    auto stop = high_resolution_clock::now(); // Stop the timer
    auto duration = duration_cast<microseconds>(stop - start); // Calculate the duration

    printf("Execution time: %ld microseconds", duration.count()); // Print the execution time

    std::ofstream outputFileStream("Parallel_Matrix.txt"); // Open a file stream for writing

    // Write the result matrix to the file
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            outputFileStream << resultMatrix[i][j] << "\t";
        }
        outputFileStream << std::endl;
    }

    // Write the execution time to the file
    outputFileStream << "Execution time: " << duration.count() << " microseconds";
    outputFileStream.close(); // Close the file stream

    return 0; // Return success
}
