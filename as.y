%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "as.h"
//#include "y.tab.h"

// command line switches
const char * g_szOutputFilename = "a.out";
int g_bDebug = 0;
int g_bSyncROM = 0;
int g_bROM = 0;
int lineno = 1;

FILE *yyin = NULL;
FILE *fout = NULL;

//uint16_t inst;
uint16_t addr = 0;

uint16_t code[MAX_CODE];

// accumulate generated code
void emit(uint16_t v)
{
    code[addr] = v;
    addr++;
}

// helper functions
uint16_t rrr(int op, int ra, int rb, int rc) { return (op << OP_SHIFT) | (ra << RA_SHIFT) | (rb << RB_SHIFT) | rc; }
uint16_t rri(int op, int ra, int rb, int imm7) { return (op << OP_SHIFT) | (ra << RA_SHIFT) | (rb << RB_SHIFT) | (imm7 & 0x7f); }
uint16_t ri(int op, int ra, int imm10) { return (op << OP_SHIFT) | (ra << RA_SHIFT) | (imm10 & 0x3ff); }

const char *fixup_names[] =
{
    "IMM7",
    "IMM10",
    "IMM6",
    "IMM10_HI",
    "REL7"
};

// symbol table
Symbol_t symbols[MAX_SYMBOLS];
int symbol_count = 0;

// fixups
Fixup_t fixups[MAX_FIXUPS];
int fixup_count = 0;

%}

%union 
{
    int ival;
    int symbol;
    char *lexeme;
}

%token EQU
%token <symbol> ID NEWID
%token <ival> ADD ADDI NAND LUI SW LW BEQ JALR
%token <ival> INC DEC
%token <ival> RET PUSH POP CALL J MOVI LLI NOP
%token <ival> NUMBER R0 R1 R2 R3 R4 R5 R6 R7 LR SP
%type <ival> register imm7 imm10 line imm rel7
%token FILL SPACE HALT

%%

file: equates lines
    ;

equates:
    | equates equate
    ;

equate: ID EQU NUMBER         { assert(symbols[$1].type == ST_UNDEF); symbols[$1].value = $3; symbols[$1].type = ST_EQU; }
    ;

lines:
    | line lines
    ;

line: label instruction     {}
    ;

label:
    | ID ':'    { assert(symbols[$1].type == ST_UNDEF); symbols[$1].value = addr; symbols[$1].type = ST_LABEL; }
    ;

rel7: NUMBER    { $$ = $1 & MASK_7b; }
    | ID        { if (symbols[$1].type == ST_UNDEF) { add_fixup($1, addr, FIXUP_REL7); $$ = 0; } else $$ = (symbols[$1].value & MASK_7b) - (addr + 1); /* return symbol value */ }
    ;

imm7: NUMBER    { $$ = $1 & MASK_7b; }
    | ID        { if (symbols[$1].type == ST_UNDEF) { add_fixup($1, addr, FIXUP_IMM7); $$ = 0; } else $$ = symbols[$1].value & MASK_7b; /* return symbol value */ }
    ;

imm10: NUMBER   { $$ = $1 & MASK_10b; }
    | ID        { if (symbols[$1].type == ST_UNDEF) { add_fixup($1, addr, FIXUP_IMM10); $$ = 0; } else $$ = symbols[$1].value & MASK_10b; /* return symbol value*/ }
    ;

imm: NUMBER
    | ID        { if (symbols[$1].type == ST_UNDEF) { add_fixup($1, addr, FIXUP_IMM10_HI); add_fixup($1, addr + 1, FIXUP_IMM6); $$ = 0; } else $$ = symbols[$1].value; /* return symbol value */ }
    ;

instruction: ADD register ',' register ',' register     { emit(rrr(OP_ADD, $2, $4, $6)); }
    | ADDI register ',' register ',' imm7               { emit(rri(OP_ADDI, $2, $4, $6)); }
    | NAND register ',' register ',' register           { emit(rrr(OP_NAND, $2, $4, $6)); }
    | LUI register ',' imm10                            { emit(ri(OP_LUI, $2, $4)); }
    | SW register ',' register ',' imm7                 { emit(rri(OP_SW, $2, $4, $6)); }
    | LW register ',' register ',' imm7                 { emit(rri(OP_LW, $2, $4, $6)); }
    | BEQ register ',' register ',' rel7                { emit(rri(OP_BEQ, $2, $4, $6)); }
    | JALR register ',' register                        { emit(rri(OP_JALR, $2, $4, 0)); }
    | RET                                               { emit(rri(OP_JALR, 0, 6, 0)); }
    | PUSH register                                     { emit(rri(OP_ADDI, 7, 7, -1)); emit(rri(OP_SW, $2, 7, 0)); }
    | POP register                                      { emit(rri(OP_LW, $2, 7, 0)); emit(rri(OP_ADDI, 7, 7, 1)); }
    | J register                                        { emit(rri(OP_JALR, 0, $2, 0)); }
    | CALL register                                     { emit(rri(OP_JALR, 6, $2, 0)); }
    | MOVI register ',' imm                             { emit(ri(OP_LUI, $2, ($4 & 0xffc0) >> 6)); emit(rri(OP_ADDI, $2, $2, $4 & MASK_6b)); }
    | LLI register ',' imm7                             { emit(rri(OP_ADDI, $2, $2, $4 & 0x3f)); }
    | NOP                                               { emit(rrr(OP_ADD, 0, 0, 0)); }
    | INC register                                      { emit(rri(OP_ADDI, $2, $2, 1)); }
    | DEC register                                      { emit(rri(OP_ADDI, $2, $2, -1)); }
    | FILL NUMBER                                       { emit($2); }
    | SPACE NUMBER                                      { for(int i = 0; i < $2; i++) emit(0); }
    | HALT                                              { emit(rri(OP_JALR, 0, 0, 1)); }
    ;

register: R0    { $$ = 0; }
    | R1        { $$ = 1; }
    | R2        { $$ = 2; }
    | R3        { $$ = 3; }
    | R4        { $$ = 4; }
    | R5        { $$ = 5; }
    | R6        { $$ = 6; }
    | R7        { $$ = 7; }
    | LR        { $$ = 6; }
    | SP        { $$ = 7; }
    ;

%%

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

    // useful register aliases
    {"LR", LR},
    {"SP", SP},

    // pseudo instructions
    {"RET", RET},
    {"PUSH", PUSH},
    {"POP", POP},
    {"CALL", CALL},
    {"J", J},
    {"MOVI", MOVI},
    {"LLI", LLI},
    {"NOP", NOP},
    { "EQU", EQU},
    { "INC", INC},
    { "DEC", DEC},

    { ".FILL", FILL},
    { ".SPACE", SPACE},
    { "HALT", HALT},

    { NULL, 0}
};

// get options from the command line
int getopt(int n, char *args[])
{
	int i;
	for (i = 1; args[i] && args[i][0] == '-'; i++)
	{
		if (args[i][1] == 'v')
			g_bDebug = 1;

        if (args[i][1] == 'r')
            g_bROM = 1;

        if (args[i][1] == 's')
        {
            g_bROM = 1;
            g_bSyncROM = 1;
        }

		if (args[i][1] == 'o')
		{
			g_szOutputFilename = args[i + 1];
			i++;
		}

        if (args[i][1] == 'i')
            yyin = stdin;
	}

	return i;
}

// add a fixup
void add_fixup(int symbol, int addr, int type)
{
    if (g_bDebug)
        printf("adding %s fixup for %s @ addr %d\n", fixup_names[type], symbols[symbol].name, addr);

    fixups[fixup_count].symbol  = symbol;
    fixups[fixup_count].addr    = addr;
    fixups[fixup_count].type    = type;

    fixup_count++;
}

// apply fixups
void apply_fixups()
{
     if (g_bDebug)
        printf("%d fixups found.\n", fixup_count);

    for (int i = 0; i < fixup_count; i++)
    {
        Fixup_t f = fixups[i];
        if (g_bDebug)
            printf("fixing up %s reference to %s @ addr %d\n", fixup_names[f.type], symbols[fixups[i].symbol].name, fixups[i].addr);

        switch(f.type)
        {
        case FIXUP_IMM10:
            code[f.addr] |= symbols[f.symbol].value & MASK_10b;
            break;

        case FIXUP_IMM10_HI:
            code[f.addr] |= (symbols[f.symbol].value & 0xffc0) >> 6;
            break;

        case FIXUP_IMM7:
            code[f.addr] |= symbols[f.symbol].value & MASK_7b;
            break;

        case FIXUP_IMM6:
            code[f.addr] |= symbols[f.symbol].value & MASK_6b;
            break;

        case FIXUP_REL7:
            break;

        default:
            assert(0);
        }
    }
}

// lookup a symbol
int lookup_symbol(const char *name)
{
    for (int i = 0; i < symbol_count; i++)
    {
        if (!strcasecmp(name, symbols[i].name))
            return i;
    }

    // symbol not found!
    return -1;
}

// add a new symbols
int add_symbol(const char *name, int lineno)
{
    // error if symbol already exists
    if (lookup_symbol(name) > 0)
        return -1;

    symbols[symbol_count].name      = strdup(name);
    symbols[symbol_count].lineno    = lineno;
    symbols[symbol_count].type      = ST_UNDEF;
    symbols[symbol_count].value     = -1;

    symbol_count++;
    return symbol_count - 1;
}

//========================
// error routine
//========================
void yyerror(char *s)
{
    fprintf(stderr, "error: %s near line %d\n", s, lineno);
}

//========================
// discard input to EOL
//========================
void skipToEOL(void)
{
	int c;

	// skip to EOL
	do {
		c = getc(yyin);
	} while (c != '\n' && c != EOF);

	// put last character back
	ungetc(c, yyin);
}

//==================================
// Conditionally return token value
//==================================
int follow(int expect, int ifyes, int ifno)
{
	int chr;

	chr = getc(yyin);
	if (chr == expect)
		return ifyes;

	ungetc(chr, yyin);
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
 	c = getc(yyin);
	if (c == '$' || (c == '0' && (follow('X', 1, 0) || follow('x', 1, 0))))
		base = 16;
	else if (c == '-' || c == '+')
		*bufptr++ = c;
	else
		ungetc(c, yyin);

	if (base == 16)
	{
		while (isxdigit(c = getc(yyin)))
			*bufptr++ = c;
	}
	else
	{
		while (isdigit((c = getc(yyin))) || c == '.')
			*bufptr++ = c;
	}
	
	// need to put back the last character
	ungetc(c, yyin);

	// make sure string is asciiz
	*bufptr = '\0';

    yylval.ival = strtol(buf, NULL, base);
    return NUMBER;
}

//========================
// see if we match a token
//========================
int isToken(const char *s)
{
    Tokens *pTokens = tokens;

    for (; pTokens->lexeme != NULL; pTokens++)
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
    while ((c = getc(yyin)) == ' ' || c == '\t');

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
		ungetc(c, yyin);
		return getNumber();
	}

    // look for start of a token
    if (isalpha(c)) 
    {
        char buf[BUF_SIZE], *p = buf;

        do {
            *p++ = c;
        } while ((c=getc(yyin)) != EOF && (c == '_' || isalnum(c)));
        
        // put back the last character!
        ungetc(c, yyin);

        // be sure to null terminate the string
        *p = 0;

        int token = isToken(buf);
        if (token)
        {
            return token;
        }
        
        // lookup symbol and return if exists
        int sym = lookup_symbol(buf);
        if (sym != -1)
        {
            yylval.symbol = sym;
            if (g_bDebug)
                printf("existing symbol: %s (%d)\n", buf, sym);
            return ID;
        }

        sym = add_symbol(buf, lineno);

        yylval.symbol = sym;
        if (g_bDebug)
            printf("new symbol: %s (%d)\n", buf, sym);
    
        return ID;
    }

    // track line numbers
    if (c == '\n')
    {
        lineno++;
        goto yylex01;
    }

    // return single character tokens
    return c;
}

//
void write_file()
{
    for (int i = 0; i < addr; i++)
        fprintf(fout, "%04X\n", code[i]);
}

//
void usage()
{
	puts("\nusage: as16 [options] filename\n");
    puts("-i\tget input from stdin");
	puts("-v\tverbose output");
	puts("-o file\tset output filename");
    puts("-r\tgenerate Verilog rom file");
    puts("-s\tgenerate synchronous Verilog\n");
	exit(0);

}

// generate template prologue
void prologue(FILE *f, int addr_bits, int data_bits) 
{
    fprintf(f, "`timescale 1ns / 1ps\n\n");
    fprintf(f, "module rom\n");
    fprintf(f, "(\n");

    if (g_bSyncROM)
        fprintf(f, "\tinput wire clk,\n");

    fprintf(f, "\tinput wire [%d : 0] addr,\n"
        "\toutput reg [%d : 0] data\n"
        ");\n\n", 
        addr_bits - 1,
        data_bits - 1
    );

    if (g_bSyncROM)
        fprintf(f, "\treg [%d : 0] addr_reg;\n\n"
            "\t// Sequential logic\n"
            "\talways @(posedge clk)\n"
            "\t\taddr_reg <= addr;\n\n",
            addr_bits - 1
        );

    fprintf(f, "\t// Combinational logic\n"
        "\talways @*\n"
    );

    if (g_bSyncROM)
        fprintf(f, "\t\tcase (addr_reg)\n");
    else
        fprintf(f, "\t\tcase (addr)\n");
}

// generate template epilog
void epilog(FILE *f) 
{
    fputs("\t\tendcase\n", f);
    fputs("endmodule\n", f);
}

// generate ROM data
void romgen(FILE *fout, int addr_bits, int data_bits)
{
    int num;

    prologue(fout, addr_bits, data_bits);

    // loop over the code and output Verilog
    for (int i = 0; i < addr; i++)
    {
        num = code[i];
        fprintf(fout, "\t\t\t%d'd%d: data = %d'h%x;\t// $%X\n", addr_bits, i, data_bits, num, num);
    }
    
    fprintf(fout, "\t\t\tdefault: data = %d'd0;\n", data_bits);

    epilog(fout);
}

//========================
// main entry point
//========================
int main(int argc, char *argv[])
{
    if (argc == 1)
		usage();

	int iFirstArg = getopt(argc, argv);

    if (yyin != stdin)
        yyin = fopen(argv[iFirstArg], "rt");

    // set this to 0 to disable parser debugging
    yydebug = 0;

    fout = fopen(g_szOutputFilename, "wb");

    // parse the input file
    yyparse();

    // fixup any forward references
    apply_fixups();

    if (g_bROM)
        romgen(fout, 10, 16);
    else
        write_file();

    fclose(fout);

    if (yyin != stdin)
        fclose(yyin);

    printf("\nSuccessfully assembled %d instructions to %s\n\n", addr, g_szOutputFilename);

    return 0;
}
