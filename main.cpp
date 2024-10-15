#include <iostream>
#include <vector>
using namespace std;

// Function declarations
bool solveSudoku(vector<vector<int>> &sudoku);
bool isSafe(int row, int col, int num, vector<vector<int>> &sudoku);

int main() {
    vector<vector<int>> sudoku(9, vector<int>(9));

    // Input the Sudoku puzzle from the user
    cout << "Enter the Sudoku puzzle row by row (use 0 for empty cells):" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> sudoku[i][j];
        }
    }

    // Attempt to solve the Sudoku
    if (solveSudoku(sudoku)) {
        cout << "\nSolved Sudoku:\n";
        for (const auto &row : sudoku) {
            for (int num : row) {
                cout << num << " ";
            }
            cout << endl;
        }
    } else {
        cout << "\nNo solution exists for this Sudoku." << endl;
    }

    return 0;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>> &sudoku) {
    // Find an empty cell
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (sudoku[row][col] == 0) {
                // Try placing digits 1-9 in the empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(row, col, num, sudoku)) {
                        sudoku[row][col] = num;  // Place number if it's safe

                        // Recursively try solving the rest of the puzzle
                        if (solveSudoku(sudoku)) {
                            return true;
                        }

                        // If placing num didn't lead to a solution, backtrack
                        sudoku[row][col] = 0;
                    }
                }
                // If no number can be placed in this cell, return false
                return false;
            }
        }
    }
    // If all cells are filled, the puzzle is solved
    return true;
}

// Function to check if placing num at sudoku[row][col] is valid
bool isSafe(int row, int col, int num, vector<vector<int>> &sudoku) {
    // Check if num is already present in the current row or column
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return false;
        }
    }

    // Check if num is already present in the 3x3 sub-grid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j] == num) {
                return false;
            }
        }
    }

    return true;  // Safe to place num
}
