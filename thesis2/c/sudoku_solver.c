#include <stdio.h>
#include <stdbool.h>
#include <time.h> // Include the time.h library for execution time

#define GRID_SIZE 9

// Function to print the Sudoku grid
void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

// Check if it's safe to place a number in the given cell
bool isSafe(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int num) {
    // Check if the number is in the row or column
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check if the number is in the 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

// Solve the Sudoku grid using backtracking
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) { // Find an empty cell
                for (int num = 1; num <= GRID_SIZE; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;

                        // Recursively try to solve the rest of the grid
                        if (solveSudoku(grid)) {
                            return true;
                        }

                        // Backtrack if placing num doesn't lead to a solution
                        grid[row][col] = 0;
                    }
                }
                return false; // No number fits in this cell
            }
        }
    }
    return true; // Solved
}

// Entry point for solving a Sudoku puzzle
int main() {
    int grid[GRID_SIZE][GRID_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},
    };

    printf("Initial Sudoku Puzzle:\n");
    printGrid(grid);

    // Start measuring time
    clock_t start = clock();

    if (solveSudoku(grid)) {
        // End measuring time
        clock_t end = clock();
        printf("\nSolved Sudoku Puzzle:\n");
        printGrid(grid);

        // Calculate and print execution time in seconds
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("\nExecution Time: %.6f seconds\n", time_taken);
    } else {
        printf("\nNo solution exists for the given Sudoku puzzle.\n");
    }

    return 0;
}
