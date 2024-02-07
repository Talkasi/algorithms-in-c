#include "vector.h"
#include <stdlib.h>

void STL_vector_init(STL_vector *v, size_t n_bytes) {
	v->data = NULL;
	v->n_bytes = n_bytes;
	v->cur_n = 0;
	v->max_n = 0;
}

int STL_vector_push_back(STL_vector *v, void *new_elem) {
	if (v->cur_n + 1 > v->max_n) {
		void *tmp = realloc(v->data, v->max_n * 2);
		if (tmp == NULL)
			return STL_vector_alloc;
		
		v->data = tmp;
	}

	memcpy((char *)v->data + n_bytes * v->cur_n, new_elem, v->n_bytes);
	++v->cur_n;
	return STL_ok;
}

void *STL_vector_pop_back(STL_vector *v) {
	// TODO(Talkasi): check if realloc is really needed here.
	return (char *)v->data + v->n_bytes * (v->cur_n--);
}

void *STL_vector_destroy(STL_vector *v) {
	free(v->data);
	v->n_bytes = 0;
	v->cur_n = 0;
	v->max_n = 0;
}

size_t STL_vector_size(STL_vector *v) {
	return v->cur_n;
}

