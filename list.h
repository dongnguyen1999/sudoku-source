#define MAX_LENGTH 10

typedef struct {
  int data[MAX_LENGTH];
  int size;
} List;

void initList(List *list) {
  list->size = 0;
}

void appendList(List *list, int value) {
  list->data[list->size++] = value;
}

