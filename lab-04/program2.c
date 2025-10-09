// Name: John Reed
// Class.Section: etec2110-01 Systems Programming
// Lab_Part: 4 Arrays, Strings, and Flow Control _ Program I

#include <stddef.h>
#include <stdio.h>
#include <string.h>

// Encryptes `message` of length `length` in-place using XOR encryption with
// `key`. Only the first 40 characters of `key` are used, at most.
void crypt(char *message, int length, char *key) {
  size_t key_len = strnlen(key, 40);
  // code to encrypt the message using XOR with the key string.
  for (unsigned int i = 0; i < length; i++, message++) {
    *message ^= key[i % key_len];
  }
}

int main(void) {
  char input_string[4001] = {0};
  char key_string[41] = {0};

  printf("Message to convert: ");
  fflush(stdout);
  scanf(" %4000[^\n]s", input_string);

  printf("Conversion key: ");
  fflush(stdout);
  scanf(" %40[^\n]s", key_string);

  size_t input_len = strnlen(input_string, 40);

  crypt(input_string, input_len, key_string);
  printf("Encrypted: %s\n", input_string);

  crypt(input_string, input_len, key_string);
  printf("Decrypted: %s\n", input_string);
}
