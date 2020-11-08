#include <stdio.h>
#include <math.h>

#include "token.h"

typedef struct StackNode StackNode;
typedef struct Stack Stack;

struct StackNode {
	StackNode *next;
	Token token;

	int hasValue;
	double value;
};

struct Stack {
	StackNode *top;
	int size;
};

Stack *stack_new(void);
void stack_delete(Stack *);

Stack *stack_init(Stack *);
void stack_destroy(Stack *);
void stack_clear(Stack *);

int stack_size(Stack *);

double *stack_topValue(Stack *);
Token *stack_topToken(Stack *);
int stack_topHasValue(Stack *);

double stack_popValue(Stack *);
Token stack_popToken(Stack *);

void stack_pushValue(Stack *, double);
void stack_pushToken(Stack *, Token);
