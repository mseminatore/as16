#ifndef __AS_H
#define __AS_H

//-----------------
// functinon decls
//-----------------
int yylex();
void yyerror(char*);
void add_fixup(int symbol, int addr, int type);

//-----------------
// constant decls
//-----------------
#define ADDRESS_BITS        10
#define INSTRUCTION_BITS    16

#define DONE 0

#define OP_SHIFT 13
#define RA_SHIFT 10
#define RB_SHIFT 7

#define MASK_6b     0x3f
#define MASK_7b     0x7f
#define MASK_10b    0x3ff

#define MAX_CODE    1024
#define MAX_SYMBOLS 1024
#define MAX_FIXUPS  1024

#define BUF_SIZE    256

#ifdef _WIN32
#   define strcasecmp stricmp
#endif

#ifndef TRUE
#   define TRUE 1
#endif

#ifndef FALSE
#   define FALSE 0
#endif

// remove this later
#define YYDEBUG 1

// opcodes
enum {
    OP_ADD,
    OP_ADDI,
    OP_NAND,
    OP_LUI,
    OP_SW,
    OP_LW,
    OP_BEQ,
    OP_JALR
};

enum
{
    ST_UNDEF,
    ST_EQU,
    ST_LABEL
};

enum
{
    FIXUP_IMM7,
    FIXUP_IMM10,
    FIXUP_IMM6,
    FIXUP_IMM10_HI,
    FIXUP_REL7
};

typedef struct
{
    const char *name;
    int type;
    int value;
    int lineno;
} Symbol_t;

typedef struct
{
    int symbol;
    int addr;
    int type;
} Fixup_t;

typedef struct {
    const char *lexeme;
    int token;
} Tokens;

#endif  //__AS_H
