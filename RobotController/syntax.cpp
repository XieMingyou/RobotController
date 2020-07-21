/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "syntax.y" /* yacc.c:339  */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "lexicon.h"
#include "semantics.h"//���ű�ͳ�������������

#line 73 "syntax.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.h".  */
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
#line 8 "syntax.y" /* yacc.c:355  */

	struct AST *a;

#line 219 "syntax.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 236 "syntax.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   651

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  102
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  166
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  409

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   356

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    44,    44,    50,    51,    56,    57,    61,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      81,    82,    83,    84,    88,    89,    95,    96,   102,   107,
     111,   112,   113,   114,   115,   118,   124,   128,   138,   146,
     147,   151,   152,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   189,   193,   201,   205,   213,   219,   229,
     232,   240,   243,   251,   257,   260,   263,   268,   273,   283,
     284,   290,   295,   298,   308,   314,   317,   321,   327,   330,
     334,   340,   341,   342,   348,   354,   357,   361,   364,   368,
     371,   375,   376,   380,   412,   416,   417,   418,   419,   420,
     421,   425,   426,   427,   428,   429,   430,   434,   435,   439,
     440,   444,   445,   448,   449,   455,   486,   502,   506,   507,
     511,   515,   519,   520,   524,   525,   526,   527,   528,   529,
     530,   531,   532,   533,   534,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SPACE", "COMMENT", "str", "bl", "TYPE",
  "a1", "a2", "a3", "a4", "a5", "a6", "aux1", "aux2", "aux3", "aux4",
  "aux5", "x", "y", "z", "a", "b", "c", "mode", "baseRefSys", "velAxis",
  "accAxis", "decAxis", "jerkAxis", "velPath", "accPath", "decPath",
  "jerkPath", "velOri", "accOri", "decOri", "jerkOri", "World", "PTP",
  "Lin", "Circ", "PTPRel", "LinRel", "StopRobot", "RefRobotAxis",
  "RefRobotAxisAsync", "MoveRobotAxis", "Dyn", "Dynovr", "Ramp", "Refsys",
  "Tool", "WaitTime", "Stop", "Notice", "Warning", "Error", "CALL", "WAIT",
  "IF", "THEN", "ELSE", "ELSEIF", "END_IF", "WHILE", "DO", "END_WHILE",
  "LOOP", "END_LOOP", "RUN", "KILL", "RETURN", "GOTO", "intgr", "flt",
  "id", "ASSIGN", "MINUS", "LP", "RP", "LC", "RC", "COMMA", "COLON", "AND",
  "OR", "XOR", "MUL", "DIV", "PLUS", "EQ", "NE", "LE", "LT", "GE", "GT",
  "NOT", "DOT", "ERROR", "UMINUS", "$accept", "Var_Prog", "Var",
  "DefinitionList", "Definition", "type", "real", "axisPos", "cartPos",
  "robAxisPos", "robCartPos", "auxAxisPos", "cartSys", "cartRefSys",
  "dynamic", "Prog", "StatementList", "Statement", "PTP_stm", "Lin_stm",
  "Circ_stm", "PTPRel_stm", "LinRel_stm", "StopRobot_stm",
  "RefRobotAxis_stm", "RefRobotAxisAsync_stm", "MoveRobotAxis_stm",
  "Dyn_stm", "Dynovr_stm", "Ramp_stm", "Refsys_stm", "Tool_stm",
  "WaitTime_stm", "Stop_stm", "Notice_stm", "Warning_stm", "Error_stm",
  "Condition", "CALL_stm", "WAIT_stm", "IF_stm", "ELSEIF_stm", "ELSE_stm",
  "WHILE_stm", "LOOP_stm", "RUN_stm", "KILL_stm", "RETURN_stm", "GOTO_stm",
  "LABEL_stm", "DOT_expr", "ASSIGN_stm", "Expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356
};
# endif

#define YYPACT_NINF -232

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-232)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -51,   -31,    22,    -4,    18,  -232,   -42,    28,  -232,   270,
    -232,    69,  -232,  -232,    43,    70,    79,    86,    98,   100,
     108,   109,   110,   111,   112,   113,   120,   121,   122,   123,
     125,   126,   131,   102,     6,     6,     6,    -6,   104,   127,
    -232,   135,   -57,  -232,   130,   504,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,   136,  -232,   137,   139,   141,
     147,   153,   167,   168,   192,    29,   198,   200,    -2,   205,
     -24,   206,   -20,   221,     2,    24,    25,   219,  -232,  -232,
    -232,  -232,   -60,    14,     6,    14,  -232,   136,  -232,   520,
     -27,   233,   234,   235,   223,   224,  -232,    14,  -232,   228,
    -232,  -232,    14,    32,    47,    56,   222,    57,    61,   226,
      63,   227,  -232,   248,   252,  -232,  -232,   253,    38,   254,
     256,   257,   259,   264,   265,   267,   268,   269,   271,   295,
     300,   301,   303,   308,   309,   315,  -232,  -232,   334,   501,
    -232,    14,    14,    14,    14,    14,    14,    14,    14,    14,
      14,    14,    14,    14,   207,   274,   352,   390,   428,   335,
     336,   520,  -232,   520,  -232,  -232,    60,    60,   -23,    60,
    -232,  -232,  -232,   101,  -232,  -232,  -232,    -1,     3,  -232,
    -232,  -232,  -232,   342,  -232,   345,   350,  -232,   351,  -232,
     375,  -232,  -232,    45,  -232,    50,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,   -41,   143,
     539,   -29,  -232,  -232,   -41,   -46,   -46,   -46,   -46,   -46,
     -46,   466,     6,  -232,    33,  -232,  -232,  -232,  -232,   385,
    -232,   384,  -232,   387,  -232,  -232,   446,   438,   447,   471,
     437,  -232,  -232,    60,  -232,   410,  -232,   411,   412,   414,
      65,   415,   422,    67,    76,    77,   423,  -232,   463,   467,
    -232,  -232,  -232,  -232,  -232,  -232,    60,    60,    60,    60,
      60,   515,  -232,  -232,  -232,  -232,  -232,   456,  -232,  -232,
    -232,   457,  -232,   459,  -232,   464,  -232,  -232,   314,   532,
     545,   547,   548,   540,    60,   490,   491,   493,   498,  -232,
      99,  -232,  -232,    60,    60,    60,    60,    60,   567,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,   573,   563,   565,   579,
     571,    60,    60,    60,    60,    60,    60,   585,   591,   581,
     583,   597,   589,    60,    60,    60,    60,    60,    60,   603,
     609,   599,   601,   614,   594,    60,    60,    60,    60,    60,
      60,  -232,  -232,   -11,   615,   616,   605,   566,  -232,    60,
      60,    60,  -232,   561,   562,   610,  -232,  -232,    60,   611,
      60,   612,    60,   608,    60,   613,    60,   568,  -232
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     4,     0,     6,     1,     0,
       2,     0,     3,     5,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     137,     0,     0,    40,     0,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,     0,    72,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   165,   166,
     163,   164,   162,     0,     0,     0,   114,   161,   112,   111,
       0,     0,     0,     0,     0,     0,   138,     0,   140,     0,
      39,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    89,     0,     0,    20,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   162,   161,   157,     0,     0,
     158,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,   141,   143,    13,    14,     0,     0,     0,     0,
       9,    10,     8,     0,     7,    15,    16,     0,     0,    17,
      18,    19,    73,     0,    75,     0,     0,    79,     0,    81,
       0,    83,    84,     0,    90,     0,    94,    95,    22,    23,
      96,    97,    99,    98,   100,   101,   102,   103,   104,   106,
     105,   108,   107,   110,   109,   113,   160,   159,   150,   144,
     145,   146,   147,   148,   149,   151,   152,   153,   154,   155,
     156,     0,     0,   120,     0,   118,   119,   139,   130,     0,
     133,     0,   134,     0,   135,   136,     0,     0,     0,     0,
       0,    11,    12,     0,    24,     0,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,     0,     0,
     117,   115,   116,   129,   131,   132,     0,     0,     0,     0,
       0,    30,    25,    27,    74,    76,    77,     0,    80,    82,
      86,     0,    85,     0,    91,     0,    92,   127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   126,
       0,   124,   125,     0,     0,     0,     0,     0,    31,    78,
      88,    87,    93,   123,   121,   122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    33,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    34,    28,     0,     0,     0,     0,     0,    35,     0,
       0,     0,    29,     0,     0,     0,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -232,  -232,  -232,   640,  -232,  -232,  -181,  -232,  -232,  -232,
    -232,   452,  -232,  -232,  -232,  -232,   -44,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
    -232,  -232,  -232,  -232,  -232,  -232,  -232,   -26,  -232,  -232,
    -232,  -231,  -230,  -232,  -232,  -232,  -232,  -232,  -232,  -232,
      -9,   -32,   124
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     6,     7,   194,   139,   195,   196,   197,
     198,   275,   199,   200,   201,    10,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,   106,    65,    66,
      67,   255,   256,    68,    69,    70,    71,    72,    73,    74,
     156,    76,   109
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      75,   121,   108,   108,   108,   266,   267,   148,   270,   110,
     111,    98,    99,   273,   387,   141,   268,   273,   117,    98,
      99,   117,     8,   291,   292,   107,   107,   107,   118,   150,
     152,     1,   284,   161,   286,   174,    75,   184,   185,   119,
     186,    12,   119,   165,   166,   167,     4,   175,   165,   166,
     161,   187,     5,   142,   269,   144,   145,   146,   188,   189,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   112,
     388,   113,   158,   135,   136,   137,    77,   138,     9,   149,
     274,   100,   101,   102,   276,   103,   104,   331,   332,   100,
     101,   155,   301,   103,   104,   107,   251,   252,   290,   344,
     345,   151,   153,    11,   105,     4,   131,   190,   191,   192,
     132,   193,   105,   218,   219,   319,   320,   321,   322,   323,
     135,   136,   283,    78,   138,   135,   136,   285,   202,   138,
     254,   203,   259,   261,   263,   135,   136,   204,   207,   138,
     205,   208,   209,   338,   212,   210,   306,   213,   310,   307,
      79,   311,   346,   347,   348,   349,   350,   312,   314,    80,
     313,   315,   251,   252,   343,    75,    81,    75,    75,    75,
     357,   358,   359,   360,   361,   362,   271,   272,    82,    97,
      83,   114,   369,   370,   371,   372,   373,   374,    84,    85,
      86,    87,    88,    89,   381,   382,   383,   384,   385,   386,
      90,    91,    92,    93,   115,    94,    95,   288,   393,   394,
     395,    96,   116,   120,   122,   123,   124,   399,   125,   401,
     108,   403,   161,   405,   126,   407,   289,   157,   159,   160,
     127,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   181,    75,   107,   128,   129,   183,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,   130,
     251,   252,   253,    36,   330,   133,    37,   134,    38,    39,
      40,    41,   140,   143,    42,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   147,   154,
     176,   177,   178,   179,   180,   182,   206,   211,   214,    75,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   215,   216,   217,   220,    36,   221,   222,    37,
     223,    38,    39,    40,    41,   224,   225,    42,   226,   227,
     228,   257,   229,    43,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,   230,   251,   252,   329,
      36,   231,   232,    37,   233,    38,    39,    40,    41,   234,
     235,    42,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,   119,   236,   264,   265,    36,   278,
     258,    37,   279,    38,    39,    40,    41,   280,   281,    42,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,   282,   293,   294,   296,    36,   295,   297,    37,
     260,    38,    39,    40,    41,   300,   298,    42,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
     299,   302,   303,   304,    36,   305,   308,    37,   262,    38,
      39,    40,    41,   309,   316,    42,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,   317,   318,
     324,   287,    36,   325,   326,    37,   327,    38,    39,    40,
      41,   328,   333,    42,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,   334,   335,   336,   337,
      36,   339,   340,    37,   341,    38,    39,    40,    41,   342,
     161,    42,   237,   351,   352,   353,   354,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   161,
     355,   356,   363,   364,   365,   366,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   161,   367,
     368,   375,   376,   377,   378,   162,   380,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   379,   391,   389,
     390,   392,   396,   397,   398,   404,   400,    13,   402,   408,
     277,   406
};

static const yytype_uint16 yycheck[] =
{
       9,    45,    34,    35,    36,   186,   187,     5,   189,    35,
      36,     5,     6,    14,    25,    39,    39,    14,    78,     5,
       6,    78,     0,   254,   254,    34,    35,    36,    85,     5,
       5,    82,   213,    79,   215,    62,    45,     5,     6,    99,
       8,    83,    99,    89,    90,    91,    77,    74,    89,    90,
      79,    19,    83,    77,    77,    75,    76,    77,    26,    27,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    75,
      81,    77,   104,    75,    76,    77,     7,    79,    82,    77,
      81,    75,    76,    77,    81,    79,    80,   318,   318,    75,
      76,    77,   273,    79,    80,   104,    63,    64,    65,   330,
     330,    77,    77,    85,    98,    77,    77,    75,    76,    77,
      81,    79,    98,    75,    76,   296,   297,   298,   299,   300,
      75,    76,    77,    80,    79,    75,    76,    77,    81,    79,
     174,    84,   176,   177,   178,    75,    76,    81,    81,    79,
      84,    84,    81,   324,    81,    84,    81,    84,    81,    84,
      80,    84,   333,   334,   335,   336,   337,    81,    81,    80,
      84,    84,    63,    64,    65,   174,    80,   176,   177,   178,
     351,   352,   353,   354,   355,   356,    75,    76,    80,    77,
      80,    77,   363,   364,   365,   366,   367,   368,    80,    80,
      80,    80,    80,    80,   375,   376,   377,   378,   379,   380,
      80,    80,    80,    80,    77,    80,    80,   251,   389,   390,
     391,    80,    77,    83,    78,    78,    77,   398,    77,   400,
     252,   402,    79,   404,    77,   406,   252,   103,   104,   105,
      77,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,   117,   251,   252,    77,    77,   122,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    77,
      63,    64,    65,    66,   318,    77,    69,    77,    71,    72,
      73,    74,    77,    77,    77,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,    77,    80,
      67,    67,    67,    80,    80,    77,    84,    81,    81,   318,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    84,    81,    81,    81,    66,    81,    81,    69,
      81,    71,    72,    73,    74,    81,    81,    77,    81,    81,
      81,    77,    81,    83,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    81,    63,    64,    65,
      66,    81,    81,    69,    81,    71,    72,    73,    74,    81,
      81,    77,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    99,    81,    81,    81,    66,    77,
      68,    69,    77,    71,    72,    73,    74,    77,    77,    77,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    77,    68,    70,     9,    66,    70,    20,    69,
      70,    71,    72,    73,    74,    28,    19,    77,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      19,    81,    81,    81,    66,    81,    81,    69,    70,    71,
      72,    73,    74,    81,    81,    77,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    65,    62,
      15,    65,    66,    77,    77,    69,    77,    71,    72,    73,
      74,    77,    10,    77,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    21,    20,    20,    29,
      66,    81,    81,    69,    81,    71,    72,    73,    74,    81,
      79,    77,    81,    16,    11,    22,    21,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    79,
      21,    30,    17,    12,    23,    22,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    79,    22,
      31,    18,    13,    24,    23,    86,    32,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    23,    33,    24,
      24,    75,    81,    81,    34,    37,    35,     7,    36,    81,
     198,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,   103,   104,    77,    83,   105,   106,     0,    82,
     117,    85,    83,   105,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    66,    69,    71,    72,
      73,    74,    77,    83,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   140,   141,   142,   145,   146,
     147,   148,   149,   150,   151,   152,   153,     7,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    77,     5,     6,
      75,    76,    77,    79,    80,    98,   139,   152,   153,   154,
     139,   139,    75,    77,    77,    77,    77,    78,    85,    99,
      83,   118,    78,    78,    77,    77,    77,    77,    77,    77,
      77,    77,    81,    77,    77,    75,    76,    77,    79,   108,
      77,    39,    77,    77,    75,    76,    77,    77,     5,    77,
       5,    77,     5,    77,    80,    77,   152,   154,   153,   154,
     154,    79,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    62,    74,    67,    67,    67,    80,
      80,   154,    77,   154,     5,     6,     8,    19,    26,    27,
      75,    76,    77,    79,   107,   109,   110,   111,   112,   114,
     115,   116,    81,    84,    81,    84,    84,    81,    84,    81,
      84,    81,    81,    84,    81,    84,    81,    81,    75,    76,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,    63,    64,    65,   118,   143,   144,    77,    68,   118,
      70,   118,    70,   118,    81,    81,   108,   108,    39,    77,
     108,    75,    76,    14,    81,   113,    81,   113,    77,    77,
      77,    77,    77,    77,   108,    77,   108,    65,   118,   139,
      65,   143,   144,    68,    70,    70,     9,    20,    19,    19,
      28,   108,    81,    81,    81,    81,    81,    84,    81,    81,
      81,    84,    81,    84,    81,    84,    81,    65,    62,   108,
     108,   108,   108,   108,    15,    77,    77,    77,    77,    65,
     118,   143,   144,    10,    21,    20,    20,    29,   108,    81,
      81,    81,    81,    65,   143,   144,   108,   108,   108,   108,
     108,    16,    11,    22,    21,    21,    30,   108,   108,   108,
     108,   108,   108,    17,    12,    23,    22,    22,    31,   108,
     108,   108,   108,   108,   108,    18,    13,    24,    23,    23,
      32,   108,   108,   108,   108,   108,   108,    25,    81,    24,
      24,    33,    75,   108,   108,   108,    81,    81,    34,   108,
      35,   108,    36,   108,    37,   108,    38,   108,    81
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   102,   103,   104,   104,   105,   105,   106,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     108,   108,   108,   108,   109,   109,   110,   110,   111,   112,
     113,   113,   113,   113,   113,   114,   115,   115,   116,   117,
     117,   118,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   121,   121,   122,   122,   123,
     123,   124,   124,   125,   126,   126,   126,   126,   126,   127,
     127,   128,   128,   128,   129,   130,   130,   131,   132,   132,
     133,   134,   134,   134,   135,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   141,   142,   142,   142,   142,   142,
     142,   143,   143,   143,   143,   143,   143,   144,   144,   145,
     145,   146,   146,   146,   146,   147,   148,   149,   150,   150,
     151,   152,   153,   153,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     2,     2,     1,     5,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     3,     2,     3,    12,    14,
       2,     4,     6,     8,    10,    13,    15,    15,    25,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     6,     4,     6,     6,     8,     4,
       6,     4,     6,     4,     4,     6,     6,     8,     8,     3,
       4,     6,     6,     8,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     1,     1,     4,     2,     5,     5,     5,     4,     4,
       4,     5,     5,     5,     4,     4,     4,     3,     2,     5,
       4,     5,     5,     4,     4,     4,     4,     1,     2,     4,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       3,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 44 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Var_Prog",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->varProgName = curVarProg; rootTail->next = (yyval.a); rootTail = (yyval.a); setThisRoot((yyval.a)); 
	printf("��ӡsyntax tree:\n"); traverse((yyval.a),1); printf("syntax tree��ӡ���!\n"); }
#line 1651 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 50 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Var",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 1657 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 51 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Var",2,(yyvsp[-1].a),(yyvsp[0].a)); }
#line 1663 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 56 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("DefinitionList",2,(yyvsp[-1].a),(yyvsp[0].a)); }
#line 1669 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 57 "syntax.y" /* yacc.c:1646  */
    {(yyval.a) = newAst("DefinitionList",1, (yyvsp[0].a)); }
#line 1675 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 61 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Definition",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); defTypeError((yyvsp[-2].a), (yyvsp[0].a)); newVar((yyvsp[-4].a),(yyvsp[0].a)); 
	if ((!strcmp((yyvsp[-4].a)->content, "x")) || (!strcmp((yyvsp[-4].a)->content, "a1")) || (!strcmp((yyvsp[-4].a)->content, "baseRefSys")) || (!strcmp((yyvsp[-4].a)->content, "velAxis")) || (!strcmp((yyvsp[-4].a)->content, "World")))
	{ printf("Error at Line %d: The content of the variable can not be 'x' or 'a1' or 'baseRefSys' or 'velAxis' or 'World'. Please delete variable '%s'.\n", yylineno, (yyvsp[-4].a)->content); flag = 1; }}
#line 1683 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 67 "syntax.y" /* yacc.c:1646  */
    { existVar((yyvsp[0].a)); (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1689 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 68 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1695 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 69 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1701 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 70 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->type = "INTEGER"; (yyval.a)->intgr = -((yyvsp[0].a)->intgr); }
#line 1707 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 71 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->type = "FLOAT"; (yyval.a)->flt = -((yyvsp[0].a)->flt); }
#line 1713 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 72 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1719 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 73 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1725 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 74 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1731 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 75 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1737 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 76 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1743 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 77 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); (yyval.a)->cartSys = (yyvsp[0].a)->cartSys;}
#line 1749 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 78 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("type",1,(yyvsp[0].a)); }
#line 1755 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 81 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("real",1,(yyvsp[0].a)); (yyval.a)->type = "FLOAT"; (yyval.a)->flt = (yyvsp[0].a)->intgr; }
#line 1761 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 82 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("real",1,(yyvsp[0].a)); (yyval.a)->type = "FLOAT"; (yyval.a)->flt = (yyvsp[0].a)->flt; }
#line 1767 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 83 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("real",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->type = "FLOAT"; (yyval.a)->flt = -((yyvsp[0].a)->intgr); }
#line 1773 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 84 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("real",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->type = "FLOAT"; (yyval.a)->flt = -((yyvsp[0].a)->flt); }
#line 1779 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 88 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("axisPos",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->type = "AXISPOS"; (yyval.a)->axisPos = (yyvsp[-1].a)->axisPos; }
#line 1785 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 89 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("axisPos",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	(yyval.a)->type = "AXISPOS"; (yyval.a)->axisPos = (yyvsp[-2].a)->axisPos; 
	(yyval.a)->axisPos.aux1 = (yyvsp[-1].a)->auxAxisPos.aux1; (yyval.a)->axisPos.aux2 = (yyvsp[-1].a)->auxAxisPos.aux2; (yyval.a)->axisPos.aux3 = (yyvsp[-1].a)->auxAxisPos.aux3; (yyval.a)->axisPos.aux4 = (yyvsp[-1].a)->auxAxisPos.aux4; (yyval.a)->axisPos.aux5 = (yyvsp[-1].a)->auxAxisPos.aux5; }
#line 1793 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 95 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("cartPos",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->type = "CARTPOS"; (yyval.a)->cartPos = (yyvsp[-1].a)->cartPos; }
#line 1799 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 96 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("cartPos",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	(yyval.a)->type = "CARTPOS"; (yyval.a)->cartPos = (yyvsp[-2].a)->cartPos;
	(yyval.a)->cartPos.aux1 = (yyvsp[-1].a)->auxAxisPos.aux1; (yyval.a)->cartPos.aux2 = (yyvsp[-1].a)->auxAxisPos.aux2; (yyval.a)->cartPos.aux3 = (yyvsp[-1].a)->auxAxisPos.aux3; (yyval.a)->cartPos.aux4 = (yyvsp[-1].a)->auxAxisPos.aux4; (yyval.a)->cartPos.aux5 = (yyvsp[-1].a)->auxAxisPos.aux5; }
#line 1807 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 102 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("robAxisPos",12,(yyvsp[-11].a),(yyvsp[-10].a),(yyvsp[-9].a),(yyvsp[-8].a),(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	(yyval.a)->axisPos.a1 = (yyvsp[-10].a)->flt; (yyval.a)->axisPos.a2 = (yyvsp[-8].a)->flt; (yyval.a)->axisPos.a3 = (yyvsp[-6].a)->flt; (yyval.a)->axisPos.a4 = (yyvsp[-4].a)->flt; (yyval.a)->axisPos.a5 = (yyvsp[-2].a)->flt; (yyval.a)->axisPos.a6 = (yyvsp[0].a)->flt; }
#line 1814 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 107 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("robCartPos",14,(yyvsp[-13].a),(yyvsp[-12].a),(yyvsp[-11].a),(yyvsp[-10].a),(yyvsp[-9].a),(yyvsp[-8].a),(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	(yyval.a)->cartPos.x = (yyvsp[-12].a)->flt; (yyval.a)->cartPos.y = (yyvsp[-10].a)->flt; (yyval.a)->cartPos.z = (yyvsp[-8].a)->flt; (yyval.a)->cartPos.a = (yyvsp[-6].a)->flt; (yyval.a)->cartPos.b = (yyvsp[-4].a)->flt; (yyval.a)->cartPos.c = (yyvsp[-2].a)->flt; (yyval.a)->cartPos.mode = (yyvsp[0].a)->intgr; }
#line 1821 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 111 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("auxAxisPos",2,(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->auxAxisPos.aux1 = (yyvsp[0].a)->flt; }
#line 1827 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 112 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("auxAxisPos",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->auxAxisPos.aux1 = (yyvsp[-2].a)->flt; (yyval.a)->auxAxisPos.aux2 = (yyvsp[0].a)->flt; }
#line 1833 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 113 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("auxAxisPos",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->auxAxisPos.aux1 = (yyvsp[-4].a)->flt; (yyval.a)->auxAxisPos.aux2 = (yyvsp[-2].a)->flt; (yyval.a)->auxAxisPos.aux3 = (yyvsp[0].a)->flt; }
#line 1839 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 114 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("auxAxisPos",8,(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->auxAxisPos.aux1 = (yyvsp[-6].a)->flt; (yyval.a)->auxAxisPos.aux2 = (yyvsp[-4].a)->flt; (yyval.a)->auxAxisPos.aux3 = (yyvsp[-2].a)->flt; (yyval.a)->auxAxisPos.aux4 = (yyvsp[0].a)->flt; }
#line 1845 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 115 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("auxAxisPos",10,(yyvsp[-9].a),(yyvsp[-8].a),(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); (yyval.a)->auxAxisPos.aux1 = (yyvsp[-8].a)->flt; (yyval.a)->auxAxisPos.aux2 = (yyvsp[-6].a)->flt; (yyval.a)->auxAxisPos.aux3 = (yyvsp[-4].a)->flt; (yyval.a)->auxAxisPos.aux4 = (yyvsp[-2].a)->flt; (yyval.a)->auxAxisPos.aux5 = (yyvsp[0].a)->flt;}
#line 1851 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 118 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("cartSys",13,(yyvsp[-12].a),(yyvsp[-11].a),(yyvsp[-10].a),(yyvsp[-9].a),(yyvsp[-8].a),(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));
	(yyval.a)->type = "CARTSYS"; 
	(yyval.a)->cartSys.x = (yyvsp[-11].a)->flt; (yyval.a)->cartSys.y = (yyvsp[-9].a)->flt; (yyval.a)->cartSys.z = (yyvsp[-7].a)->flt; (yyval.a)->cartSys.a = (yyvsp[-5].a)->flt; (yyval.a)->cartSys.b = (yyvsp[-3].a)->flt; (yyval.a)->cartSys.c = (yyvsp[-1].a)->flt; }
#line 1859 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 124 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("cartRefSys",15,(yyvsp[-14].a),(yyvsp[-13].a),(yyvsp[-12].a),(yyvsp[-11].a),(yyvsp[-10].a),(yyvsp[-9].a),(yyvsp[-8].a),(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));
	(yyval.a)->type = "CARTREFSYS";
	(yyval.a)->cartRefSys.baseRefSys = (yyvsp[-13].a)->content; (yyval.a)->cartRefSys.x = (yyvsp[-11].a)->flt; (yyval.a)->cartRefSys.y = (yyvsp[-9].a)->flt; (yyval.a)->cartRefSys.z = (yyvsp[-7].a)->flt; (yyval.a)->cartRefSys.a = (yyvsp[-5].a)->flt; (yyval.a)->cartRefSys.b = (yyvsp[-3].a)->flt; (yyval.a)->cartRefSys.c = (yyvsp[-1].a)->flt; 
	(yyval.a)->cartSys.x = (yyvsp[-11].a)->flt; (yyval.a)->cartSys.y = (yyvsp[-9].a)->flt; (yyval.a)->cartSys.z = (yyvsp[-7].a)->flt; (yyval.a)->cartSys.a = (yyvsp[-5].a)->flt; (yyval.a)->cartSys.b = (yyvsp[-3].a)->flt; (yyval.a)->cartSys.c = (yyvsp[-1].a)->flt; }
#line 1868 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 128 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("cartRefSys",15,(yyvsp[-14].a),(yyvsp[-13].a),(yyvsp[-12].a),(yyvsp[-11].a),(yyvsp[-10].a),(yyvsp[-9].a),(yyvsp[-8].a),(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-13].a)); var2ast((yyvsp[-13].a));
	(yyval.a)->type = "CARTREFSYS";
	if (strcmp((yyvsp[-13].a)->type, "CARTREFSYS"))
	{ printf("Error at Line %d: The type of '%s' is not 'CARTREFSYS'.\n", yylineno, (yyvsp[-13].a)->content); flag = 1;}
	(yyval.a)->cartRefSys.baseRefSys = (yyvsp[-13].a)->content; (yyval.a)->cartRefSys.x = (yyvsp[-11].a)->flt; (yyval.a)->cartRefSys.y = (yyvsp[-9].a)->flt; (yyval.a)->cartRefSys.z = (yyvsp[-7].a)->flt; (yyval.a)->cartRefSys.a = (yyvsp[-5].a)->flt; (yyval.a)->cartRefSys.b = (yyvsp[-3].a)->flt; (yyval.a)->cartRefSys.c = (yyvsp[-1].a)->flt; 
	(yyval.a)->cartSys.x = (yyvsp[-11].a)->flt; (yyval.a)->cartSys.y = (yyvsp[-9].a)->flt; (yyval.a)->cartSys.z = (yyvsp[-7].a)->flt; (yyval.a)->cartSys.a = (yyvsp[-5].a)->flt; (yyval.a)->cartSys.b = (yyvsp[-3].a)->flt; (yyval.a)->cartSys.c = (yyvsp[-1].a)->flt;
	calculateCartSys((yyval.a), (yyvsp[-13].a)); }
#line 1880 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 138 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("dynamic",25,(yyvsp[-24].a),(yyvsp[-23].a),(yyvsp[-22].a),(yyvsp[-21].a),(yyvsp[-20].a),(yyvsp[-19].a),(yyvsp[-18].a),(yyvsp[-17].a),(yyvsp[-16].a),(yyvsp[-15].a),(yyvsp[-14].a),(yyvsp[-13].a),(yyvsp[-12].a),(yyvsp[-11].a),(yyvsp[-10].a),(yyvsp[-9].a),(yyvsp[-8].a),(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	(yyval.a)->type = "DYNAMIC";
	(yyval.a)->dynamic.velAxis = (yyvsp[-23].a)->flt; (yyval.a)->dynamic.accAxis = (yyvsp[-21].a)->flt; (yyval.a)->dynamic.decAxis = (yyvsp[-19].a)->flt; (yyval.a)->dynamic.jerkAxis = (yyvsp[-17].a)->flt; (yyval.a)->dynamic.velPath = (yyvsp[-15].a)->flt; (yyval.a)->dynamic.accPath = (yyvsp[-13].a)->flt; 
	(yyval.a)->dynamic.decPath = (yyvsp[-11].a)->flt; (yyval.a)->dynamic.jerkPath = (yyvsp[-9].a)->flt; (yyval.a)->dynamic.velOri = (yyvsp[-7].a)->flt; (yyval.a)->dynamic.accOri = (yyvsp[-5].a)->flt; (yyval.a)->dynamic.decOri = (yyvsp[-3].a)->flt; (yyval.a)->dynamic.jerkOri = (yyvsp[-1].a)->flt; }
#line 1889 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 146 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Prog",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 1895 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 147 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Prog",2,(yyvsp[-1].a),(yyvsp[0].a)); }
#line 1901 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 151 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("StatementList",2,(yyvsp[-1].a),(yyvsp[0].a)); }
#line 1907 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 152 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("StatementList",1,(yyvsp[0].a)); }
#line 1913 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 156 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1919 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 157 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1925 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 158 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1931 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 159 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1937 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 160 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1943 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 161 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1949 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 162 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1955 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 163 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1961 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 164 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1967 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 165 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1973 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 166 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1979 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 167 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1985 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 168 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1991 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 169 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 1997 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 170 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2003 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 171 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2009 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 172 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2015 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 173 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2021 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 174 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2027 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 175 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2033 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 176 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2039 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 177 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2045 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 178 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2051 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 179 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2057 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 180 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2063 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 181 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2069 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 182 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2075 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 183 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2081 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 184 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2087 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 185 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Statement",1,(yyvsp[0].a)); }
#line 2093 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 189 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("PTP_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-1].a)->type, "AXISPOS") && strcmp((yyvsp[-1].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2101 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 193 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("PTP_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-3].a)->type, "AXISPOS") && strcmp((yyvsp[-3].a)->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2111 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 201 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Lin_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-1].a)->type, "AXISPOS") && strcmp((yyvsp[-1].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2119 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 205 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Lin_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));  existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-3].a)->type, "AXISPOS") && strcmp((yyvsp[-3].a)->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2129 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 213 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Circ_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));  existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-3].a)->type, "AXISPOS") && strcmp((yyvsp[-3].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "AXISPOS") && strcmp((yyvsp[-1].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2139 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 219 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Circ_stm",8,(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));  existVar((yyvsp[-5].a)); existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-5].a)->type, "AXISPOS") && strcmp((yyvsp[-5].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-5].a)->content); flag = 1; }
	if (strcmp((yyvsp[-3].a)->type, "AXISPOS") && strcmp((yyvsp[-3].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2151 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 229 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("PTPRel_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-1].a)->type, "AXISPOS") && strcmp((yyvsp[-1].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2159 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 232 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("PTPRel_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-3].a)->type, "AXISPOS") && strcmp((yyvsp[-3].a)->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2169 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 240 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("LinRel_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-1].a)->type, "AXISPOS") && strcmp((yyvsp[-1].a)->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2177 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 243 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("LinRel_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-3].a)->type, "AXISPOS") && strcmp((yyvsp[-3].a)->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2187 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 251 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("StopRobot_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));
	if (strcmp((yyvsp[-1].a)->content, "HARDSTOP") && strcmp((yyvsp[-1].a)->content, "SOFTSTOP"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2195 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 257 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("RefRobotAxis_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	if (strcmp((yyvsp[-1].a)->content, "A1") && strcmp((yyvsp[-1].a)->content, "A2") && strcmp((yyvsp[-1].a)->content, "A3") && strcmp((yyvsp[-1].a)->content, "A4") && strcmp((yyvsp[-1].a)->content, "A5") && strcmp((yyvsp[-1].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2203 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 260 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("RefRobotAxis_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));
	if (strcmp((yyvsp[-3].a)->content, "A1") && strcmp((yyvsp[-3].a)->content, "A2") && strcmp((yyvsp[-3].a)->content, "A3") && strcmp((yyvsp[-3].a)->content, "A4") && strcmp((yyvsp[-3].a)->content, "A5") && strcmp((yyvsp[-3].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }}
#line 2211 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 263 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("RefRobotAxis_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-3].a)->content, "A1") && strcmp((yyvsp[-3].a)->content, "A2") && strcmp((yyvsp[-3].a)->content, "A3") && strcmp((yyvsp[-3].a)->content, "A4") && strcmp((yyvsp[-3].a)->content, "A5") && strcmp((yyvsp[-3].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "INTEGER") && strcmp((yyvsp[-1].a)->type, "FLOAT") && strcmp((yyvsp[-1].a)->type, "DYNAMIC")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2221 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 268 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("RefRobotAxis_stm",8,(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-5].a)->content, "A1") && strcmp((yyvsp[-5].a)->content, "A2") && strcmp((yyvsp[-5].a)->content, "A3") && strcmp((yyvsp[-5].a)->content, "A4") && strcmp((yyvsp[-5].a)->content, "A5") && strcmp((yyvsp[-5].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-5].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2231 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 273 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("RefRobotAxis_stm",8,(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-5].a)->content, "A1") && strcmp((yyvsp[-5].a)->content, "A2") && strcmp((yyvsp[-5].a)->content, "A3") && strcmp((yyvsp[-5].a)->content, "A4") && strcmp((yyvsp[-5].a)->content, "A5") && strcmp((yyvsp[-5].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-5].a)->content); flag = 1; }
	if (strcmp((yyvsp[-3].a)->type, "INTEGER") && strcmp((yyvsp[-3].a)->type, "FLOAT"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2243 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 283 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("RefRobotAxisAsync_stm",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2249 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 284 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("RefRobotAxisAsync_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a)); 
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2257 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 290 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("MoveRobotAxis_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-3].a)->content, "A1") && strcmp((yyvsp[-3].a)->content, "A2") && strcmp((yyvsp[-3].a)->content, "A3") && strcmp((yyvsp[-3].a)->content, "A4") && strcmp((yyvsp[-3].a)->content, "A5") && strcmp((yyvsp[-3].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "INTEGER") && strcmp((yyvsp[-1].a)->type, "FLOAT"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2267 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 295 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("MoveRobotAxis_stm",6,(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	if (strcmp((yyvsp[-3].a)->content, "A1") && strcmp((yyvsp[-3].a)->content, "A2") && strcmp((yyvsp[-3].a)->content, "A3") && strcmp((yyvsp[-3].a)->content, "A4") && strcmp((yyvsp[-3].a)->content, "A5") && strcmp((yyvsp[-3].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }}
#line 2275 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 298 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("MoveRobotAxis_stm",8,(yyvsp[-7].a),(yyvsp[-6].a),(yyvsp[-5].a),(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-3].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-5].a)->content, "A1") && strcmp((yyvsp[-5].a)->content, "A2") && strcmp((yyvsp[-5].a)->content, "A3") && strcmp((yyvsp[-5].a)->content, "A4") && strcmp((yyvsp[-5].a)->content, "A5") && strcmp((yyvsp[-5].a)->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-5].a)->content); flag = 1; }
	if (strcmp((yyvsp[-3].a)->type, "INTEGER") && strcmp((yyvsp[-3].a)->type, "FLOAT"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2287 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 308 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("Dyn_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-1].a)->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2295 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 314 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("Dynovr_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if ((strcmp((yyvsp[-1].a)->type, "INTEGER") && strcmp((yyvsp[-1].a)->type, "FLOAT")) || (!strcmp((yyvsp[-1].a)->type, "INTEGER") && (yyvsp[-1].a)->intgr < 0) || (!strcmp((yyvsp[-1].a)->type, "FLOAT") && (yyvsp[-1].a)->flt < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2303 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 317 "syntax.y" /* yacc.c:1646  */
    {  (yyval.a) = newAst("Dynovr_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2309 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 321 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Ramp_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	if (strcmp((yyvsp[-1].a)->content, "T") && strcmp((yyvsp[-1].a)->content, "S"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2317 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 327 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("RefSys_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-1].a)->type, "CARTREFSYS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2325 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 330 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("RefSys_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2331 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 334 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Tool_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if (strcmp((yyvsp[-1].a)->type, "CARTSYS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2339 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 340 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("WaitTime_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2345 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 341 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("WaitTime_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2351 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 342 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("WaitTime_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-1].a));
	if ((strcmp((yyvsp[-1].a)->type, "INTEGER") && strcmp((yyvsp[-1].a)->type, "FLOAT")) || (!strcmp((yyvsp[-1].a)->type, "INTEGER") && (yyvsp[-1].a)->intgr < 0) || (!strcmp((yyvsp[-1].a)->type, "FLOAT") && (yyvsp[-1].a)->flt < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2359 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 348 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Stop_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));
	if (strcmp((yyvsp[-1].a)->content, "HARDSTOP") && strcmp((yyvsp[-1].a)->content, "SOFTSTOP"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2367 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 354 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Notice_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	if (strcmp((yyvsp[-1].a)->type, "STRING"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2375 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 357 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Notice_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2381 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 361 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Warning_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	if (strcmp((yyvsp[-1].a)->type, "STRING"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2389 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 364 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Warning_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2395 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 368 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Error_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	if (strcmp((yyvsp[-1].a)->type, "STRING"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-1].a)->content); flag = 1; }}
#line 2403 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 371 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Error_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2409 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 375 "syntax.y" /* yacc.c:1646  */
    { isBool((yyvsp[0].a)); (yyval.a) = newAst("Condition",1,(yyvsp[0].a)); }
#line 2415 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 376 "syntax.y" /* yacc.c:1646  */
    { isBool((yyvsp[0].a)); (yyval.a) = newAst("Condition",1,(yyvsp[0].a)); }
#line 2421 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 380 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("CALL_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); 
	char *progFilePath = new char[projName.size() + strlen((yyvsp[-2].a)->content) + 40];
	sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", (yyvsp[-2].a)->content, ".prog");
	FILE *progFile = fopen(progFilePath, "r");
	delete[]progFilePath;
	if (!progFile)
	{ 
	  printf("The subprogram '%s' dose not exist.\n", (yyvsp[-2].a)->content); flag = 1;
	}
	else
	{
	  fclose(progFile);
      struct AST *tempRoot = rootHead->next;
	  queue<char*> tempVarProgQueue(varProgQueue);
	  bool firstCompile = true;
	  while (!tempVarProgQueue.empty())
	  {
	    char *varProg = tempVarProgQueue.front();
		tempVarProgQueue.pop();
		if (!strcmp(varProg, (yyvsp[-2].a)->content))
		{
		  firstCompile = false;
		  break;
		}
	  }
	  if (firstCompile)
	  {
		varProgQueue.push((yyvsp[-2].a)->content);
	  }}}
#line 2455 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 412 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("WAIT_stm",2,(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2461 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 416 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("IF_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2467 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 417 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("IF_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2473 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 418 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("IF_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2479 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 419 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("IF_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2485 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 420 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("IF_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2491 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 421 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("IF_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2497 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 425 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSEIF_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2503 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 426 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSEIF_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2509 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 427 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSEIF_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2515 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 428 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSEIF_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2521 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 429 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSEIF_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2527 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 430 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSEIF_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2533 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 434 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSE_stm",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2539 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 435 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ELSE_stm",2,(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2545 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 439 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("WHILE_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2551 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 440 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("WHILE_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2557 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 444 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("LOOP_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2563 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 445 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("LOOP_stm",5,(yyvsp[-4].a),(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-3].a));
	if (strcmp((yyvsp[-3].a)->type, "INTEGER") ||  (!strcmp((yyvsp[-3].a)->type, "INTEGER") && (yyvsp[-3].a)->intgr < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-3].a)->content); flag = 1; }}
#line 2571 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 448 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("LOOP_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2577 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 449 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("LOOP_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-2].a));
	if (strcmp((yyvsp[-2].a)->type, "INTEGER") ||  (!strcmp((yyvsp[-2].a)->type, "INTEGER") && (yyvsp[-2].a)->intgr < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, (yyvsp[-2].a)->content); flag = 1; }}
#line 2585 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 455 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("RUN_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));
	char *progFilePath = new char[projName.size() + strlen((yyvsp[-2].a)->content) + 40];
	sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", (yyvsp[-2].a)->content, ".prog");
	FILE *progFile = fopen(progFilePath, "r");
	delete[]progFilePath;
	if (!progFile)
	{ 
	  printf("The subprogram '%s' dose not exist.\n", (yyvsp[-2].a)->content); flag = 1;
	}
	else
	{ 
      fclose(progFile);
	  queue<char*> tempVarProgQueue(varProgQueue);
	  bool firstCompile = true;
	  while (!tempVarProgQueue.empty())
	  {
	    char *varProg = tempVarProgQueue.front();
		tempVarProgQueue.pop();
		if (!strcmp(varProg, (yyvsp[-2].a)->content))
		{
		  firstCompile = false;
		  break;
		}
	  }
	  if (firstCompile)
	  {
		varProgQueue.push((yyvsp[-2].a)->content);
	  }}}
#line 2618 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 486 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("KILL_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a));
	char *progFilePath = new char[projName.size() + strlen((yyvsp[-2].a)->content) + 40];
	sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", (yyvsp[-2].a)->content, ".prog");
	FILE *progFile = fopen(progFilePath, "r");
	delete[]progFilePath;
	if (!progFile)
	{ 
	  printf("The subprogram '%s' dose not exist.\n", (yyvsp[-2].a)->content); flag = 1;
	}
	else
	{
	  fclose(progFile);
	}}
#line 2636 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 502 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("RETURN_stm",1,(yyvsp[0].a)); }
#line 2642 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 506 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("GOTO_stm",2,(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2648 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 507 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("GOTO_stm",4,(yyvsp[-3].a),(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); }
#line 2654 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 511 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("LABEL_stm",2,(yyvsp[-1].a),(yyvsp[0].a)); newLabel((yyvsp[-1].a)); }
#line 2660 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 515 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("DOT_expr",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-2].a)); dot_var2ast((yyvsp[-2].a),(yyvsp[0].a),(yyval.a)); }
#line 2666 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 519 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ASSIGN_stm",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); existVar((yyvsp[-2].a)); assignment((yyvsp[-2].a),(yyvsp[0].a)); ast2ast((yyvsp[-2].a),(yyval.a)); ast2var((yyvsp[-2].a)); }
#line 2672 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 520 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("ASSIGN_stm",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); assignment((yyvsp[-2].a),(yyvsp[0].a)); ast2ast((yyvsp[-2].a),(yyval.a)); dot_ast2var((yyvsp[-2].a)->l,(yyvsp[-2].a)->l->r->r,(yyvsp[-2].a)); }
#line 2678 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 524 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); logical((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2684 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 525 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); logical((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2690 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 526 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); logical((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2696 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 527 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2702 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 528 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2708 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 529 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2714 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 530 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2720 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 531 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2726 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 532 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2732 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 533 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2738 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 534 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2744 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 535 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2750 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 536 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); arithmetic((yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a),(yyval.a)); }
#line 2756 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 537 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",2,(yyvsp[-1].a),(yyvsp[0].a)); minusOperator((yyvsp[0].a),(yyval.a)); }
#line 2762 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 538 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",2,(yyvsp[-1].a),(yyvsp[0].a)); notOperator((yyvsp[0].a),(yyval.a)); }
#line 2768 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 539 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); ast2ast((yyvsp[-1].a),(yyval.a)); }
#line 2774 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 540 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",3,(yyvsp[-2].a),(yyvsp[-1].a),(yyvsp[0].a)); ast2ast((yyvsp[-1].a),(yyval.a)); }
#line 2780 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 541 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",1,(yyvsp[0].a)); }
#line 2786 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 542 "syntax.y" /* yacc.c:1646  */
    { existVar((yyvsp[0].a)); (yyval.a) = newAst("Expression",1,(yyvsp[0].a)); }
#line 2792 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 543 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",1,(yyvsp[0].a)); }
#line 2798 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 544 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",1,(yyvsp[0].a)); }
#line 2804 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 545 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",1,(yyvsp[0].a)); }
#line 2810 "syntax.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 546 "syntax.y" /* yacc.c:1646  */
    { (yyval.a) = newAst("Expression",1,(yyvsp[0].a)); }
#line 2816 "syntax.cpp" /* yacc.c:1646  */
    break;


#line 2820 "syntax.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 548 "syntax.y" /* yacc.c:1906  */
