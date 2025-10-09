// Name: John Reed
// Class.Section: etec2110-01 Systems Programming

// I'm bored

#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 1

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

struct ThreadCollatzRet {
	long long int number;
	int len;
};

struct ThreadCollatzArgs {
	long long int number;
	long long int max_num;
	struct ThreadCollatzRet *results;
};

void* thread_collatz_length(void* arguments) {
	struct ThreadCollatzArgs *args = (struct ThreadCollatzArgs *)(arguments);

	int max_len = 0;
	long long int longest_num = 0;

	for (long long int i = args->number; i <= args->max_num; i += NUM_THREADS) {
		int i_len = collatz_length(i);
		if (i_len > max_len) {
			max_len = i_len;
			longest_num = i;
		}
	}

	args->results->number = longest_num;
	args->results->len = max_len;

	return NULL;
}

int find_max_collatz() {
	long long int max_num = 100;

	pthread_t threads[NUM_THREADS];
	struct ThreadCollatzArgs thread_args[NUM_THREADS];
	struct ThreadCollatzRet thread_results[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++) {
		thread_args[i].number = i;
		thread_args[i].max_num = max_num;
		thread_args[i].results = &thread_results[i];

		pthread_create(&threads[i], NULL, thread_collatz_length, &thread_args[i]);
	}

	int max_len = 0;
	long long int longest_num = 0;
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);

		if (thread_results[i].len > max_len) {
			max_len = thread_results[i].len;
			longest_num = thread_results[i].number;
		}
	}
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
