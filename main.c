#include "stack.h"

int main(int argc, char **argv)
{
	Stack stack;
	stack_init(&stack);

	char buffer[BUFFER_SIZE] = {0};

	//printf("Enter postfix expression: ");

	int hasEOF = 0;
	while (!hasEOF) {
		fgets(buffer, BUFFER_SIZE, stdin);

		for (int i = 0; buffer[i]; i++) {
			if (buffer[i] == '\n')
				hasEOF = 1;

			stack_next(&stack, buffer[i]);
		}
	}

	if (stack_size(&stack) == 1)
		printf("%g\n", stack_pop(&stack));
	else
		error();

	stack_destroy(&stack);
}
