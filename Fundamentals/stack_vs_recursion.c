#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

struct stack {
	node_t *data[MAX_STACK_SIZE];
	int i;
};

int dummy;

void visit(node_t *n)
{
    dummy = n->n;
}

struct stack stack;

int stack_empty() {
	return stack.i == 0;
}

void stack_push(node_t *t) {
	stack.data[stack.i++] = t;
}

node_t *stack_pop() {
	return stack.data[--stack.i];
}


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
		assert(tmp->n != new->n);
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

void rec_traversal(node_t *root) {
    if (!root)
        return;

    //printf("%d\n", root->n);
    rec_traversal(root->l);
    rec_traversal(root->r);
}

void stack_traversal(node_t *root) {
    node_t *tmp = root;
    stack_push(tmp);
    while (!stack_empty()) {
        tmp = stack_pop();
        if (tmp) {
            //printf("%d\n", tmp->n);
            stack_push(tmp->r);
            stack_push(tmp->l);
        }
    }
}

int main() {
	node_t *root = NULL;

	for (int i = MAX_STACK_SIZE / 2; i < MAX_STACK_SIZE; ++i) {
		node_t *new = calloc(1, sizeof(node_t));
		if (!new)
			return 1;
		new->n = i;
		root = insert_tree(root, new);
	}

	for (int i = 0; i < MAX_STACK_SIZE / 2; ++i) {
		node_t *new = calloc(1, sizeof(node_t));
		if (!new)
			return 1;
		new->n = i;
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
