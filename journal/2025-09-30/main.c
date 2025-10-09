#include <limits.h>
#include <stdio.h>

int max_int(int *array, int num_elements) {
	int array_max = INT_MIN;

	for (int i = 0; i < num_elements; i++) {
		if (array[i] > array_max) {
			array_max = array[i];
		}
		// array_max = array[i] > array_max ? array[i] : array_max
	}

	return array_max;
}

int main(int argc, char **argv) {
	char *ptr;

	ptr = "hello  ";
	ptr[0] = 'A';

	puts(ptr);
}
