#include "sudoku.h"

int exploredCounter = 0;
int sudokuBackTracking(Sudoku* sudoku) {
  if (isFilledSudoku(*sudoku)) return 1;
  // Coord position = getNextEmptyCell(*sudoku);
  Coord position = getNextMinDomainCell(*sudoku);
  List availables = getAvailableValues(position, *sudoku);
  if (availables.size == 0) return 0; //ec
  int j;
  for (j = 0; j < availables.size; j++) {
    int value = availables.data[j];
    sudoku->cells[position.x][position.y] = value;
    exploredCounter++;
    ListCoord history;
    initListCoord(&history);
    spreadConstrainsFrom(position, &sudoku->constrains, &history);
    if (sudokuBackTracking(sudoku)) return 1;
    sudoku->cells[position.x][position.y] = EMPTY;
    removeConstrainsFrom(position, &sudoku->constrains, history);
  }
  return 0;
}

Sudoku solveSudoku(Sudoku sudoku) {
  clearConstrains(&sudoku.constrains);
  for (int i = 0; i < NB_ROWS; i++) {
    for (int j = 0; j < NB_COLUMNS; j ++) {
      if (sudoku.cells[i][j] != EMPTY) {
        ListCoord history;
        initListCoord(&history);
        Coord pos = {i, j};
        spreadConstrainsFrom(pos, &sudoku.constrains, &history);
      }
    }
  }
  exploredCounter = 0;
  if (sudokuBackTracking(&sudoku)) printf("Solved\n");
  else printf("Can not solve\n");
  printf("Explored %d states\n", exploredCounter);
  return sudoku;
}

int inputs1[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0 , 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9},
};

int inputs2[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int inputs3[9][9] = {
    {0, 1, 6, 3, 0, 8, 4, 2, 0},
    {8, 4, 0, 0, 0, 0, 7, 3, 0},
    {3, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 6, 0, 9, 4, 0, 8, 0, 2},
    {0, 8, 1, 0, 3, 0, 7, 9, 0},
    {9, 0, 3, 0, 7, 6, 0, 4, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 3},
    {0, 0, 5, 7, 0, 0, 0, 6, 8},
    {0, 7, 8, 1, 0, 3, 2, 5, 0},
};

int inputs4[9][9] = {
    {0, 0, 2, 0, 3, 0, 0, 0, 8},
    {0, 0, 0, 0, 0, 8, 0, 0, 0},
    {0, 3, 1, 0, 2, 0, 0, 0, 0},
    {0, 6, 0, 0, 5, 0, 2, 7, 0},
    {0, 1, 0, 0, 0, 0, 0, 5, 0},
    {2, 0, 4, 0, 6, 0, 0, 3, 1},
    {0, 0, 0, 0, 8, 0, 6, 0, 5},
    {0, 0, 0, 0, 0, 0, 0, 1, 3},
    {0, 0, 5, 3, 1, 0, 4, 0, 0},
};

int inputs5[9][9] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 8, 0, 0, 0, 0, 4, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 6, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int inputs6[9][9] = {
    {0, 6, 1, 0, 0, 7, 0, 0, 3},
    {0, 9, 2, 0, 0, 3, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 8, 5, 3, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 5, 0, 4},
    {5, 0, 0, 0, 0, 8, 0, 0, 0},
    {0, 4, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 1, 6, 0, 8, 0, 0},
    {6, 0, 0, 0, 0, 0, 0, 0, 0},
};

int main() {
  Sudoku sudoku;
  initSudokuWithValues(&sudoku, inputs6);
  printSudoku(sudoku);
  Sudoku result = solveSudoku(sudoku);
  printSudoku(result);
}