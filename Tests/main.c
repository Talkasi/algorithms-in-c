#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define NO_COLOR "\033[0m"

#define DIR "Tests/Data/"
#define ZERO_FILE "00000"
#define SORTED "_S"
#define TEST_FORMAT ".txt"

size_t max(size_t *a, size_t n);
void update_file_name(char *file_name, size_t end_i, size_t new_n);
void *read_int_test_data(FILE *f, size_t n);

int main() {
	size_t tests_info[] = {1, 2, 5, 10, 100, 1000, 5000, 10000};
	size_t tests_n = sizeof(tests_info) / sizeof(tests_info[0]);

	char test[] = DIR ZERO_FILE TEST_FORMAT;
	char result[] = DIR ZERO_FILE SORTED TEST_FORMAT;
	size_t test_i = sizeof(DIR) - 1 + sizeof(ZERO_FILE) - 1 - 1;

	for (size_t i = 0; i < tests_n; ++i) {
		update_file_name(test, test_i, tests_info[i]);
		update_file_name(result, test_i, tests_info[i]);

		FILE *f_test = fopen(test, "r");
		assert(f_test);
		int *test_data = read_int_test_data(f_test, tests_info[i]);
		fclose(f_test);

		FILE *f_result = fopen(result, "r");
		assert(f_result);
		int *result_data = read_int_test_data(f_result, tests_info[i]);
		fclose(f_result);
		
		SelectionSortInt(test_data, tests_info[i]);

		if (memcmp(test_data, result_data, tests_info[i] * sizeof(int)) == 0)
			printf("%s: %s\n", test, GREEN "PASSED" NO_COLOR);
		else
			printf("%s: %s\n", test, RED "FAILED" NO_COLOR);

		free(test_data);
		free(result_data);
	}

	return 0;
}

size_t max(size_t *a, size_t n)
{
	size_t m = a[0];

	for (size_t i = 1; i < n; ++i)
		if (m < a[i])
			m = a[i];

	return m;
}

void update_file_name(char *file_name, size_t end_i, size_t new_n)
{
	for (size_t s = 0; s < sizeof(ZERO_FILE) - 1; ++s) {
		file_name[end_i - s] = new_n % 10 + '0';
		new_n = new_n / 10;
	}
}

void *read_int_test_data(FILE *f, size_t n)
{
	int *data = calloc(n, sizeof(int));
	size_t data_i = 0;
	while (data_i < n && fscanf(f, "%d", &data[data_i]) == 1)
		++data_i;
	return data;
}
