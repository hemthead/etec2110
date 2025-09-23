// Name: John Reed
// Class.Section: etec2110-01 Systems Programming
// Lab_Part: 2_I C Language Performance & the Collatz Conjecture

#include <stdio.h>

// Returns the number of iterations in the collatz conjecture required to reach a value of 1. Does
// not include the original number.
int collatz_length(long long int number) {
	int len = 0;

	if (number <= 0) return -1;

	while (number != 1) {
		// collatz
		if (number % 2 == 0) {
			number = number / 2;
		} else {
			number = 3*number + 1;
		}

		len++;
	}

	return len;
}

void collatz_print_sequence(long long int number) {
	if (number <= 0) {
        printf("Error: %lld <= 0, the Collatz Conjecture only applies to positive integers.\n",
			   number);
        return;
	}

	printf("%lld: %lld", number, number);

	while (number != 1) {
		// collatz
		if (number % 2 == 0) {
			number = number / 2;
		} else {
			number = 3*number + 1;
		}

		printf(", %lld", number);
	}

	puts("");
}

int main(int argc, char **argv) {
	int max_len = 0;
	long long int longest_num = 0;

	for (long long int i = 1; i <= 1000000; i++) {
		int i_len = collatz_length(i);
		if (i_len > max_len) {
			max_len = i_len;
			longest_num = i;
		}
	}

	collatz_print_sequence(longest_num);
}
