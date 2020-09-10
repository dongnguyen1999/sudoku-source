#include <stdio.h>

typedef struct {
  int x, y;
} Coord;

void printCoord(Coord coord) {
  printf("(%d, %d)\n", coord.x, coord.y);
}

