#include "stack.h"
#include "token.h"
#include "parser.h"

double sinPi(double rad)
{
	rad = rad - 2*M_PI*((int) (rad/(2*M_PI)));

	if (rad == M_PI)
		return 0;

	return sin(rad);
}

double cosPi(double rad)
{
	rad = rad - 2*M_PI*((int) (rad/(2*M_PI)));

	if (rad == M_PI/2 || rad == 3*M_PI/2)
		return 0;

	return cos(rad);
}

double tgPi(double rad)
{
	double cosValue = cosPi(rad);
	if (cosValue == 0)
		return 1.0/0;
	else if (cosValue == -1)
		cosValue = 1;

	return sinPi(rad)/cosValue;
}

double stackTop_to_value(Stack *stack)
{
	if (stack_topHasValue(stack))
		return *stack_topValue(stack);

	Token *token = stack_topToken(stack);
	if (token->type == TOKEN_TYPE_NUM)
		return atof(token->lexem);
	else if (token->type == TOKEN_TYPE_PI)
		return M_PI;
	else if (token->type == TOKEN_TYPE_E)
		return M_E;
	else 
		syntax_error("Incorrect operand type of operator", token);

	return 0;
}

typedef struct funcPtr {
	char *name;
	double (*ptr)(double);
} funcPtr;

funcPtr funcPointers[] = {
	{"sqrt", sqrt},
	{"cbrt", cbrt},

	{"abs", fabs},
	{"ceil", ceil},
	{"floor", floor},
	{"round", round},

	{"cos", cosPi},
	{"sin", sinPi},
	{"tg", tgPi},
	{"tan", tgPi},
	{"acos", acos},
	{"asin", asin},
	{"arctg", atan},
	{"atan", atan},

	{"ln", log},
	{"log2", log2},
	{"log10", log10}
};

double (*search_funcPtr(char *name)) (double)
{
	for (int i = 0; i < sizeof(funcPointers)/sizeof(funcPointers[0]); i++)
		if (strcmp(funcPointers[i].name, name) == 0)
			return funcPointers[i].ptr;

	return NULL;
}

int main(int argc, char **argv)
{
	double aValue;
	double bValue;
	Token aToken;

	Stack stack;
	stack_init(&stack);

	Token token;
	for (get_next_token(&token); token.type != TOKEN_TYPE_EOF; get_next_token(&token)) {
		switch (token.type) {
		case TOKEN_TYPE_E:
		case TOKEN_TYPE_PI:
		case TOKEN_TYPE_NUM:
		case TOKEN_TYPE_NAME:
			stack_pushToken(&stack, token);
			break;
		case TOKEN_TYPE_PLUS:
		case TOKEN_TYPE_MINUS:
		case TOKEN_TYPE_MUL:
		case TOKEN_TYPE_DIV:
		case TOKEN_TYPE_MOD:
		case TOKEN_TYPE_POWER:
			bValue = stackTop_to_value(&stack);
			stack_popValue(&stack);

			aValue = stackTop_to_value(&stack);
			stack_popValue(&stack);

			switch (token.type) {
			case TOKEN_TYPE_PLUS:  stack_pushValue(&stack, aValue+bValue); break;
			case TOKEN_TYPE_MINUS: stack_pushValue(&stack, aValue-bValue); break;
			case TOKEN_TYPE_MUL:   stack_pushValue(&stack, aValue*bValue); break;
			case TOKEN_TYPE_DIV:   stack_pushValue(&stack, aValue/bValue); break;
			case TOKEN_TYPE_MOD: stack_pushValue(&stack, fmod(aValue, bValue)); break;
			case TOKEN_TYPE_POWER: stack_pushValue(&stack, powf(aValue, bValue)); break;
			}

			break;
		case TOKEN_TYPE_FUNCCALL:
			bValue = stackTop_to_value(&stack);
			stack_popValue(&stack);

			aToken = stack_popToken(&stack);
			double (*funcPtr)(double) = search_funcPtr(aToken.lexem);
			if (funcPtr == NULL)
				syntax_error("It's not correct function name", &aToken);

			stack_pushValue(&stack, funcPtr(bValue));
			break;
		}
	}

	if (stack_size(&stack) != 1)
		syntax_error("There is no enough operators after operand", &token);

	if (stack_topHasValue(&stack))
		printf("%g\n", stack_popValue(&stack));
	else
		printf("%s\n", stack_popToken(&stack).lexem);

	stack_destroy(&stack);
}
