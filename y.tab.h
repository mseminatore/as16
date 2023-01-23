/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
     RET = 271,
     PUSH = 272,
     POP = 273,
     CALL = 274,
     J = 275,
     MOVI = 276,
     LLI = 277,
     NOP = 278,
     NUMBER = 279,
     R0 = 280,
     R1 = 281,
     R2 = 282,
     R3 = 283,
     R4 = 284,
     R5 = 285,
     R6 = 286,
     R7 = 287,
     LR = 288,
     SP = 289,
     FP = 290,
     FILL = 291,
     SPACE = 292,
     HALT = 293
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
#define RET 271
#define PUSH 272
#define POP 273
#define CALL 274
#define J 275
#define MOVI 276
#define LLI 277
#define NOP 278
#define NUMBER 279
#define R0 280
#define R1 281
#define R2 282
#define R3 283
#define R4 284
#define R5 285
#define R6 286
#define R7 287
#define LR 288
#define SP 289
#define FP 290
#define FILL 291
#define SPACE 292
#define HALT 293




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 87 "as.y"
{
    int ival;
    int symbol;
    char *lexeme;
}
/* Line 1529 of yacc.c.  */
#line 131 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

