#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 512

typedef struct StackNode StackNode;
typedef struct Stack Stack;

struct StackNode {
	StackNode *next;
	float value;
};

struct Stack {
	StackNode *top;
	int size;
};

void error(void);

Stack *stack_new(void);
void stack_delete(Stack *);

Stack *stack_init(Stack *);
void stack_destroy(Stack *);
void stack_clear(Stack *);

int stack_size(Stack *);

float *stack_top(Stack *);
float stack_pop(Stack *);
void stack_push(Stack *, float);

void stack_next(Stack *, char);
