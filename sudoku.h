#include "constrains.h"
#include <stdlib.h>
#include "list.h"
#define MAX_VALUE 10
#define EMPTY 0
#define AREA_SQUARE_SIZE 3
#define INF 999999

typedef struct {
  int cells[NB_ROWS][NB_COLUMNS];
  Constrains constrains;
} Sudoku;

void initSudoku(Sudoku* sudoku) {
  int i, j;
  for (i = 0; i < NB_ROWS; i++) {
    for (j = 0; j < NB_COLUMNS; j++) {
      sudoku->cells[i][j] = EMPTY;
    }
  }
  initConstrains(&sudoku->constrains);
}

void initSudokuWithValues(Sudoku* sudoku, int inputs[NB_ROWS][NB_COLUMNS]) {
  int i, j;
  for (i = 0; i < NB_ROWS; i++) {
    for (j = 0; j < NB_COLUMNS; j++) {
      sudoku->cells[i][j] = inputs[i][j];
    }
  }
  initConstrains(&sudoku->constrains);
}

void printSudoku(Sudoku sudoku) {
  int i,j;
  printf("Sudoku:\n");
  for (i = 0; i < NB_ROWS; i++) {
    if (i % AREA_SQUARE_SIZE == 0) printf("-------------------------\n");
    for (j = 0; j < NB_COLUMNS; j++) {
      if (j % AREA_SQUARE_SIZE == 0) printf ("| ");
      printf ("%d ", sudoku.cells[i][j]);
    }
    printf("|\n");
  }
  printf("-------------------------\n");
}

int isFilledSudoku(Sudoku sudoku) {
  int i, j;
  for (i = 0; i < NB_ROWS; i++) {
    for (j = 0; j < NB_COLUMNS; j++) {
      if (sudoku.cells[i][j] == EMPTY) return 0;
    }
  }
  return 1;
}

void spreadConstrainsFrom(Coord position, Constrains* constrains, ListCoord* changeds) {
  int row = position.x, column = position.y;
  int i,j;
  for (int i = 0; i < NB_ROWS; i++) {
    if (i != row) {
      Coord pos = {i, column};
      if (addConstrain(constrains, position, pos)) appendListCoord(changeds, pos);
    }
  }
  for (int i = 0; i < NB_COLUMNS; i++) {
    if (i != column) {
      Coord pos = {row, i};
      if (addConstrain(constrains, position, pos)) appendListCoord(changeds, pos);
    } 
  }
  for (int i = 0; i < AREA_SQUARE_SIZE; i++) {
    for (int j = 0; j < AREA_SQUARE_SIZE; j++) {
      int areaX = (row/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
      int areaY = (column/AREA_SQUARE_SIZE) * AREA_SQUARE_SIZE;
      if (areaX+i != row || areaY+j != column) {
        Coord pos = {areaX+i, areaY+j};
        if (addConstrain(constrains, position, pos)) appendListCoord(changeds, pos);
      }
    }
  }
}

void removeConstrainsFrom(Coord position, Constrains* constrains, ListCoord history) {
  int i;
  for (i = 0; i < history.size; i++) {
    removeConstrain(constrains, position, history.data[i]);
  }
}

List getAvailableValues(Coord position, Sudoku sudoku) {
  ListCoord posList = getConstrains(sudoku.constrains, position);
  int availables[MAX_VALUE]; // 0->9 array, just use 1->9
  int i;
  for (i = 1; i < MAX_VALUE; i++) availables[i] = 1;
  for (i = 0; i < posList.size; i++) {
    Coord pos = posList.data[i];
    if (sudoku.cells[pos.x][pos.y] != EMPTY) {
      availables[sudoku.cells[pos.x][pos.y]] = 0;
    }
  }
  List result;
  initList(&result);
  for (int i = 1; i < MAX_VALUE; i++) {
    if (availables[i]) appendList(&result, i);
  }
  return result;
}

Coord getNextEmptyCell(Sudoku sudoku) {
  int i,j;
  for (i = 0; i < NB_ROWS; i++) {
    for (j = 0; j < NB_COLUMNS; j++) {
      Coord pos = {i,j};
      if (sudoku.cells[i][j] == EMPTY) return pos;
    }
  }
}

Coord getNextMinDomainCell(Sudoku sudoku) {
  int minLength = INF;
  Coord result;
  for (int i = 0; i < NB_ROWS; i++) {
    for (int j = 0; j < NB_COLUMNS; j++) {
      if (sudoku.cells[i][j] == EMPTY) {
        Coord pos = {i,j};
        int availablesLength = getAvailableValues(pos, sudoku).size;
        if (availablesLength < minLength) {
          minLength = availablesLength;
          result = pos;
        }
      }
    }
  }
  return result;
}



