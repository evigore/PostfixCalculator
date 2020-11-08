#include "parser.h"

static int pos = 0; // Position of currect input symbol

void get_next_token(Token *token)
{
	char sym = get_next_char();
	if (sym == ' ')
		sym = get_next_char();

	switch (sym) {
		case '+':
			token_init(token, TOKEN_TYPE_PLUS, NULL, pos);
			break;
		case '-':
			token_init(token, TOKEN_TYPE_MINUS, NULL, pos);
			break;
		case '/':
			token_init(token, TOKEN_TYPE_DIV, NULL, pos);
			break;
		case '*':
			token_init(token, TOKEN_TYPE_MUL, NULL, pos);
			break;
		case '^':
			token_init(token, TOKEN_TYPE_POWER, NULL, pos);
			break;
		case '(':
			if (get_next_char() != ')')
				lex_error("Unknown operator", sym);

			token_init(token, TOKEN_TYPE_FUNCCALL, NULL, pos);
			break;
		case '\n':
			token_init(token, TOKEN_TYPE_EOF, NULL, pos);
			break;
		case 'a'...'z':
		case 'A'...'Z': 
			unget_char(sym);
			parseName(token);

			break;
		case '0'...'9':
			unget_char(sym);
			parseNum(token);
			break;
		default:
			lex_error("Unknown lexem", sym);
			token_init(token, TOKEN_TYPE_NULL, NULL, -1);
			break;
	}
}

static void parseName(Token *token)
{
	char lexem[LEXEM_LENGTH] = {0};
	int i = -1;

	do
		lexem[++i] = get_next_char();
	while (isalpha(lexem[i]) && i < LEXEM_LENGTH-1);

	while (isdigit(lexem[i]) && i < LEXEM_LENGTH-1)
		lexem[++i] = get_next_char();

	unget_char(lexem[i]);
	lexem[i] = '\0';

	if (tolower(lexem[0]) == 'e' && lexem[1] == '\0')
		token_init(token, TOKEN_TYPE_E, lexem, pos);
	else if (tolower(lexem[0]) == 'p' && tolower(lexem[1]) == 'i' && lexem[2] == '\0')
		token_init(token, TOKEN_TYPE_PI, lexem, pos);
	else
		token_init(token, TOKEN_TYPE_NAME, lexem, pos);
}

static void parseNum(Token *token)
{
	char lexem[LEXEM_LENGTH] = {0};
	int i = -1;

	do {
		lexem[++i] = get_next_char();
	} while (isdigit(lexem[i]) && i < LEXEM_LENGTH-1);

	if (lexem[i] == '.') {
		lexem[++i] = get_next_char();
		if (!isdigit(lexem[i]))
			lex_error("Bad number", lexem[i]);

		do
			lexem[++i] = get_next_char();
		while (isdigit(lexem[i]) && i < LEXEM_LENGTH-1);
	}

	unget_char(lexem[i]);
	lexem[i] = '\0';

	token_init(token, TOKEN_TYPE_NUM, lexem, pos);
}

static char get_next_char(void)
{
	pos++;
	char sym = fgetc(stdin);

	if (sym == ' ' || sym == '\t') {
		do {
			pos++;
			sym = fgetc(stdin);
		} while (sym == ' ' || sym == '\t');

		pos--;
		ungetc(sym, stdin);
		return ' ';
	}

	return sym;
}

static void unget_char(char sym)
{
	pos--;
	ungetc(sym, stdin);
}

static void lex_error(char *msg, char sym)
{
	fprintf(stderr, "%s in position %d (%c)\n", msg, pos, sym);
	exit(1);
}

void syntax_error(char *msg, Token *token)
{
	fprintf(stderr, "%s in position %lu (%s)\n", msg, token->pos - strlen(token->lexem), token->lexem);
	exit(1);
}
