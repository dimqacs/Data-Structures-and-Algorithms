#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "menu.h"
#include "array.h"
#include "read.h"
#include "sort.h"
#include "math.h"
#include "matrix.h"

const int K = 10;

int main(void) {
    unsigned int option, arraySize = 0, matrixSize = 0, oldMatrixSize = 0;

    int *array = NULL;
    int **matrix = NULL;

    const char *options[] = {
        "-------------------------Array-------------------------",
        "Display Array",
        "Fill Array Manually",
        "Fill Array Randomly",
        "Sort Array",
        "-------------------------Matrix------------------------",
        "Display Matrix",
        "Fill Matrix Manually",
        "Fill Matrix Randomly",
        "Sort Matrix",
        "-------------------------------------------------------",
        "Free Space & Exit",
        "-------------------------------------------------------"
    };

    setMenuOptions(options, 13);

    printf("-------------------------Welcome-------------------------\n");

    while (true) {
        displayMenu();

        readUnsignedInt("Introduce an option: ", &option);

        switch (option) {
            case 1:
                displayArray(array, arraySize, "The original Array: ", true);
                break;
            case 2:
                readUnsignedInt("Enter the size of the Array: ", &arraySize);

                if (arraySize == 0 || arraySize % 2 == 1) {
                    arraySize = 0;
                    handleNext("Cannot create Array with size 0 or odd number of elements.");
                    break;
                }
                fillArrayManually(&array, arraySize);
                break;
            case 3:
                readUnsignedInt("Enter the size of the Array: ", &arraySize);

                if (arraySize == 0 || arraySize % 2 == 1) {
                    arraySize = 0;
                    handleNext("Cannot create Array with size 0 or odd number of elements.");
                    break;
                }

                fillArrayRandomly(&array, (int) arraySize);
                break;
            case 4:
                if (arraySize == 0) {
                    handleNext("There is nothing to sort, try adding Array first.");
                    break;
                }

                displayArray(array, arraySize, "The original unsorted Array: ", false);

                // Condition A
                bool sorted = false;

                for (int index = 0; index < arraySize; index++) {
                    if (*(array + index) < 0) {
                        if (index % 2 == 0) {
                            displayArray(heapSortAscending(array, arraySize), arraySize,
                                         "\nA: First negative element is on even position - sorting the Array Ascending using Heap Sort: ",
                                         false);
                            sorted = true;
                        }
                        break;
                    }
                }

                if (!sorted) {
                    displayArray(countSortDescending(array, arraySize), arraySize,
                                 "\nA: First negative element is not on even position - sorting the Array Descending using Count Sort: ",
                                 false);
                }

                // Condition B
                evenSmallerThenOdd(array, arraySize)
                    ? displayArray(radixSortDescending(array, arraySize), arraySize,
                                   "\nB: Sum of even elements is smaller then arithmetic mean of odd elements - sorting Array Descending using Radix Sort: ",
                                   false)
                    : displayArray(combSortAscending(array, arraySize), arraySize,
                                   "\nB: Sum of even elements is not smaller then arithmetic mean of odd elements - sorting Array Ascending using Comb Sort: ",
                                   false);

                // Condition C
                unsigned int primeNumbers = 0;
                for (int index = 0; index < arraySize; index++) {
                    if (isPrime(*(array + index))) {
                        primeNumbers++;
                    }
                }

                primeNumbers >= 2
                    ? displayArray(mergeSortAscending(array, arraySize), arraySize,
                                   "\nC: There are minimum two prime numbers - sorting Ascending Array using Merge Sort: ",
                                   true)
                    : displayArray(bubbleSortDescending(array, arraySize), arraySize,
                                   "\nC: There are less then two prime numbers - sorting Descending Array using Bubble Sort: ",
                                   true);

                break;
            case 5:
                displayMatrix(matrix, matrixSize, "The original Matrix: \n", true);
                break;
            case 6:
                oldMatrixSize = matrixSize;
                readUnsignedInt("Enter the size of the Matrix: ", &matrixSize);

                if (matrixSize == 0) {
                    matrixSize = oldMatrixSize;
                    handleNext("Cannot create Matrix with size 0.");
                    break;
                }

                fillMatrixManually(&matrix, matrixSize, oldMatrixSize);
                break;
            case 7:
                oldMatrixSize = matrixSize;
                readUnsignedInt("Enter the size of the Matrix: ", &matrixSize);

                if (matrixSize == 0) {
                    matrixSize = oldMatrixSize;
                    handleNext("Cannot create Matrix with size 0.");
                    break;
                }

                fillMatrixRandomly(&matrix, matrixSize, oldMatrixSize);
                break;
            case 8:
                if (matrixSize == 0) {
                    handleNext("There is nothing to sort, try adding Matrix first.");
                    break;
                }

                displayMatrix(matrix, matrixSize, "\nThe original unsorted Matrix: \n", false);

                // Condition A
                int multiplication = 1;
                int **sortedMatrix = NULL;
                allocateMatrixMemory(&sortedMatrix, matrixSize, 0);
                equalMatrix(&matrix, &sortedMatrix, matrixSize);

                for (unsigned int row = 0; row < matrixSize; row++) {
                    multiplication *= *(*(matrix + row) + 0);
                }

                if (multiplication > K) {
                    int *mainDiagonal = NULL;
                    allocateArrayMemory(&mainDiagonal, matrixSize);

                    for (unsigned int row = 0; row < matrixSize; row++) {
                        *(mainDiagonal + row) = *(*(matrix + row) + row);
                    }

                    mainDiagonal = quickSortAscending(mainDiagonal, matrixSize);

                    for (unsigned int row = 0; row < matrixSize; row++) {
                        *(*(sortedMatrix + row) + row) = *(mainDiagonal + row);
                    }

                    displayMatrix(sortedMatrix, matrixSize,
                                  "\nA: Multiplication of first column in bigger then global constant K - sorting the main diagonal of Matrix Ascending using Quick Sort:\n",
                                  false);

                    free(mainDiagonal);
                } else {
                    int *secondaryDiagonal = NULL;
                    allocateArrayMemory(&secondaryDiagonal, matrixSize);

                    for (unsigned int row = 0; row < matrixSize; row++) {
                        *(secondaryDiagonal + row) = *(*(matrix + row) + matrixSize - row - 1);
                    }

                    secondaryDiagonal = shellSortDescending(secondaryDiagonal, matrixSize);

                    for (unsigned int row = 0; row < matrixSize; row++) {
                        *(*(sortedMatrix + row) + matrixSize - row - 1) = *(secondaryDiagonal + row);
                    }

                    displayMatrix(sortedMatrix, matrixSize,
                                  "\nA: Multiplication of first column is not bigger then global constant K - sorting the secondary diagonal of Matrix Descending using Shell Sort:\n",
                                  false);

                    free(secondaryDiagonal);
                }

                // Condition B
                equalMatrix(&matrix, &sortedMatrix, matrixSize);

                int minValue = **(matrix);
                unsigned int minValueRow = 0, minValueColumn = 0;
                for (unsigned int row = 0; row < matrixSize; row++) {
                    for (unsigned int column = 0; column < matrixSize; column++) {
                        if (*(*(matrix + row) + column) >= minValue) {
                            continue;
                        }

                        minValue = *(*(matrix + row) + column);
                        minValueRow = row;
                        minValueColumn = column;
                    }
                }

                bool condition = minValueRow % 2 == 1 ? true : false;

                if (!condition) {
                    for (unsigned int row = 1; row < matrixSize && !condition; row += 2) {
                        for (unsigned int column = 0; column < matrixSize; column++) {
                            if (*(*(matrix + row) + column) == minValue) {
                                condition = true;
                                minValueRow = row;
                                break;
                            }
                        }
                    }
                }
                int *sortedLine = NULL;
                allocateArrayMemory(&sortedLine, matrixSize);

                if (condition) {
                    for (unsigned int column = 0; column < matrixSize; column++) {
                        *(sortedLine + column) = *(*(matrix + minValueRow) + column);
                    }

                    sortedLine = selectionSortAscending(sortedLine, matrixSize);

                    for (unsigned int column = 0; column < matrixSize; column++) {
                        *(*(sortedMatrix + minValueRow) + column) = *(sortedLine + column);
                    }

                    displayMatrix(sortedMatrix, matrixSize,
                                  "\nB: The minimal value is at least 1 time on odd row - sorting the row of minimum value of Matrix Ascending using Selection Sort:\n",
                                  true);
                } else {
                    for (unsigned int row = 0; row < matrixSize; row++) {
                        *(sortedLine + row) = *(*(matrix + row) + minValueColumn);
                    }

                    sortedLine = insertionSortDescending(sortedLine, matrixSize);

                    for (unsigned int row = 0; row < matrixSize; row++) {
                        *(*(sortedMatrix + row) + minValueColumn) = *(sortedLine + row);
                    }

                    displayMatrix(sortedMatrix, matrixSize,
                                  "\nB: The minimal value is not on odd row - sorting the column of minimum value of Matrix Descending using Insertion Sort:\n",
                                  true);
                }

                free(sortedLine);
                freeMatrix(&sortedMatrix, matrixSize);
                break;
            case 9:
                free(array);
                printf("Memory cleaned successfully. \n");
                displayByeMessageAndExit();
            default:
                handleNext("Option not defined.");
                break;
        }
    }
}
