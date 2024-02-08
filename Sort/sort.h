#ifndef __SORT_H__
#define __SORT_H__
#include <stddef.h>

typedef int (*comparator_t)(const void *, const void *);

void SelectionSortInt(int a[], size_t n);
void SelectionSort(void *arr, size_t n, size_t b, comparator_t cmp);

void InsertionSortInt(int *a, size_t n);
void InsertionSort(void *arr, size_t n, size_t b, comparator_t cmp);

#endif
