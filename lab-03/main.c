// Name: John Reed
// Class.Section: etec2110-01 Systems Programming
// Lab_Part: 3 'C' Functions, Masking, & Bit-wise Operators

#include <stdio.h>

const unsigned char hexTable[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                  '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void printBinary(unsigned char ch) {
  printf("0b");

  for (unsigned char mask = 0x80; mask > 0; mask >>= 1) {
    if (ch & mask) {
      printf("1");
    } else {
      printf("0");
    }
  }
}

void printHex(unsigned char ch) {
  unsigned char low = ch & 0xF;
  unsigned char high = ch >> 4;
  printf("0x%c%c", hexTable[high], hexTable[low]);
}

void printTable(unsigned char startChar, unsigned char endChar) {
  printf("Table %c to %c:\n\tnum\tch\tbin       \thex \n", startChar, endChar);

  for (unsigned char ch = startChar; ch <= endChar; ch++) {
    printf("\t%d\t%c\t", ch, ch);
    printBinary(ch);
    printf("\t");
    printHex(ch);
    printf("\n");
  }
}

int main(void) { printTable('A', 'Z'); }
