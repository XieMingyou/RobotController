/*Function:词法分析模块，对每个终结符建立一个叶子结点，返回记号，供bison语法分析使用*/
%{
#include "io.h"
#include "stdio.h"
#include "stdlib.h"
#include "syntax.h"
#include "semantics.h"
%}
%option yylineno noyywrap 
COMMENT     (\/\/.*\n)|(\/\*[\s\S]*\*\/)
str         \"[^"]+\"
SPACE       [ \f\n\r\t\v]+
GAP         [ \f\n\r\t\v]*
bl          TRUE|FALSE|true|false
TYPE        INTEGER|FLOAT|STRING|BOOL|AXISPOS|CARTPOS|CARTREFSYS|TOOL|DYNAMIC
a1          \({GAP}a1{GAP}\=
a2          \,{GAP}a2{GAP}\=
a3          \,{GAP}a3{GAP}\=
a4          \,{GAP}a4{GAP}\=
a5          \,{GAP}a5{GAP}\=
a6          \,{GAP}a6{GAP}\=
aux1        \,{GAP}aux1{GAP}\=
aux2        \,{GAP}aux2{GAP}\=
aux3        \,{GAP}aux3{GAP}\=
aux4        \,{GAP}aux4{GAP}\=
aux5        \,{GAP}aux5{GAP}\=
x           ((\,)|(\()){GAP}x{GAP}\=
y           \,{GAP}y{GAP}\=
z           \,{GAP}z{GAP}\=
a           \,{GAP}a{GAP}\=
b           \,{GAP}b{GAP}\=
c           \,{GAP}c{GAP}\=
mode        \,{GAP}mode{GAP}\=
baseRefSys  \({GAP}baseRefSys{GAP}\=
velAxis     \({GAP}velAxis{GAP}\=
accAxis     \,{GAP}accAxis{GAP}\=
decAxis     \,{GAP}decAxis{GAP}\=
jerkAxis    \,{GAP}jerkAxis{GAP}\=
velPath     \,{GAP}velPath{GAP}\=
accPath     \,{GAP}accPath{GAP}\=
decPath     \,{GAP}decPath{GAP}\=
jerkPath    \,{GAP}jerkPath{GAP}\=
velOri      \,{GAP}velOri{GAP}\=
accOri      \,{GAP}accOri{GAP}\=
decOri      \,{GAP}decOri{GAP}\=
jerkOri     \,{GAP}jerkOri{GAP}\=
World        World
PTP         PTP
Lin         Lin
Circ        Circ
PTPRel      PTPRel
LinRel      LinRel
StopRobot   StopRobot
RefRobotAxis       RefRobotAxis
RefRobotAxisAsync  RefRobotAxisAsync
MoveRobotAxis      MoveRobotAxis
Dyn         Dyn
Dynovr      Dynovr
Ramp        Ramp
Refsys      Refsys
Tool        Tool
WaitTime    WaitTime
Stop        Stop
Notice      Notice
Warning     Warning
Error       Error
CALL        CALL
WAIT        WAIT
IF          IF
THEN        THEN
ELSE        ELSE
ELSEIF      ELSEIF
END_IF      END_IF
WHILE       WHILE
DO          DO
END_WHILE   END_WHILE
LOOP        LOOP
END_LOOP    END_LOOP
RUN         RUN
KILL        KILL
RETURN      RETURN
GOTO        GOTO
intgr       ([1-9]+[0-9]*)|0
flt         [0-9]+\.[0-9]*
id          [a-z_A-Z][a-zA-Z_0-9]*
ASSIGN      \=
MINUS       \-
LP          \(
RP          \)
LC          \{
RC          \}
COMMA       \,
COLON       \:
AND         \&\&
OR          \|\|
XOR         \^
MUL         \*
DIV         \/
PLUS        \+
EQ          \=\=
NE          \!\=
LE          \<\=
LT          \<
GE          \>\=
GT          \>
NOT         \!
DOT         \.
ERROR       .
%%
{COMMENT}     {}
{str}         { yylval.a = newAst("str", 0, yylineno); return str; }
{bl}          { yylval.a = newAst("bl", 0, yylineno); return bl; }
{TYPE}        { yylval.a = newAst("TYPE", 0, yylineno); return TYPE; }
{a1}          { yylval.a = newAst("a1", 0, yylineno); return a1; }
{a2}          { yylval.a = newAst("a2", 0, yylineno); return a2; }
{a3}          { yylval.a = newAst("a3", 0, yylineno); return a3; }
{a4}          { yylval.a = newAst("a4", 0, yylineno); return a4; }
{a5}          { yylval.a = newAst("a5", 0, yylineno); return a5; }
{a6}          { yylval.a = newAst("a6", 0, yylineno); return a6; }
{aux1}        { yylval.a = newAst("aux1", 0, yylineno); return aux1; }
{aux2}        { yylval.a = newAst("aux2", 0, yylineno); return aux2; }
{aux3}        { yylval.a = newAst("aux3", 0, yylineno); return aux3; }
{aux4}        { yylval.a = newAst("aux4", 0, yylineno); return aux4; }
{aux5}        { yylval.a = newAst("aux5", 0, yylineno); return aux5; }
{x}           { yylval.a = newAst("x", 0, yylineno); return x; }
{y}           { yylval.a = newAst("y", 0, yylineno); return y; }
{z}           { yylval.a = newAst("z", 0, yylineno); return z; }
{a}           { yylval.a = newAst("a", 0, yylineno); return a; }
{b}           { yylval.a = newAst("b", 0, yylineno); return b; }
{c}           { yylval.a = newAst("c", 0, yylineno); return c; }
{mode}        { yylval.a = newAst("mode", 0, yylineno); return mode; }
{baseRefSys}  { yylval.a = newAst("baseRefSys", 0, yylineno); return baseRefSys; }
{velAxis}     { yylval.a = newAst("velAxis", 0, yylineno); return velAxis; }
{accAxis}     { yylval.a = newAst("accAxis", 0, yylineno); return accAxis; }
{decAxis}     { yylval.a = newAst("decAxis", 0, yylineno); return decAxis; }
{jerkAxis}    { yylval.a = newAst("jerkAxis", 0, yylineno); return jerkAxis; }
{velPath}     { yylval.a = newAst("velPath", 0, yylineno); return velPath; }
{accPath}     { yylval.a = newAst("accPath", 0, yylineno); return accPath; }
{decPath}     { yylval.a = newAst("decPath", 0, yylineno); return decPath; }
{jerkPath}    { yylval.a = newAst("jerkPath", 0, yylineno); return jerkPath; }
{velOri}      { yylval.a = newAst("velOri", 0, yylineno); return velOri; }
{accOri}      { yylval.a = newAst("accOri", 0, yylineno); return accOri; }
{decOri}      { yylval.a = newAst("decOri", 0, yylineno); return decOri; }
{jerkOri}     { yylval.a = newAst("jerkOri", 0, yylineno); return jerkOri; }
{World}       { yylval.a = newAst("World", 0, yylineno); return World; }
{SPACE}       {}
{PTP}         { yylval.a = newAst("PTP", 0, yylineno); return PTP; }
{Lin}         { yylval.a = newAst("LIN", 0, yylineno); return Lin; }
{Circ}        { yylval.a = newAst("CIRC", 0, yylineno); return Circ; }
{PTPRel}      { yylval.a = newAst("PTPRel", 0, yylineno); return PTPRel; }
{LinRel}      { yylval.a = newAst("LinRel", 0, yylineno); return LinRel; }
{StopRobot}   { yylval.a = newAst("StopRobot", 0, yylineno); return StopRobot; }
{RefRobotAxis}        { yylval.a = newAst("RefRobotAxis", 0, yylineno); return RefRobotAxis; }
{RefRobotAxisAsync}   { yylval.a = newAst("RefRobotAxisAsync", 0, yylineno); return RefRobotAxisAsync; }
{MoveRobotAxis}       { yylval.a = newAst("MoveRobotAxis", 0, yylineno); return MoveRobotAxis; }
{Dyn}         { yylval.a = newAst("Dyn", 0, yylineno); return Dyn; }
{Dynovr}      { yylval.a = newAst("Dynovr", 0, yylineno); return Dynovr; }
{Ramp}        { yylval.a = newAst("Ramp", 0, yylineno); return Ramp; }
{Refsys}      { yylval.a = newAst("Refsys", 0, yylineno); return Refsys; }
{Tool}        { yylval.a = newAst("Tool", 0, yylineno); return Tool; }
{WaitTime}    { yylval.a = newAst("WaitTime", 0, yylineno); return WaitTime; }
{Stop}        { yylval.a = newAst("Stop", 0, yylineno); return Stop; }
{Notice}      { yylval.a = newAst("Notice", 0, yylineno); return Notice; }
{Warning}     { yylval.a = newAst("Warning", 0, yylineno); return Warning; }
{Error}       { yylval.a = newAst("Error", 0, yylineno); return Error; }
{CALL}        { yylval.a = newAst("CALL", 0, yylineno); return CALL; }
{WAIT}        { yylval.a = newAst("WAIT", 0, yylineno); return WAIT; }
{IF}          { yylval.a = newAst("IF", 0, yylineno); return IF; }
{THEN}        { yylval.a = newAst("THEN", 0, yylineno); return THEN; }
{ELSE}        { yylval.a = newAst("ELSE", 0, yylineno); return ELSE; }
{ELSEIF}      { yylval.a = newAst("ELSEIF", 0, yylineno); return ELSEIF; }
{END_IF}      { yylval.a = newAst("END_IF", 0, yylineno); return END_IF; }
{WHILE}       { yylval.a = newAst("WHILE", 0, yylineno); return WHILE; }
{DO}          { yylval.a = newAst("DO", 0, yylineno); return DO; }
{END_WHILE}   { yylval.a = newAst("END_WHILE", 0, yylineno); return END_WHILE; }
{LOOP}        { yylval.a = newAst("LOOP", 0, yylineno); return LOOP; }
{END_LOOP}    { yylval.a = newAst("END_LOOP", 0, yylineno); return END_LOOP; }
{RUN}         { yylval.a = newAst("RUN", 0, yylineno); return RUN; }
{KILL}        { yylval.a = newAst("KILL", 0, yylineno); return KILL; }
{RETURN}      { yylval.a = newAst("RETURN", 0, yylineno); return RETURN; }
{GOTO}        { yylval.a = newAst("GOTO", 0, yylineno); return GOTO; }
{intgr}       { yylval.a = newAst("intgr", 0, yylineno); return intgr; }
{flt}         { yylval.a = newAst("flt", 0, yylineno); return flt; }
{id}          { yylval.a = newAst("id", 0, yylineno); return id; }
{ASSIGN}      { yylval.a = newAst("ASSIGN", 0, yylineno); return ASSIGN; }
{MINUS}       { yylval.a = newAst("MINUS", 0, yylineno); return MINUS; }
{LP}          { yylval.a = newAst("LP", 0, yylineno); return LP; }
{RP}          { yylval.a = newAst("RP", 0, yylineno); return RP; }
{LC}          { yylval.a = newAst("LC", 0, yylineno); return LC; }
{RC}          { yylval.a = newAst("RC", 0, yylineno); return RC; }
{COMMA}       { yylval.a = newAst("COMMA", 0, yylineno); return COMMA; }
{COLON}       { yylval.a = newAst("COLON", 0, yylineno); return COLON; }
{AND}         { yylval.a = newAst("AND", 0, yylineno); return AND; }
{OR}          { yylval.a = newAst("OR", 0, yylineno); return OR; }
{XOR}         { yylval.a = newAst("XOR", 0, yylineno); return XOR; }
{MUL}         { yylval.a = newAst("MUL", 0, yylineno); return MUL; }
{DIV}         { yylval.a = newAst("DIV", 0, yylineno); return DIV; }
{PLUS}        { yylval.a = newAst("PLUS", 0, yylineno); return PLUS; }
{EQ}          { yylval.a = newAst("EQ", 0, yylineno); return EQ; }
{NE}          { yylval.a = newAst("NE", 0, yylineno); return NE; }
{LE}          { yylval.a = newAst("LE", 0, yylineno); return LE; }
{LT}          { yylval.a = newAst("LT", 0, yylineno); return LT; }
{GE}          { yylval.a = newAst("GE", 0, yylineno); return GE; }
{GT}          { yylval.a = newAst("GT", 0, yylineno); return GT; }
{NOT}         { yylval.a = newAst("NOT", 0, yylineno); return NOT; }
{DOT}         { yylval.a = newAst("DOT", 0, yylineno); return DOT; }
{ERROR}       { printf("Error type at line %d: Mystirious charachter '%s'\n", yylineno, yytext); }
%%