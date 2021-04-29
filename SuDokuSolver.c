#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

// Prints out the board
void printBoard(int grid[][9]){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0 && !(j % 9 == 0)) {
                printf("| ");
            }
            printf("%d ", grid[i][j]);
        }
        if (i == 2 || i == 5) {
            printf("\n");
            printf("---------------------\n");
        }
        else {
            printf("\n");
        }
    }
    printf("\n");
}

// Resets the board to the default values so auto solving algorith can function properly
void clearBoard(int grid[][9]){
  int originalGrid[9][9] = {
                        {0,0,3,0,2,0,6,0,0},
                        {9,0,0,3,0,5,0,0,1},
                        {0,0,1,8,0,6,4,0,0},
                        {0,0,8,1,0,2,9,0,0},
                        {7,0,0,0,0,0,0,0,8},
                        {0,0,6,7,0,8,2,0,0},
                        {0,0,2,6,0,9,5,0,0},
                        {8,0,0,2,0,3,0,0,9},
                        {0,0,5,0,1,0,3,0,0}};

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      grid[i][j] = originalGrid[i][j];
    }
  }
}

// Checks to see if there is another open spot. If there is, it sets the coordinates using pointers
bool checkOpen(int grid[][9], int *row, int *col){
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (grid[i][j] == 0) {
          *row = i;
          *col = j;
          return true;
        }
      }
    }
    return false;
}

// Checks to see if the input value is in the same row as the open spot
bool isInRow(int grid[][9], int row, int value){
    for (int i = 0; i < 9; i++) {
      if (grid[row][i] == value && value != 0) {
        return true;
      }
      
    } 
    return false;
}

// Checks to see if the input value is in the same column as the open spot
bool isInCol(int grid[][9], int col, int value){
    for (int i = 0; i < 9; i++) {
        if (grid[i][col] == value && value != 0) {
          return true;
        }
    } 
    return false;
}

// Checks to see if the input value is already within the 3x3 grid of the open value
bool isInBox(int grid[][9], int row, int col, int value){
    for (int i = row; i < row + 3; i++) {
      for (int j = col; j < col + 3; j++) {
        if (grid[i][j] == value && value != 0) {
          return true;
        }
      }
    }
    return false;
}

// Check to see if user is attempting to place a value in a default filled spot
bool isDefaultValue(int row, int col){
    int originalGrid[9][9] = {
                        {0,0,3,0,2,0,6,0,0},
                        {9,0,0,3,0,5,0,0,1},
                        {0,0,1,8,0,6,4,0,0},
                        {0,0,8,1,0,2,9,0,0},
                        {7,0,0,0,0,0,0,0,8},
                        {0,0,6,7,0,8,2,0,0},
                        {0,0,2,6,0,9,5,0,0},
                        {8,0,0,2,0,3,0,0,9},
                        {0,0,5,0,1,0,3,0,0}};
    
    // Checks to see if the user entered coordinates are already filled by default
    if (originalGrid[row][col] != 0) {
      return true;
    } 
}

// Checks to see if the input value is a valid number to use in the open spot
bool isValid(int grid[][9], int row, int col, int value) {
    if (isDefaultValue(row, col), isInRow(grid, row, value) || isInCol(grid, col, value) || isInBox(grid, row - row % 3, col - col % 3, value) || value < 0) {
      return false;
    }
    else {
      return true; // Returns if the value is valid
    }   
}

// Recursive solving algorithm
bool solveBoard(int grid[][9]){
    int row;
    int col;
    // Base case, checks to see if there is an open spot left 
    if (!checkOpen(grid, &row, &col)) { //If no open spot, board is solved
      return true;
    }
    else { // If there is open spot, assign row and col using checkOpen method
        checkOpen(grid, &row, &col);
    }
    
    // Loop to test input values in current open spot
    for (int i = 1; i < 10; i++) {
      if (isValid(grid, row, col, i)) { // Checks to see if the input value is a valid
        grid[row][col] = i; // Assigns current open spot with i if it is valid
        
        if (solveBoard(grid)){ // Checks to see if board is solved
            return true;
        }
        grid[row][col] = 0; // Sets current open spot back to zero
      }
    }
    return false; 
}

// Checks to see if all of the values in the board have been filled
bool isSolved(int grid[][9]){
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (grid[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

int main(void) {
    // Creates Sudoku Board
    
    int grid[9][9] = {
                    {0,0,3,0,2,0,6,0,0},
                    {9,0,0,3,0,5,0,0,1},
                    {0,0,1,8,0,6,4,0,0},
                    {0,0,8,1,0,2,9,0,0},
                    {7,0,0,0,0,0,0,0,8},
                    {0,0,6,7,0,8,2,0,0},
                    {0,0,2,6,0,9,5,0,0},
                    {8,0,0,2,0,3,0,0,9},
                    {0,0,5,0,1,0,3,0,0}};
                    
    /*
    int grid[9][9] = {
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,1,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0}};
    */
    // Initialization of user values
    int row;
    int col;
    int value;

    // Loop that allows user to play until the board is solved
    while (true) {
      printBoard(grid);
      printf("Enter the row, col, and input value. Enter -1 in each entry to auto-solve\n"); // Prompts user for inputs
      scanf("%d", &row);
      scanf("%d", &col);
      scanf("%d", &value);
      // Handles auto solve function
      if (row == -1 && col == -1 && value == -1) {
        clearBoard(grid);
        solveBoard(grid);
      }
      else {
        // Checks if the user entered values are valid or not
        if (isValid(grid, row, col, value)) {
          grid[row][col] = value;
        }
        else {
          printf("Sorry, invalid value\n");
        }
      }
      // Checks to see if the board is solved
      if(isSolved(grid)){
        printf("Congratulations, you solved the board!\n");
        printBoard(grid);
        break;
      }
    }
    return EXIT_SUCCESS;
}
