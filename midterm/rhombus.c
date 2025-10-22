#include <stdio.h>

void rhombus(unsigned int size) {
  for (unsigned int row = 0; row < size; ++row) {
    // shift row to the right to create angle
    for (unsigned int i = (size-1) - row; i > 0; --i) {
      printf(" ");
    }

    for (unsigned int col = 0; col < size; ++col) {
      printf("* ");
    }

    // next row
    printf("\n");
  }
}


int main(void) {
  rhombus(5);
}
