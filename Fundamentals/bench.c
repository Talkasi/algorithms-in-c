#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#define MAX_STACK_SIZE 128
#define N_TESTS 100

typedef struct node node_t;
struct node {
	int n;
	node_t *l;
	node_t *r;
};

void free_tree(node_t *root) {
	if (!root) {
		free_tree(root->l);
		free_tree(root->r);
		free(root);
	}
}

node_t *insert_tree(node_t *root, node_t *new) {
	node_t *tmp = root;
	node_t *prev = NULL;
	while (tmp) {
		prev = tmp;
		if (tmp->n > new->n)
			tmp = tmp->l;
		else
			tmp = tmp->r;
	}

	if (prev == NULL)
		return new;

	else if (prev->n < new->n)
		prev->r = new;
	else
		prev->l = new;

	return root;
}

int dummy;

void visit(node_t *n)
{
    dummy = n->n;
}

void rec_traversal(node_t *root) {
    if (!root)
        return;

    visit(root);
    rec_traversal(root->l);
    rec_traversal(root->r);
}


void stack_traversal(node_t *root) {
	node_t *stack[MAX_STACK_SIZE];
	int stack_size = 0;
    stack[stack_size++] = root;
    while (stack_size) {
        root = stack[--stack_size];
        if (root) {
            visit(root);
            stack[stack_size++] = root->l;
            stack[stack_size++] = root->r;
        }
    }
}

void traversal_print(node_t *root) {
    if (!root)
        return;

    printf("%d ", root->n);
    traversal_print(root->l);
    traversal_print(root->r);
}

int main() {
	node_t *root = NULL;

	srand(time(NULL));
	for (int i = 0; i < MAX_STACK_SIZE; ++i) {
		node_t *new = calloc(1, sizeof(node_t));
		if (!new)
			return 1;
		new->n = rand() % 10000;
		root = insert_tree(root, new);
	}

	unsigned long long all_t = 0;
	for (int i = 0; i < N_TESTS; ++i) {
		unsigned long long start_t = rdtsc();
		rec_traversal(root);
		all_t += rdtsc() - start_t;
	}

	unsigned long long all_t2 = 0;
	for (int i = 0; i < N_TESTS; ++i) {
		unsigned long long start_t = rdtsc();
		stack_traversal(root);
		all_t2 += rdtsc() - start_t;
	}
	printf("Average rdtsc value for recursive traversal: %lld\n", all_t);
	printf("Average rdtsc value for stack traversal: %lld\n", all_t2);
	
	free_tree(root);
	return 0;
}
