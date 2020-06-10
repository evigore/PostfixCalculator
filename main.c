#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFFER_SIZE 512

typedef struct List {
	struct List *next;
	float value;
} List;

typedef struct Stack {
	List *top;
	int count;
} Stack;


void error(void)
{
	printf("Incorrect expression\n");
	exit(1);
}

Stack *Stack_New(void)
{
	Stack *this = malloc(sizeof(Stack));
	if (!this)
		return NULL;

	this->top = NULL;
	this->count = 0;

	return this;
}

void Stack_Delete(Stack *this)
{
	List *prev;
	List *list = this->top;

	while (list) {
		prev = list;
		list = list->next;

		free(prev);
	}
}

int Stack_Length(Stack *this)
{return this->count;}

float Stack_Top(Stack *this)
{
	if (this->count > 0)
		return this->top->value;
	return -1;
}

float Stack_Pop(Stack *this)
{
	if (this->count == 0)
		return -1;

	List *top = this->top;
	this->top = top->next;

	float value = top->value;
	free(top);
	this->count--;

	return value;
}

void Stack_Push(Stack *this, float value)
{
	List *elem = malloc(sizeof(List));
	elem->value = value;
	elem->next = this->top;

	this->top = elem;
	this->count++;
}

float Calculate(char *buffer)
{
	float num;
	int count;
	Stack *stack = Stack_New();

	for (int i = 0; buffer[i]; i++) {
		num = 0;
		count = 1;

		switch (buffer[i]) {
		case '*':
			if (Stack_Length(stack) < 2)
				error();
			
			Stack_Push(stack, Stack_Pop(stack) * Stack_Pop(stack));
			break;
		case '/':
			if (Stack_Length(stack) < 2)
				error();
		
			Stack_Push(stack, 1 / (Stack_Pop(stack)/Stack_Pop(stack)));
			break;
		case '+':
			if (Stack_Length(stack) < 2)
				error();

			Stack_Push(stack, Stack_Pop(stack) + Stack_Pop(stack));
			break;
		case '^':
			if (Stack_Length(stack) < 2)
				error();

			float b = Stack_Pop(stack);
			Stack_Push(stack, powf(Stack_Pop(stack), b));
			break;
		case '-':
			if (Stack_Length(stack) < 2)
				error();

			Stack_Push(stack, -Stack_Pop(stack) + Stack_Pop(stack));
			break;
		case '0'...'9':
			do {
				num = num*10 + buffer[i++]-'0';
			} while (buffer[i] >= '0' && buffer[i] <= '9');

			if (buffer[i] == '.') {
				i++;

				if (buffer[i] < '0' || buffer[i] > '9')
					error();

				do {
					num = num*10 + buffer[i++]-'0';
					count *= 10;
				} while (buffer[i] >= '0' && buffer[i] <= '9');
			}

			i--;
			num /= count;

			Stack_Push(stack, num);
			break;
		}
	}

	return Stack_Top(stack);
}

int main(int argc, char **argv)
{
	char buffer[BUFFER_SIZE] = {0};

	printf("Enter expression: ");
	fgets(buffer, BUFFER_SIZE, stdin);

	printf("%g\n", Calculate(buffer));
}
