%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

int lineno = 1;

int yylex();
void yyerror(char*);

//#define YYSTYPE char*

FILE *fout = NULL;

uint16_t inst;

// remove this later
#define YYDEBUG 1
%}

%union 
{
    int ival;
    char *token;
}

%token LABEL ADD ADDI NAND LUI SW LW BEQ JALR
%token <ival> NUMBER R0 R1 R2 R3 R4 R5 R6 R7
%type <ival> register imm7 imm10

%%

lines:
    | line lines
    ;

line: label instruction
    ;

label:
    | LABEL
    ;

imm7: NUMBER
    ;

imm10: NUMBER
    ;

instruction: ADD register ',' register ',' register
    | ADDI register ',' register ',' imm7
    | NAND register ',' register ',' register
    | LUI register ',' imm10
    | SW register ',' register ',' imm7
    | LW register ',' register ',' imm7
    | BEQ register ',' register ',' imm7
    | JALR register ',' register
    ;

register: R0    { $$ = 0; }
    | R1        { $$ = 1; }
    | R2        { $$ = 2; }
    | R3        { $$ = 3; }
    | R4        { $$ = 4; }
    | R5        { $$ = 5; }
    | R6        { $$ = 6; }
    | R7        { $$ = 7; }
    ;

%%

#define BUF_SIZE 256

//========================
// main entry point
//========================
int main(int argc, char *argv[])
{
    // set this to 0 to disable parser debugging
    yydebug = 0;

    fout = fopen("a.out", "wb");

    yyparse();

    fclose(fout);

    return 0;
}

//========================
// error routine
//========================
void yyerror(char *s)
{
    fprintf(stderr, "error: %s at line %d\n", s, lineno);
}

//========================
//
//========================
void skipToEOL(void)
{
	int c;

	// skip to EOL
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);

	// put last character back
	ungetc(c, stdin);
}

//==================================
// Conditionally return token value
//==================================
int follow(int expect, int ifyes, int ifno)
{
	int chr;

	chr = getchar();
	if (chr == expect)
		return ifyes;

	ungetc(chr, stdin);
	return ifno;
}

//========================
// match a number token
//========================
int getNumber()
{
	int c;
	char buf[BUF_SIZE];
	char *bufptr = buf;
	int base = 10;

	// look for hex numbers
 	c = getchar();
	if (c == '0' && (follow('X', 1, 0) || follow('x', 1, 0)))
		base = 16;
	else if (c == '-' || c == '+')
		*bufptr++ = c;
	else
		ungetc(c, stdin);

	if (base == 16)
	{
		while (isxdigit(c = getchar()))
			*bufptr++ = c;
	}
	else
	{
		while (isdigit((c = getchar())) || c == '.')
			*bufptr++ = c;
	}
	
	// need to put back the last character
	ungetc(c, stdin);

	// make sure string is asciiz
	*bufptr = '\0';

	// handle floats and ints
//	if (!strchr(buf, '.'))
//	{
		yylval.ival = strtol(buf, NULL, base);
		return NUMBER;
//	}
//	else
//	{
//		m_yylval->fval = (float)atof(buf);
//		return TV_FLOATVAL;
//	}
}

//========================
// lexical analyzer
//========================
int yylex()
{
    int c;

yylex01:
    // skip leading whitespace
    while ((c = getchar()) == ' ' || c == '\t');

    // see if input is empty
    if (c == EOF)
        return 0;

    // look for asm style comments
    if (c == '#' || c == ';')
    {
        skipToEOL();
        goto yylex01;
    }

	// look for a number value
	if (isdigit(c) || c == '-' || c == '+')
	{
		ungetc(c, stdin);
		return getNumber();
	}

    // look for start of a token
    if (isalpha(c)) 
    {
        char buf[BUF_SIZE], *p = buf;

        do {
            *p++ = c;
        } while ((c=getchar()) != EOF && isalnum(c));
        
        // put back the last character!
        ungetc(c, stdin);

        // be sure to null terminate the string
        *p = 0;
        yylval.token = strdup(buf);
        
//        printf("WORD: %s\n", buf);

        return WORD;
    }

    // track line numbers
    if (c == '\n')
    {
        lineno++;
        goto yylex01;
    }

    // return single character tokens
//    printf("TOKEN: '%c'\n", c);
    return c;
}
