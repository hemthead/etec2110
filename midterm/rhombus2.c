#include <stdio.h>

void rhombus2(unsigned int size) {
  for (unsigned int row = size; row > 0; --row) {
    for (unsigned int i = row - 1; i > 0; --i) {
      printf(" ");
    }

    for (unsigned int col = size * 2; col > 1; --col) {
      // top and bottom rows
      if (row == 1 || row == size) {
        // hyphens in the center, askterisks in the corners
        if (2 < col && col < size * 2) {
          printf("-");
        } else {
          printf("*");
        }

        continue;
      }

      // slashes on the left and right sides
      if (col == 2 || col == size * 2) {
        printf("/");

        continue;
      }

      // alternate between asterisks and spaces in the center
      if (col % 2) {
        printf(" ");
      } else {
        printf("*");
      }
    }
    printf("\n");
  }
}

int main(void) {
  rhombus2(5);
}
