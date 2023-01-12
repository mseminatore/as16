%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

int lineno = 1;

int yylex();
void yyerror(char*);

#define OP_SHIFT 13
#define RA_SHIFT 10
#define RB_SHIFT 7

FILE *fout = NULL;

uint16_t inst;

#ifdef _WIN32
#   define strcasecmp stricmp
#endif

// remove this later
#define YYDEBUG 1

void emit(uint16_t v)
{
    printf("%04X\n", v);
}

uint16_t rrr(int op, int ra, int rb, int rc) { return (op << OP_SHIFT) | (ra << RA_SHIFT) | (rb << RB_SHIFT) | rc; }
uint16_t rri(int op, int ra, int rb, int imm7) { return (op << OP_SHIFT) | (ra << RA_SHIFT) | (rb << RB_SHIFT) | imm7; }
uint16_t ri(int op, int ra, int imm10) { return (op << OP_SHIFT) | (ra << RA_SHIFT) | imm10; }

%}

%union 
{
    int ival;
    char *lexeme;
}

%token <ival> ID ADD ADDI NAND LUI SW LW BEQ JALR
%token <ival> RET PUSH POP CALL J MOVI LLI NOP
%token <ival> NUMBER R0 R1 R2 R3 R4 R5 R6 R7
%type <ival> register imm7 imm10 line instruction

%%

lines:
    | line lines
    ;

line: label instruction     {  }
    ;

label:
    | ID ':'
    ;

imm7: NUMBER    { $$ = $1 & 0x7f; }
    ;

imm10: NUMBER   { $$ = $1 & 0x3ff; }
    ;

instruction: ADD register ',' register ',' register     { emit(rrr(0, $2, $4, $6)); }
    | ADDI register ',' register ',' imm7               { emit(rri(1, $2, $4, $6)); }
    | NAND register ',' register ',' register           { emit(rrr(2, $2, $4, $6)); }
    | LUI register ',' imm10                            { emit(ri(3, $2, $4)); }
    | SW register ',' register ',' imm7                 { emit(rri(4, $2, $4, $6)); }
    | LW register ',' register ',' imm7                 { emit(rri(5, $2, $4, $6)); }
    | BEQ register ',' register ',' imm7                { emit(rri(6, $2, $4, $6)); }
    | JALR register ',' register                        { emit(rri(7, $2, $4, 0)); }
    | RET                                               { emit(rri(7, 0, 6, 0)); }
    | PUSH register                                     { /*emit(); emit(); */ }
    | POP register                                      { /*emit(); emit(); */ }
    | J register                                        { emit(rri(7, 0, $2, 0)); }
    | CALL register                                     { emit(rri(7, 6, $2, 0)); }
    | MOVI                                              { /*emit(); emit(); */ }
    | LLI register ',' imm7                             { emit(rri(1, $2, $2, $4 & 0x3f)); }
    | NOP                                               { emit(rrr(0, 0, 0, 0)); }                          
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

typedef struct {
    const char *lexeme;
    int token;
} Tokens;

Tokens tokens[] =
{
    {"ADD", ADD},
    {"ADDI", ADDI},
    {"NAND", NAND},
    {"LUI", LUI},
    {"SW", SW},
    {"LW", LW},
    {"BEQ", BEQ},
    {"JALR", JALR},
    {"R0", R0},
    {"R1", R1},
    {"R2", R2},
    {"R3", R3},
    {"R4", R4},
    {"R5", R5},
    {"R6", R6},
    {"R7", R7},

    {"RET", RET},
    {"PUSH", PUSH},
    {"POP", POP},
    {"CALL", CALL},
    {"J", J},
    {"MOVI", MOVI},
    {"LLI", LLI},
    {"NOP", NOP},

    { NULL, 0}
};

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
	if (c == '$' || (c == '0' && (follow('X', 1, 0) || follow('x', 1, 0))))
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

    yylval.ival = strtol(buf, NULL, base);
    return NUMBER;
}

//
int isToken(const char *s)
{
    Tokens *pTokens = tokens;

    for (; pTokens != NULL; pTokens++)
    {
        if (!strcasecmp(s, pTokens->lexeme))
            return pTokens->token;
    }

    return 0;
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

        int token = isToken(buf);
        if (token)
        {
            return token;
        }
        
//        printf("WORD: %s\n", buf);

        yylval.lexeme = strdup(buf);
        return ID;
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
