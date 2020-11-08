#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <ctype.h>
#include "token.h"

enum {
	TOKEN_TYPE_NULL = 0,
	TOKEN_TYPE_EOF,

	TOKEN_TYPE_PLUS,
	TOKEN_TYPE_MINUS,
	TOKEN_TYPE_MUL,
	TOKEN_TYPE_DIV,
	TOKEN_TYPE_MOD,
	TOKEN_TYPE_POWER,
	TOKEN_TYPE_FUNCCALL,

	TOKEN_TYPE_E,
	TOKEN_TYPE_PI,
	TOKEN_TYPE_NUM,
	TOKEN_TYPE_NAME
};

void get_next_token(Token *);

static void parseName(Token *);
static void parseNum(Token *);

static char get_next_char(void);
static void unget_char(char);

static void lex_error(char *, char);
void syntax_error(char *, Token *);

#endif
