#include "listcoord.h"
#define NB_ROWS 9
#define NB_COLUMNS 9

typedef struct {
  int data[NB_ROWS*NB_COLUMNS][NB_ROWS*NB_COLUMNS];
  int n;   
} Constrains;

void initConstrains(Constrains* constrains) {
  int i,j;
  for (i = 0; i < NB_ROWS*NB_COLUMNS; i++) {
    for (j = 0; j < NB_ROWS*NB_COLUMNS; j++) {
      constrains->data[i][j] = 0;
    }
  }
  constrains->n = NB_ROWS*NB_COLUMNS;
}

int indexOf(Coord coord) {
  return (NB_ROWS*coord.x + coord.y);
}

Coord positionOfVertex(int vertex) {
  Coord coord;
  coord.x = vertex / NB_ROWS;
  coord.y = vertex % NB_COLUMNS;
  return coord;
}

int addConstrain(Constrains* constrains, Coord source, Coord target) {
  int u = indexOf(source);
  int v = indexOf(target);
  if (constrains->data[u][v] == 0) {
    constrains->data[u][v] = 1;
    constrains->data[v][u] = 1;
    return 1;
  }
  return 0;
}

void removeConstrain(Constrains* constrains, Coord source, Coord target) {
  int u = indexOf(source);
  int v = indexOf(target);
  constrains->data[u][v] = 0;
  constrains->data[v][u] = 0;
}

ListCoord getConstrains(Constrains constrains, Coord coord) {
  int i;
  int v = indexOf(coord);
  ListCoord result;
  initListCoord(&result);
  for (i = 0; i < constrains.n; i ++) {
    if (constrains.data[v][i] == 1) {
      appendListCoord(&result, positionOfVertex(i));
    }
  }
  return result;
}

void clearConstrains(Constrains* constrains) {
  int i,j;
  for (i = 0; i < constrains->n; i++) {
    for (j = 0; j < constrains->n; j++)
    constrains->data[i][j] = 0;
  }
}