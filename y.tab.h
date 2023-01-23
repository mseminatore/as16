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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 87 "as.y"
{
    int ival;
    int symbol;
    char *lexeme;
}
/* Line 1529 of yacc.c.  */
#line 135 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

