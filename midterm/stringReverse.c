#include <stdio.h>

void stringReverse(char *string) {
  char *ep;
  for (ep = string; *ep; ++ep) {
    ;
  }
  --ep; // don't count null terminator

  for (char *sp = string; ep > sp; ++sp, --ep) {
    char tmp = *sp;
    *sp = *ep;
    *ep = tmp;
  }
}

int main(void) {
  char buffer[] = "Hello World!";
  stringReverse(buffer);
  printf("%s\n", buffer);
}
