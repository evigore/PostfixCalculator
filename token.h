#ifndef __TOKEN_H__
#define __TOKEN_H__

#define LEXEM_LENGTH 20

#include <stdlib.h>
#include <string.h>

typedef struct Token {
	int pos;
	int type;
	char lexem[LEXEM_LENGTH];
} Token;

Token token_(int, char *, int);
Token token_null(void);

Token *token_init(Token *, int, char *, int);
Token *token_copy(Token *, Token *);
Token *token_new(void);
void token_delete(Token *);


#endif
