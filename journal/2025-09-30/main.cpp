#include <algorithm>
#include <climits>
#include <cstdio>

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
	int values[100] = {
		-5, 10, 300, -65, -100, 103, 643
	};
	std::printf("%d\n", max_int(values, 100));
	//std::printf("%d\n", *std::max_element(values, values+99));
}
