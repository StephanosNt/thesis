// Define the size of the Sudoku grid
const GRID_SIZE: i32 = 9;

// Check if a number is safe to place in the given position
function isSafe(grid: StaticArray<StaticArray<i32>>, row: i32, col: i32, num: i32): bool {
  // Check the row and column
  for (let x: i32 = 0; x < GRID_SIZE; x++) {
    if (grid[row][x] == num || grid[x][col] == num) {
      return false;
    }
  }

  // Check the 3x3 subgrid
  let startRow: i32 = row - (row % 3);
  let startCol: i32 = col - (col % 3);
  for (let i: i32 = 0; i < 3; i++) {
    for (let j: i32 = 0; j < 3; j++) {
      if (grid[startRow + i][startCol + j] == num) {
        return false;
      }
    }
  }

  return true;
}

// Solve the Sudoku puzzle
export function solveSudoku(grid: StaticArray<StaticArray<i32>>): bool {
  for (let row: i32 = 0; row < GRID_SIZE; row++) {
    for (let col: i32 = 0; col < GRID_SIZE; col++) {
      if (grid[row][col] == 0) { // Find an empty cell
        for (let num: i32 = 1; num <= 9; num++) {
          if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively try to solve the rest of the grid
            if (solveSudoku(grid)) {
              return true;
            }

            // Backtrack if the solution is not valid
            grid[row][col] = 0;
          }
        }
        return false; // No number fits in this cell
      }
    }
  }

  return true; // Solved
}

// Export a function to initialize the grid and solve it
export function start(gridPointer: usize): bool {
  let grid = load<StaticArray<StaticArray<i32>>>(gridPointer);
  return solveSudoku(grid);
}
