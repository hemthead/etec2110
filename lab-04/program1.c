// Name: John Reed
// Class.Section: etec2110.01 Systems Programming
// Lab_Part: 4_I Arrays, Strings, and Flow Control

#include <stdio.h>

void convertToLeetSpeak(char *text) {
  for (; *text; text++) {
    switch (*text) {
    case 'a':
      *text = '@';
      break;

    case 'A':
      *text = '4';
      break;

    case 'b':
      *text = '6';
      break;

    case 'B':
      *text = '8';
      break;

    case 's':
      *text = '5';
      break;

    case 'S':
      *text = '$';
      break;

    case 'e':
    case 'E':
      *text = '3';
      break;

    case 'l':
    case 'L':
      *text = '1';
      break;

    case 'o':
    case 'O':
      *text = '0';
      break;

    case 't':
    case 'T':
      *text = '7';
      break;

    case 'z':
    case 'Z':
      *text = '2';
      break;

    default:
      break;
    }
  }
}

int main(void) {
  char input_string[4001] = {0};

  printf("Message to convert: ");
  fflush(stdout);
  scanf(" %4000[^\n]s", input_string);

  convertToLeetSpeak(input_string);
  printf("Converted message:  %s\n", input_string);
}
