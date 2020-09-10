#include "coord.h"
#define MAX_LENGTH 100

typedef struct {
  Coord data[MAX_LENGTH];
  int size;
} ListCoord;

void initListCoord(ListCoord *list) {
  list->size = 0;
}

void appendListCoord(ListCoord *list, Coord coord) {
  list->data[list->size++] = coord;
}