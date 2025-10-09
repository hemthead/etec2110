// count_characters
// is_palindromic

#include <stdio.h>

int count_characters(char *st, char ch) {
  int count = 0;

  while (*st) {
    if (*st == ch) {
      count++;
    }
    st++;
  }

  return count;
}

int revised_count_characters(char *st, char ch) {
  int count = 0;

  for (; *st; st++) {
    count += *st == ch;
  }

  return count;
}

int is_palindromic(char *st) {
  int len = 0;
  for (char *s = st; *s; s++, len++) {
    ;
  }

  for (int i = 0; i < len; i++) {
    if (st[i] != st[(len-1) - i]) {
      return 0;
    }
  }

  return 1;
}

int main(void) {
  printf("count: %d\npal: %d\n", count_characters("aaaba", 'a'), is_palindromic("kayak"));
  printf("count: %d\npal: %d\n", count_characters("baba is you", 'a'), is_palindromic("nope"));

  printf("count: %d\npal: %d\n", revised_count_characters("aaaba", 'a'), is_palindromic("kayak"));
  printf("count: %d\npal: %d\n", revised_count_characters("baba is you", 'a'), is_palindromic("nope"));
}
