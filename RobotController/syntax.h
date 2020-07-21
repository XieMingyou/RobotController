/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_SYNTAX_H_INCLUDED
# define YY_YY_SYNTAX_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SPACE = 258,
    COMMENT = 259,
    str = 260,
    bl = 261,
    TYPE = 262,
    a1 = 263,
    a2 = 264,
    a3 = 265,
    a4 = 266,
    a5 = 267,
    a6 = 268,
    aux1 = 269,
    aux2 = 270,
    aux3 = 271,
    aux4 = 272,
    aux5 = 273,
    x = 274,
    y = 275,
    z = 276,
    a = 277,
    b = 278,
    c = 279,
    mode = 280,
    baseRefSys = 281,
    velAxis = 282,
    accAxis = 283,
    decAxis = 284,
    jerkAxis = 285,
    velPath = 286,
    accPath = 287,
    decPath = 288,
    jerkPath = 289,
    velOri = 290,
    accOri = 291,
    decOri = 292,
    jerkOri = 293,
    World = 294,
    PTP = 295,
    Lin = 296,
    Circ = 297,
    PTPRel = 298,
    LinRel = 299,
    StopRobot = 300,
    RefRobotAxis = 301,
    RefRobotAxisAsync = 302,
    MoveRobotAxis = 303,
    Dyn = 304,
    Dynovr = 305,
    Ramp = 306,
    Refsys = 307,
    Tool = 308,
    WaitTime = 309,
    Stop = 310,
    Notice = 311,
    Warning = 312,
    Error = 313,
    CALL = 314,
    WAIT = 315,
    IF = 316,
    THEN = 317,
    ELSE = 318,
    ELSEIF = 319,
    END_IF = 320,
    WHILE = 321,
    DO = 322,
    END_WHILE = 323,
    LOOP = 324,
    END_LOOP = 325,
    RUN = 326,
    KILL = 327,
    RETURN = 328,
    GOTO = 329,
    intgr = 330,
    flt = 331,
    id = 332,
    ASSIGN = 333,
    MINUS = 334,
    LP = 335,
    RP = 336,
    LC = 337,
    RC = 338,
    COMMA = 339,
    COLON = 340,
    AND = 341,
    OR = 342,
    XOR = 343,
    MUL = 344,
    DIV = 345,
    PLUS = 346,
    EQ = 347,
    NE = 348,
    LE = 349,
    LT = 350,
    GE = 351,
    GT = 352,
    NOT = 353,
    DOT = 354,
    ERROR = 355,
    UMINUS = 356
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 8 "syntax.y" /* yacc.c:1909  */

	struct AST *a;

#line 160 "syntax.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_H_INCLUDED  */
