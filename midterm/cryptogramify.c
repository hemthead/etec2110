
#include <stdio.h>
void cryptogramify(char *message) {
  // alphabet in reverse order
  const char alpha_rev[26] = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

  for (char *c = message; *c; ++c) {
    // if uppercase character, use reversed alphabet to map to opposite end.
    if ('A' <= *c && *c <= 'Z') {
      // translate character into offset into alphabet and look up, set
      // character to opposite
      *c = alpha_rev[*c - 'A'];
    }

    // if lowercase character, use reversed alphabet to map to opposite end.
    if ('a' <= *c && *c <= 'z') {
      // translate character into offset and look up, result is uppercase
      // opposite
      char opposite_upper = alpha_rev[*c - 'a'];

      // translate uppercase result into lowercase by adding offset between
      // cases, and set character
      *c = opposite_upper + ('a' - 'A');
    }

    // ignore non-alphabetic characters
  }
}

int main(void) {
  char buffer[] = "DSVM BLF XLNV GL Z ULIP RM GSV ILZW, GZPV RG. - BLTR YVIIZ";
  cryptogramify(buffer);
  printf("%s\n", buffer);
}
