#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct {
	void *data;

	size_t n_bytes;
	size_t cur_n;
	size_t max_n;
} STL_vector;

void STL_vector_init(STL_vector *v, size_t n_bytes);
int STL_vector_push_back(STL_vector *v, void *new_elem);
void *STL_vector_pop_back(STL_vector *v);
void *STL_vector_destroy(STL_vector *v);
size_t STL_vector_size(STL_vector *v);

#endif