#include "stack.h"

void error(void)
{
	printf("Incorrect expression\n");
	exit(1);
}

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
		StackNode *next = i->next;;
		free(i);

		i = next;
	}
}

int stack_size(Stack *this)
{
	return this->size;
}

float *stack_top(Stack *this)
{
	if (this->size == 0)
		return NULL;

	return &this->top->value;
}

float stack_pop(Stack *this)
{
	if (this->size == 0)
		return 0;

	StackNode *top = this->top;
	this->top = top->next;
	float value = top->value;

	free(top);
	this->size--;

	return value;
}

void stack_push(Stack *this, float value)
{
	StackNode *top = malloc(sizeof(StackNode));
	if (!top)
		return;

	top->value = value;
	top->next = this->top;

	this->top = top;
	this->size++;
}

void stack_next(Stack *this, char sym)
{
	float a;
	float b;

	static int num = 0;
	static int size = 1;
	static int is_num = 0;
	static int is_float = 0;

	switch (sym) {
	case '*':
		if (stack_size(this) < 2)
			error();

		b = stack_pop(this);
		a = stack_pop(this);
		
		stack_push(this, a * b);
		break;
	case '/':
		if (stack_size(this) < 2)
			error();

		b = stack_pop(this);
		a = stack_pop(this);
		
		stack_push(this, a / b);
		break;
	case '+':
		if (stack_size(this) < 2)
			error();

		b = stack_pop(this);
		a = stack_pop(this);
		
		stack_push(this, a + b);
		break;
	case '^':
		if (stack_size(this) < 2)
			error();

		b = stack_pop(this);
		a = stack_pop(this);
		
		stack_push(this, powf(a, b));
		break;
	case '-':
		if (stack_size(this) < 2)
			error();

		b = stack_pop(this);
		a = stack_pop(this);
		
		stack_push(this, a - b);
		break;
	case ' ':
	case '\t':
		if (is_num) {
			*stack_top(this) = num / size;

			is_num = 0;
			is_float = 0;
			num = 0;
			size = 1;
		}

		break;
	case '0'...'9':
		if (!is_num) {
			is_num = 1;
			stack_push(this, 0);
		}

		num = num*10 + sym-'0';

		if (is_float)
			size *= 10;

		break;
	case '.':
		if (is_num && !is_float)
			is_float = 1;
		else
			error();

		break;
	case '\n':
	case '\0':
		break;
	default:
		error();
	}
}
