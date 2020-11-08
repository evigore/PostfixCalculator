#include "stack.h"

Stack *stack_new(void)
{
	Stack *this = malloc(sizeof(Stack));
	if (!this)
		return NULL;

	stack_init(this);

	return this;
}

void stack_delete(Stack *this)
{
	stack_clear(this);
	free(this);
}

Stack *stack_init(Stack *this)
{
	this->top = NULL;
	this->size = 0;

	return this;
}

void stack_destroy(Stack *this)
{
	stack_clear(this);
}

void stack_clear(Stack *this)
{
	StackNode *i = this->top;

	while (i) {
		StackNode *next = i->next;
		free(i);

		i = next;
	}
}

int stack_size(Stack *this)
{
	return this->size;
}

double *stack_topValue(Stack *this)
{
	if (this->size == 0)
		return NULL;

	return &this->top->value;
}

Token *stack_topToken(Stack *this)
{
	if (this->size == 0)
		return NULL;

	return &this->top->token;
}

int stack_topHasValue(Stack *this)
{
	if (this->size == 0)
		return 0;

	return this->top->hasValue;
}

double stack_popValue(Stack *this)
{
	if (this->size == 0)
		return 0;

	StackNode *top = this->top;
	this->top = top->next;
	double value = top->value;

	free(top);
	this->size--;

	return value;
}

Token stack_popToken(Stack *this)
{
	if (this->size == 0)
		return token_null();

	StackNode *top = this->top;
	this->top = top->next;

	Token token;
	token_copy(&token, &top->token);

	free(top);
	this->size--;

	return token;
}

void stack_pushValue(Stack *this, double value)
{
	StackNode *top = malloc(sizeof(StackNode));
	if (!top)
		return;

	top->hasValue = 1;
	top->value = value;
	top->token = token_null();

	top->next = this->top;
	this->top = top;
	this->size++;
}

void stack_pushToken(Stack *this, Token token)
{
	StackNode *top = malloc(sizeof(StackNode));
	if (!top)
		return;

	top->value = 0;
	top->hasValue = 0;
	token_copy(&top->token, &token);

	top->next = this->top;
	this->top = top;
	this->size++;
}

