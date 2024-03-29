/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EQU = 258,
     ID = 259,
     NEWID = 260,
     ADD = 261,
     ADDI = 262,
     NAND = 263,
     LUI = 264,
     SW = 265,
     LW = 266,
     BEQ = 267,
     JALR = 268,
     INC = 269,
     DEC = 270,
     MOV = 271,
     LWI = 272,
     RET = 273,
     PUSH = 274,
     POP = 275,
     CALL = 276,
     J = 277,
     MOVI = 278,
     LLI = 279,
     NOP = 280,
     NUMBER = 281,
     R0 = 282,
     R1 = 283,
     R2 = 284,
     R3 = 285,
     R4 = 286,
     R5 = 287,
     R6 = 288,
     R7 = 289,
     LR = 290,
     SP = 291,
     FP = 292,
     FILL = 293,
     SPACE = 294,
     HALT = 295
   };
#endif
/* Tokens.  */
#define EQU 258
#define ID 259
#define NEWID 260
#define ADD 261
#define ADDI 262
#define NAND 263
#define LUI 264
#define SW 265
#define LW 266
#define BEQ 267
#define JALR 268
#define INC 269
#define DEC 270
#define MOV 271
#define LWI 272
#define RET 273
#define PUSH 274
#define POP 275
#define CALL 276
#define J 277
#define MOVI 278
#define LLI 279
#define NOP 280
#define NUMBER 281
#define R0 282
#define R1 283
#define R2 284
#define R3 285
#define R4 286
#define R5 287
#define R6 288
#define R7 289
#define LR 290
#define SP 291
#define FP 292
#define FILL 293
#define SPACE 294
#define HALT 295




/* Copy the first part of user declarations.  */
#line 9 "as.y"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "as.h"

// command line switches
const char * g_szOutputFilename = "a.out";
int g_bDebug    = FALSE;
int g_bSyncROM  = TRUE;
int g_bROM      = FALSE;
int g_bSystemV  = FALSE;

// parser tracking
int lineno = 1;
int err_count = 0;

// assembler input and output files
FILE *yyin = NULL;
FILE *fout = NULL;

// code segment
uint16_t addr = 0;
uint16_t code[MAX_CODE];

// symbol table
Symbol_t symbols[MAX_SYMBOLS];
int symbol_count = 0;

// fixups
Fixup_t fixups[MAX_FIXUPS];
int fixup_count = 0;

// helper functions for instruction format encoding
uint16_t rrr(int op, int ra, int rb, int rc) 
{ 
    return (op << OP_SHIFT) | (ra << RA_SHIFT) | (rb << RB_SHIFT) | rc; 
}

uint16_t rri(int op, int ra, int rb, int imm7) 
{ 
    return (op << OP_SHIFT) | (ra << RA_SHIFT) | (rb << RB_SHIFT) | (imm7 & 0x7f); 
}

uint16_t ri(int op, int ra, int imm10) 
{ 
    return (op << OP_SHIFT) | (ra << RA_SHIFT) | (imm10 & 0x3ff); 
}

const char *fixup_names[] =
{
    "IMM7",
    "IMM10",
    "IMM6",
    "IMM10_HI",
    "REL7"
};

// Verilog vs. SystemVerilog strings
char *input_wire    = "input wire";
char *output_reg    = "output reg";
char *always_ff     = "always @(posedge clk)";
char *always_comb   = "always @*";
char *reg           = "reg";

// helper function to accumulate generated code
void emit(uint16_t v)
{
    code[addr] = v;
    addr++;
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 87 "as.y"
{
    int ival;
    int symbol;
    char *lexeme;
}
/* Line 193 of yacc.c.  */
#line 259 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 272 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   105

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  13
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNRULES -- Number of states.  */
#define YYNSTATES  113

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    41,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     7,    10,    14,    15,    18,    21,
      22,    25,    27,    29,    31,    33,    35,    37,    39,    41,
      48,    55,    62,    67,    74,    81,    88,    93,    95,    98,
     101,   104,   107,   112,   117,   122,   124,   127,   130,   133,
     136,   138,   143,   145,   147,   149,   151,   153,   155,   157,
     159,   161,   163
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    45,    47,    -1,    -1,    45,    46,    -1,
       4,     3,    26,    -1,    -1,    48,    47,    -1,    49,    54,
      -1,    -1,     4,    41,    -1,    26,    -1,     4,    -1,    26,
      -1,     4,    -1,    26,    -1,     4,    -1,    26,    -1,     4,
      -1,     6,    55,    42,    55,    42,    55,    -1,     7,    55,
      42,    55,    42,    51,    -1,     8,    55,    42,    55,    42,
      55,    -1,     9,    55,    42,    52,    -1,    10,    55,    42,
      55,    42,    51,    -1,    11,    55,    42,    55,    42,    51,
      -1,    12,    55,    42,    55,    42,    50,    -1,    13,    55,
      42,    55,    -1,    18,    -1,    19,    55,    -1,    20,    55,
      -1,    22,    55,    -1,    21,    55,    -1,    23,    55,    42,
      53,    -1,    17,    55,    42,    53,    -1,    24,    55,    42,
      51,    -1,    25,    -1,    14,    55,    -1,    15,    55,    -1,
      38,    26,    -1,    39,    26,    -1,    40,    -1,    16,    55,
      42,    55,    -1,    27,    -1,    28,    -1,    29,    -1,    30,
      -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,    37,
      -1,    35,    -1,    36,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   105,   105,   108,   109,   112,   115,   116,   119,   122,
     123,   126,   127,   130,   131,   134,   135,   138,   139,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQU", "ID", "NEWID", "ADD", "ADDI",
  "NAND", "LUI", "SW", "LW", "BEQ", "JALR", "INC", "DEC", "MOV", "LWI",
  "RET", "PUSH", "POP", "CALL", "J", "MOVI", "LLI", "NOP", "NUMBER", "R0",
  "R1", "R2", "R3", "R4", "R5", "R6", "R7", "LR", "SP", "FP", "FILL",
  "SPACE", "HALT", "':'", "','", "$accept", "file", "equates", "equate",
  "lines", "line", "label", "rel7", "imm7", "imm10", "imm", "instruction",
  "register", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    58,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    47,    47,    48,    49,
      49,    50,    50,    51,    51,    52,    52,    53,    53,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     3,     0,     2,     2,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     6,
       6,     6,     4,     6,     6,     6,     4,     1,     2,     2,
       2,     2,     4,     4,     4,     1,     2,     2,     2,     2,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     9,     1,     0,     4,     2,     9,     0,     0,
      10,     0,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,     0,     0,     0,     0,
       0,     0,    35,     0,     0,    40,     8,     5,    42,    43,
      44,    45,    46,    47,    48,    49,    51,    52,    50,     0,
       0,     0,     0,     0,     0,     0,     0,    36,    37,     0,
       0,    28,    29,    31,    30,     0,     0,    38,    39,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    15,    22,     0,     0,     0,
      26,    41,    18,    17,    33,    32,    14,    13,    34,     0,
       0,     0,     0,     0,     0,    19,    20,    21,    23,    24,
      12,    11,    25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,     6,     7,     8,   112,    98,    86,
      94,    36,    49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -63
static const yytype_int8 yypact[] =
{
     -63,    46,    54,   -63,     8,   -63,   -63,    80,    12,    13,
     -63,     6,   -63,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,   -63,    42,    42,    42,    42,
      42,    42,   -63,    22,    27,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,    26,
      44,    47,    48,    49,    50,    51,    52,   -63,   -63,    53,
      55,   -63,   -63,   -63,   -63,    56,    57,   -63,   -63,    42,
      42,    42,    38,    42,    42,    42,    42,    42,    39,    39,
      40,    58,    59,    60,   -63,   -63,   -63,    61,    62,    63,
     -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,    42,
      40,    42,    40,    40,    41,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   -63,   -63,   -63,    74,   -63,   -63,   -63,   -62,   -63,
       3,   -63,   -14
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -7
static const yytype_int8 yytable[] =
{
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,     9,    61,    62,    63,    64,    65,    66,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   106,    37,
     108,   109,    84,    92,    96,   110,     3,    10,    67,    10,
      33,    34,    35,    68,    -6,    81,    82,    83,     4,    87,
      88,    89,    90,    91,    85,    93,    97,   111,    69,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -6,    12,    95,     0,    11,   105,    70,   107,     0,    71,
      72,    73,    74,    75,    76,    77,     0,    78,    79,    80,
      99,   100,   101,   102,   103,   104
};

static const yytype_int8 yycheck[] =
{
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     3,    26,    27,    28,    29,    30,    31,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,   100,    26,
     102,   103,     4,     4,     4,     4,     0,    41,    26,    41,
      38,    39,    40,    26,     0,    69,    70,    71,     4,    73,
      74,    75,    76,    77,    26,    26,    26,    26,    42,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
       0,     7,    79,    -1,     4,    99,    42,   101,    -1,    42,
      42,    42,    42,    42,    42,    42,    -1,    42,    42,    42,
      42,    42,    42,    42,    42,    42
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    45,     0,     4,    46,    47,    48,    49,     3,
      41,     4,    47,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    38,    39,    40,    54,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    26,    26,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    55,    55,    55,     4,    26,    52,    55,    55,    55,
      55,    55,     4,    26,    53,    53,     4,    26,    51,    42,
      42,    42,    42,    42,    42,    55,    51,    55,    51,    51,
       4,    26,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 112 "as.y"
    { if (symbols[(yyvsp[(1) - (3)].symbol)].type != ST_UNDEF) yyerror("duplicate symbol"); symbols[(yyvsp[(1) - (3)].symbol)].value = (yyvsp[(3) - (3)].ival); symbols[(yyvsp[(1) - (3)].symbol)].type = ST_EQU; }
    break;

  case 8:
#line 119 "as.y"
    { /* empty action needed here for now */ }
    break;

  case 10:
#line 123 "as.y"
    { assert(symbols[(yyvsp[(1) - (2)].symbol)].type == ST_UNDEF); symbols[(yyvsp[(1) - (2)].symbol)].value = addr; symbols[(yyvsp[(1) - (2)].symbol)].type = ST_LABEL; }
    break;

  case 11:
#line 126 "as.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival) & MASK_7b; }
    break;

  case 12:
#line 127 "as.y"
    { if (symbols[(yyvsp[(1) - (1)].symbol)].type == ST_UNDEF) { add_fixup((yyvsp[(1) - (1)].symbol), addr, FIXUP_REL7); (yyval.ival) = 0; } else (yyval.ival) = (symbols[(yyvsp[(1) - (1)].symbol)].value & MASK_7b) - (addr + 1); /* return symbol value */ }
    break;

  case 13:
#line 130 "as.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival) & MASK_7b; }
    break;

  case 14:
#line 131 "as.y"
    { if (symbols[(yyvsp[(1) - (1)].symbol)].type == ST_UNDEF) { add_fixup((yyvsp[(1) - (1)].symbol), addr, FIXUP_IMM7); (yyval.ival) = 0; } else (yyval.ival) = symbols[(yyvsp[(1) - (1)].symbol)].value & MASK_7b; /* return symbol value */ }
    break;

  case 15:
#line 134 "as.y"
    { (yyval.ival) = (yyvsp[(1) - (1)].ival) & MASK_10b; }
    break;

  case 16:
#line 135 "as.y"
    { if (symbols[(yyvsp[(1) - (1)].symbol)].type == ST_UNDEF) { add_fixup((yyvsp[(1) - (1)].symbol), addr, FIXUP_IMM10); (yyval.ival) = 0; } else (yyval.ival) = symbols[(yyvsp[(1) - (1)].symbol)].value & MASK_10b; /* return symbol value*/ }
    break;

  case 18:
#line 139 "as.y"
    { if (symbols[(yyvsp[(1) - (1)].symbol)].type == ST_UNDEF) { add_fixup((yyvsp[(1) - (1)].symbol), addr, FIXUP_IMM10_HI); add_fixup((yyvsp[(1) - (1)].symbol), addr + 1, FIXUP_IMM6); (yyval.ival) = 0; } else (yyval.ival) = symbols[(yyvsp[(1) - (1)].symbol)].value; /* return symbol value */ }
    break;

  case 19:
#line 142 "as.y"
    { emit(rrr(OP_ADD, (yyvsp[(2) - (6)].ival), (yyvsp[(4) - (6)].ival), (yyvsp[(6) - (6)].ival))); }
    break;

  case 20:
#line 143 "as.y"
    { emit(rri(OP_ADDI, (yyvsp[(2) - (6)].ival), (yyvsp[(4) - (6)].ival), (yyvsp[(6) - (6)].ival))); }
    break;

  case 21:
#line 144 "as.y"
    { emit(rrr(OP_NAND, (yyvsp[(2) - (6)].ival), (yyvsp[(4) - (6)].ival), (yyvsp[(6) - (6)].ival))); }
    break;

  case 22:
#line 145 "as.y"
    { emit(ri(OP_LUI, (yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].ival))); }
    break;

  case 23:
#line 146 "as.y"
    { emit(rri(OP_SW, (yyvsp[(2) - (6)].ival), (yyvsp[(4) - (6)].ival), (yyvsp[(6) - (6)].ival))); }
    break;

  case 24:
#line 147 "as.y"
    { emit(rri(OP_LW, (yyvsp[(2) - (6)].ival), (yyvsp[(4) - (6)].ival), (yyvsp[(6) - (6)].ival))); }
    break;

  case 25:
#line 148 "as.y"
    { emit(rri(OP_BEQ, (yyvsp[(2) - (6)].ival), (yyvsp[(4) - (6)].ival), (yyvsp[(6) - (6)].ival))); }
    break;

  case 26:
#line 149 "as.y"
    { emit(rri(OP_JALR, (yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].ival), 0)); }
    break;

  case 27:
#line 150 "as.y"
    { emit(rri(OP_JALR, 0, 6, 0)); }
    break;

  case 28:
#line 151 "as.y"
    { emit(rri(OP_ADDI, 7, 7, -1)); emit(rri(OP_SW, (yyvsp[(2) - (2)].ival), 7, 0)); }
    break;

  case 29:
#line 152 "as.y"
    { emit(rri(OP_LW, (yyvsp[(2) - (2)].ival), 7, 0)); emit(rri(OP_ADDI, 7, 7, 1)); }
    break;

  case 30:
#line 153 "as.y"
    { emit(rri(OP_JALR, 0, (yyvsp[(2) - (2)].ival), 0)); }
    break;

  case 31:
#line 154 "as.y"
    { emit(rri(OP_JALR, 6, (yyvsp[(2) - (2)].ival), 0)); }
    break;

  case 32:
#line 155 "as.y"
    { emit(ri(OP_LUI, (yyvsp[(2) - (4)].ival), ((yyvsp[(4) - (4)].ival) & 0xffc0) >> 6)); emit(rri(OP_ADDI, (yyvsp[(2) - (4)].ival), (yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].ival) & MASK_6b)); }
    break;

  case 33:
#line 156 "as.y"
    { emit(ri(OP_LUI, (yyvsp[(2) - (4)].ival), ((yyvsp[(4) - (4)].ival) & 0xffc0) >> 6)); emit(rri(OP_ADDI, (yyvsp[(2) - (4)].ival), (yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].ival) & MASK_6b)); }
    break;

  case 34:
#line 157 "as.y"
    { emit(rri(OP_ADDI, (yyvsp[(2) - (4)].ival), (yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].ival) & 0x3f)); }
    break;

  case 35:
#line 158 "as.y"
    { emit(rrr(OP_ADD, 0, 0, 0)); }
    break;

  case 36:
#line 159 "as.y"
    { emit(rri(OP_ADDI, (yyvsp[(2) - (2)].ival), (yyvsp[(2) - (2)].ival), 1)); }
    break;

  case 37:
#line 160 "as.y"
    { emit(rri(OP_ADDI, (yyvsp[(2) - (2)].ival), (yyvsp[(2) - (2)].ival), -1)); }
    break;

  case 38:
#line 161 "as.y"
    { emit((yyvsp[(2) - (2)].ival)); }
    break;

  case 39:
#line 162 "as.y"
    { for(int i = 0; i < (yyvsp[(2) - (2)].ival); i++) emit(0); }
    break;

  case 40:
#line 163 "as.y"
    { emit(rri(OP_JALR, 0, 0, 1)); }
    break;

  case 41:
#line 164 "as.y"
    { emit(rri(OP_ADDI, (yyvsp[(2) - (4)].ival), (yyvsp[(4) - (4)].ival), 0)); }
    break;

  case 42:
#line 167 "as.y"
    { (yyval.ival) = 0; }
    break;

  case 43:
#line 168 "as.y"
    { (yyval.ival) = 1; }
    break;

  case 44:
#line 169 "as.y"
    { (yyval.ival) = 2; }
    break;

  case 45:
#line 170 "as.y"
    { (yyval.ival) = 3; }
    break;

  case 46:
#line 171 "as.y"
    { (yyval.ival) = 4; }
    break;

  case 47:
#line 172 "as.y"
    { (yyval.ival) = 5; }
    break;

  case 48:
#line 173 "as.y"
    { (yyval.ival) = 6; }
    break;

  case 49:
#line 174 "as.y"
    { (yyval.ival) = 7; }
    break;

  case 50:
#line 175 "as.y"
    { (yyval.ival) = 5; }
    break;

  case 51:
#line 176 "as.y"
    { (yyval.ival) = 6; }
    break;

  case 52:
#line 177 "as.y"
    { (yyval.ival) = 7; }
    break;


/* Line 1267 of yacc.c.  */
#line 1775 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 180 "as.y"


// define our keyword token table
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
    {"FP", FP},

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
    { "MOV", MOV},
    { "LWI", LWI},

    { ".FILL", FILL},
    { ".SPACE", SPACE},
    { "HALT", HALT},

    { NULL, 0}
};

//========================
// error routine
//========================
void yyerror(char *s)
{
    fprintf(stderr, "error: %s near line %d\n", s, lineno);
    err_count++;
}

// get options from the command line
int getopt(int n, char *args[])
{
	int i;
    
	for (i = 1; args[i] && args[i][0] == '-'; i++)
	{
        // flag for enabling verbose logging
		if (args[i][1] == 'v')
			g_bDebug = TRUE;

        // flag for generating Verilog rom
        if (args[i][1] == 'r')
            g_bROM = TRUE;

        // flag for generating SystemVerilog rom
        if (args[i][1] == 's')
        {
            g_bROM      = TRUE;
            g_bSystemV  = TRUE;
            input_wire  = "logic";
            output_reg  = "logic";
            reg         = "logic";
            always_comb = "always_comb";
            always_ff   = "always_ff";
        }

        // flag for generating an async rom
        if (args[i][1] == 'a')
        {
            g_bROM      = TRUE;
            g_bSyncROM  = FALSE;
        }

        // flag for setting output file name
		if (args[i][1] == 'o')
		{
			g_szOutputFilename = args[i + 1];
			i++;
		}

        // flag for taking input from stdio
        if (args[i][1] == 'i')
            yyin = stdin;
	}

	return i;
}

// add a fixup
void add_fixup(int symbol, int addr, int type)
{
    assert(fixup_count < MAX_FIXUPS);

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

        // check that the symbols was defined
        if (symbols[f.symbol].type == ST_UNDEF)
        {
            fprintf(stderr, "error: undefined symbol %s near line %d\n", symbols[f.symbol].name, symbols[f.symbol].lineno);
            err_count++;
            continue;
        }

        // handle the specific fixup type
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
            code[f.addr] |= (symbols[f.symbol].value - (f.addr + 1)) & MASK_7b;
            break;

        default:
            fprintf(stderr, "Error: unknown fixup type!\n");
            assert(FALSE);
        }
    }
}

//========================
// lookup a symbol
//========================
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

//========================
// add a new symbols
//========================
int add_symbol(const char *name, int lineno)
{
    assert(symbol_count < MAX_SYMBOLS);

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

    return FALSE;
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
        return DONE;

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
    puts("-a\tgenerate asynchronous Verilog rom");
    puts("-s\tuse System Verilog\n");
	exit(0);

}

// generate template prologue
void prologue(const char *filename, FILE *f, int addr_bits, int data_bits) 
{
    fprintf(f, "`timescale 1ns / 1ps\n\n");
    fprintf(f, "//////////////////////////////////////////////////////////////////\n");
    fprintf(f, "// Verilog ROM file auto-generated from %s\n", filename);
    fprintf(f, "//\n");
    fprintf(f, "// Using as16, see https://github.com/mseminatore/as16\n");
    fprintf(f, "//////////////////////////////////////////////////////////////////\n");
    fprintf(f, "module rom\n");
    fprintf(f, "(\n");

    if (g_bSyncROM)
        fprintf(f, "\t%s clk,\n", input_wire);

    fprintf(f, "\t%s [%d : 0] addr,\n"
        "\t%s [%d : 0] data\n"
        ");\n\n",
        input_wire,
        addr_bits - 1,
        output_reg,
        data_bits - 1
    );

    if (g_bSyncROM)
        fprintf(f, "\t// internal address register\n"
            "\t%s [%d : 0] addr_reg;\n\n"
            "\t//--------------------\n"
            "\t// Sequential logic\n"
            "\t//--------------------\n"
            "\t%s\n"
            "\t\taddr_reg <= addr;\n\n",
            reg,
            addr_bits - 1,
            always_ff
        );

    fprintf(f, "\t//--------------------\n"
        "\t// Combinational logic\n"
        "\t//--------------------\n"
        "\t%s\n",
        always_comb
    );

    if (g_bSyncROM)
        fprintf(f, "\t\tcase (addr_reg)\n");
    else
        fprintf(f, "\t\tcase (addr)\n");
}

//==========================
// generate template epilog
//==========================
void epilog(FILE *f) 
{
    fputs("\t\tendcase\n", f);
    fputs("endmodule\n", f);
}

//========================
// generate ROM data
//========================
void romgen(const char *filename, FILE *fout, int addr_bits, int data_bits)
{
    int num;

    prologue(filename, fout, addr_bits, data_bits);

    // loop over the code and output Verilog
    for (int i = 0; i < addr; i++)
    {
        num = code[i];
        fprintf(fout, "\t\t\t%d'd%d: data = %d'h%X;\t// decimal: %d\n", addr_bits, i, data_bits, num, num);
    }
    
    fprintf(fout, "\t\t\tdefault: data = %d'd0;\n", data_bits);

    epilog(fout);
}

//========================
// main entry point
//========================
int main(int argc, char *argv[])
{
    char infile[BUF_SIZE] = "stdin";

    // show usage if no arguments given
    if (argc == 1)
		usage();

	int iFirstArg = getopt(argc, argv);

    if (yyin != stdin)
    {
        yyin = fopen(argv[iFirstArg], "rt");
        strcpy(infile, argv[iFirstArg]);
    }

    // set this to 0 to disable parser debugging
    yydebug = 0;

    fout = fopen(g_szOutputFilename, "wb");

    // parse the input file
    yyparse();

    // fixup any forward references
    apply_fixups();

    // output hex code or rom file
    if (g_bROM)
        romgen(infile, fout, ADDRESS_BITS, INSTRUCTION_BITS);
    else
        write_file();

    fclose(fout);

    if (yyin != stdin)
        fclose(yyin);
    
    printf("\nAssembled %d instructions to %s\n", addr, g_szOutputFilename);
    if (err_count)
        printf("%d errors found.\n\n", err_count);

    return 0;
}

