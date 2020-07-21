/*Function:语法分析模块*/
%{
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "lexicon.h"
#include "semantics.h"//符号表和抽象语义树创建
%}
%union {
	struct AST *a;
}

/*declare tokens*/
%token <a> SPACE COMMENT str bl TYPE a1 a2 a3 a4 a5 a6 aux1 aux2 aux3 aux4 aux5 x y z a b c mode baseRefSys velAxis accAxis decAxis jerkAxis velPath accPath decPath jerkPath velOri accOri decOri jerkOri World
%token <a> PTP Lin Circ PTPRel LinRel StopRobot RefRobotAxis RefRobotAxisAsync MoveRobotAxis
%token <a> Dyn Dynovr Ramp Refsys Tool
%token <a> WaitTime Stop Notice Warning Error
%token <a> CALL WAIT IF THEN ELSE ELSEIF END_IF WHILE DO END_WHILE  LOOP END_LOOP RUN KILL RETURN GOTO
%token <a> intgr flt id ASSIGN MINUS LP RP LC RC COMMA COLON AND OR XOR MUL DIV PLUS EQ NE LE LT GE GT NOT DOT ERROR
%type  <a> Var_Prog 
%type  <a> Var DefinitionList Definition type real axisPos cartPos robAxisPos robCartPos auxAxisPos cartSys cartRefSys dynamic
%type  <a> Prog StatementList Statement 
%type  <a> PTP_stm Lin_stm Circ_stm PTPRel_stm LinRel_stm StopRobot_stm RefRobotAxis_stm RefRobotAxisAsync_stm MoveRobotAxis_stm
%type  <a> Dyn_stm Dynovr_stm Ramp_stm Refsys_stm Tool_stm
%type  <a> WaitTime_stm Stop_stm Notice_stm Warning_stm Error_stm
%type  <a> CALL_stm WAIT_stm Condition IF_stm ELSEIF_stm ELSE_stm WHILE_stm LOOP_stm RUN_stm KILL_stm RETURN_stm GOTO_stm LABEL_stm
%type  <a> DOT_expr ASSIGN_stm Expression

/*priority*/
%right ASSIGN
%left OR
%left AND 
%left XOR
%left EQ NE LE LT GE GT
%left PLUS MINUS
%left MUL DIV
%left UMINUS
%right NOT
%left LP RP DOT
%left LC RC
%%

/*共有部分*/
Var_Prog:
	Var Prog { $$ = newAst("Var_Prog",2,$1,$2); $$->varProgName = curVarProg; rootTail->next = $$; rootTail = $$; setThisRoot($$); 
	printf("打印syntax tree:\n"); traverse($$,1); printf("syntax tree打印完毕!\n"); }
	;

/*数据文件*/
Var:
	LC DefinitionList RC { $$ = newAst("Var",3,$1,$2,$3); }
	| LC RC { $$ = newAst("Var",2,$1,$2); }
	;


DefinitionList:
	Definition DefinitionList { $$ = newAst("DefinitionList",2,$1,$2); }
	| Definition {$$ = newAst("DefinitionList",1, $1); }
	;

Definition:
	id COLON TYPE ASSIGN type { $$ = newAst("Definition",5,$1,$2,$3,$4,$5); defTypeError($3, $5); newVar($1,$5); 
	if ((!strcmp($1->content, "x")) || (!strcmp($1->content, "a1")) || (!strcmp($1->content, "baseRefSys")) || (!strcmp($1->content, "velAxis")) || (!strcmp($1->content, "World")))
	{ printf("Error at Line %d: The content of the variable can not be 'x' or 'a1' or 'baseRefSys' or 'velAxis' or 'World'. Please delete variable '%s'.\n", yylineno, $1->content); flag = 1; }}
	;

type:
	id { existVar($1); $$ = newAst("type",1,$1); }
	| intgr { $$ = newAst("type",1,$1); }
	| flt { $$ = newAst("type",1,$1); }
	| MINUS intgr { $$ = newAst("type",2,$1,$2); $$->type = "INTEGER"; $$->intgr = -($2->intgr); }
	| MINUS flt { $$ = newAst("type",2,$1,$2); $$->type = "FLOAT"; $$->flt = -($2->flt); }
	| str { $$ = newAst("type",1,$1); }
	| bl { $$ = newAst("type",1,$1); }
	| axisPos{ $$ = newAst("type",1,$1); }
	| cartPos { $$ = newAst("type",1,$1); }
	| cartSys { $$ = newAst("type",1,$1); }
	| cartRefSys { $$ = newAst("type",1,$1); $$->cartSys = $1->cartSys;}
	| dynamic { $$ = newAst("type",1,$1); }

real:
	intgr { $$ = newAst("real",1,$1); $$->type = "FLOAT"; $$->flt = $1->intgr; }
	| flt { $$ = newAst("real",1,$1); $$->type = "FLOAT"; $$->flt = $1->flt; }
	| MINUS intgr { $$ = newAst("real",2,$1,$2); $$->type = "FLOAT"; $$->flt = -($2->intgr); }
	| MINUS flt { $$ = newAst("real",2,$1,$2); $$->type = "FLOAT"; $$->flt = -($2->flt); }
	

axisPos:
	robAxisPos RP{ $$ = newAst("axisPos",2,$1,$2); $$->type = "AXISPOS"; $$->axisPos = $1->axisPos; }
	| robAxisPos auxAxisPos RP { $$ = newAst("axisPos",3,$1,$2,$3); 
	$$->type = "AXISPOS"; $$->axisPos = $1->axisPos; 
	$$->axisPos.aux1 = $2->auxAxisPos.aux1; $$->axisPos.aux2 = $2->auxAxisPos.aux2; $$->axisPos.aux3 = $2->auxAxisPos.aux3; $$->axisPos.aux4 = $2->auxAxisPos.aux4; $$->axisPos.aux5 = $2->auxAxisPos.aux5; }
	;

cartPos:
	robCartPos RP{ $$ = newAst("cartPos",2,$1,$2); $$->type = "CARTPOS"; $$->cartPos = $1->cartPos; }
	| robCartPos auxAxisPos RP{ $$ = newAst("cartPos",3,$1,$2,$3); 
	$$->type = "CARTPOS"; $$->cartPos = $1->cartPos;
	$$->cartPos.aux1 = $2->auxAxisPos.aux1; $$->cartPos.aux2 = $2->auxAxisPos.aux2; $$->cartPos.aux3 = $2->auxAxisPos.aux3; $$->cartPos.aux4 = $2->auxAxisPos.aux4; $$->cartPos.aux5 = $2->auxAxisPos.aux5; }
	;

robAxisPos:
	a1 real a2 real a3 real a4 real a5 real a6 real { $$ = newAst("robAxisPos",12,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12); 
	$$->axisPos.a1 = $2->flt; $$->axisPos.a2 = $4->flt; $$->axisPos.a3 = $6->flt; $$->axisPos.a4 = $8->flt; $$->axisPos.a5 = $10->flt; $$->axisPos.a6 = $12->flt; }
	;

robCartPos:
	x real y real z real a real b real c real mode intgr { $$ = newAst("robCartPos",14,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14); 
	$$->cartPos.x = $2->flt; $$->cartPos.y = $4->flt; $$->cartPos.z = $6->flt; $$->cartPos.a = $8->flt; $$->cartPos.b = $10->flt; $$->cartPos.c = $12->flt; $$->cartPos.mode = $14->intgr; }

auxAxisPos:
	aux1 real { $$ = newAst("auxAxisPos",2,$1,$2); $$->auxAxisPos.aux1 = $2->flt; }
	| aux1 real aux2 real { $$ = newAst("auxAxisPos",4,$1,$2,$3,$4); $$->auxAxisPos.aux1 = $2->flt; $$->auxAxisPos.aux2 = $4->flt; }
	| aux1 real aux2 real aux3 real { $$ = newAst("auxAxisPos",6,$1,$2,$3,$4,$5,$6); $$->auxAxisPos.aux1 = $2->flt; $$->auxAxisPos.aux2 = $4->flt; $$->auxAxisPos.aux3 = $6->flt; }
	| aux1 real aux2 real aux3 real aux4 real { $$ = newAst("auxAxisPos",8,$1,$2,$3,$4,$5,$6,$7,$8); $$->auxAxisPos.aux1 = $2->flt; $$->auxAxisPos.aux2 = $4->flt; $$->auxAxisPos.aux3 = $6->flt; $$->auxAxisPos.aux4 = $8->flt; }
	| aux1 real aux2 real aux3 real aux4 real aux5 real { $$ = newAst("auxAxisPos",10,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10); $$->auxAxisPos.aux1 = $2->flt; $$->auxAxisPos.aux2 = $4->flt; $$->auxAxisPos.aux3 = $6->flt; $$->auxAxisPos.aux4 = $8->flt; $$->auxAxisPos.aux5 = $10->flt;}

cartSys:
	x real y real z real a real b real c real RP { $$ = newAst("cartSys",13,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13);
	$$->type = "CARTSYS"; 
	$$->cartSys.x = $2->flt; $$->cartSys.y = $4->flt; $$->cartSys.z = $6->flt; $$->cartSys.a = $8->flt; $$->cartSys.b = $10->flt; $$->cartSys.c = $12->flt; }
	;

cartRefSys:
	baseRefSys World x real y real z real a real b real c real RP { $$ = newAst("cartRefSys",15,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15);
	$$->type = "CARTREFSYS";
	$$->cartRefSys.baseRefSys = $2->content; $$->cartRefSys.x = $4->flt; $$->cartRefSys.y = $6->flt; $$->cartRefSys.z = $8->flt; $$->cartRefSys.a = $10->flt; $$->cartRefSys.b = $12->flt; $$->cartRefSys.c = $14->flt; 
	$$->cartSys.x = $4->flt; $$->cartSys.y = $6->flt; $$->cartSys.z = $8->flt; $$->cartSys.a = $10->flt; $$->cartSys.b = $12->flt; $$->cartSys.c = $14->flt; }
	| baseRefSys id x real y real z real a real b real c real RP { $$ = newAst("cartRefSys",15,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15); existVar($2); var2ast($2);
	$$->type = "CARTREFSYS";
	if (strcmp($2->type, "CARTREFSYS"))
	{ printf("Error at Line %d: The type of '%s' is not 'CARTREFSYS'.\n", yylineno, $2->content); flag = 1;}
	$$->cartRefSys.baseRefSys = $2->content; $$->cartRefSys.x = $4->flt; $$->cartRefSys.y = $6->flt; $$->cartRefSys.z = $8->flt; $$->cartRefSys.a = $10->flt; $$->cartRefSys.b = $12->flt; $$->cartRefSys.c = $14->flt; 
	$$->cartSys.x = $4->flt; $$->cartSys.y = $6->flt; $$->cartSys.z = $8->flt; $$->cartSys.a = $10->flt; $$->cartSys.b = $12->flt; $$->cartSys.c = $14->flt;
	calculateCartSys($$, $2); }
	;

dynamic:
	velAxis real accAxis real decAxis real jerkAxis real velPath real accPath real decPath real jerkPath real velOri real accOri real decOri real jerkOri real RP { $$ = newAst("dynamic",25,$1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21,$22,$23,$24,$25); 
	$$->type = "DYNAMIC";
	$$->dynamic.velAxis = $2->flt; $$->dynamic.accAxis = $4->flt; $$->dynamic.decAxis = $6->flt; $$->dynamic.jerkAxis = $8->flt; $$->dynamic.velPath = $10->flt; $$->dynamic.accPath = $12->flt; 
	$$->dynamic.decPath = $14->flt; $$->dynamic.jerkPath = $16->flt; $$->dynamic.velOri = $18->flt; $$->dynamic.accOri = $20->flt; $$->dynamic.decOri = $22->flt; $$->dynamic.jerkOri = $24->flt; }
	;

/*程序文件*/
Prog:
	LC StatementList RC { $$ = newAst("Prog",3,$1,$2,$3); }
	| LC RC { $$ = newAst("Prog",2,$1,$2); }
	;

StatementList: 
	Statement StatementList { $$ = newAst("StatementList",2,$1,$2); }
	| Statement { $$ = newAst("StatementList",1,$1); }
	;

Statement:
	PTP_stm { $$ = newAst("Statement",1,$1); }
	| Lin_stm { $$ = newAst("Statement",1,$1); }
	| Circ_stm { $$ = newAst("Statement",1,$1); }
	| PTPRel_stm { $$ = newAst("Statement",1,$1); }
	| LinRel_stm { $$ = newAst("Statement",1,$1); }
	| StopRobot_stm { $$ = newAst("Statement",1,$1); }
	| RefRobotAxis_stm { $$ = newAst("Statement",1,$1); }
	| RefRobotAxisAsync_stm { $$ = newAst("Statement",1,$1); }
	| MoveRobotAxis_stm { $$ = newAst("Statement",1,$1); }
	| Dyn_stm { $$ = newAst("Statement",1,$1); }
	| Dynovr_stm { $$ = newAst("Statement",1,$1); }
	| Ramp_stm { $$ = newAst("Statement",1,$1); }
	| Refsys_stm { $$ = newAst("Statement",1,$1); }
	| Tool_stm { $$ = newAst("Statement",1,$1); }
	| WaitTime_stm { $$ = newAst("Statement",1,$1); }
	| Stop_stm { $$ = newAst("Statement",1,$1); }
	| Notice_stm { $$ = newAst("Statement",1,$1); }
	| Warning_stm { $$ = newAst("Statement",1,$1); }
	| Error_stm { $$ = newAst("Statement",1,$1); }
	| CALL_stm { $$ = newAst("Statement",1,$1); }
	| WAIT_stm { $$ = newAst("Statement",1,$1); }
	| IF_stm { $$ = newAst("Statement",1,$1); }
	| WHILE_stm { $$ = newAst("Statement",1,$1); }
	| LOOP_stm { $$ = newAst("Statement",1,$1); }
	| RUN_stm { $$ = newAst("Statement",1,$1); }
	| KILL_stm { $$ = newAst("Statement",1,$1); }
	| RETURN_stm { $$ = newAst("Statement",1,$1); }
	| GOTO_stm { $$ = newAst("Statement",1,$1); }
	| LABEL_stm { $$ = newAst("Statement",1,$1); }
	| ASSIGN_stm { $$ = newAst("Statement",1,$1); }
	;

PTP_stm:
	PTP LP id RP { $$ = newAst("PTP_stm",4,$1,$2,$3,$4); existVar($3); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}

	| PTP LP id COMMA id RP { $$ = newAst("PTP_stm",6,$1,$2,$3,$4,$5,$6); existVar($3); existVar($5); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }}
	;

Lin_stm:
	Lin LP id RP { $$ = newAst("Lin_stm",4,$1,$2,$3,$4); existVar($3);
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}

	| Lin LP id COMMA id RP { $$ = newAst("Lin_stm",6,$1,$2,$3,$4,$5,$6);  existVar($3); existVar($5); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }}
	;

Circ_stm:
	Circ LP id COMMA id RP { $$ = newAst("Circ_stm",6,$1,$2,$3,$4,$5,$6);  existVar($3); existVar($5); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "AXISPOS") && strcmp($5->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }}

	| Circ LP id COMMA id COMMA id RP { $$ = newAst("Circ_stm",8,$1,$2,$3,$4,$5,$6,$7,$8);  existVar($3); existVar($5); existVar($7); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "AXISPOS") && strcmp($5->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }
	if (strcmp($7->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $7->content); flag = 1; }}
	;

PTPRel_stm:
	PTPRel LP id RP { $$ = newAst("PTPRel_stm",4,$1,$2,$3,$4); existVar($3); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| PTPRel LP id COMMA id RP { $$ = newAst("PTPRel_stm",6,$1,$2,$3,$4,$5,$6); existVar($3); existVar($5); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }}
	;

LinRel_stm:
	LinRel LP id RP { $$ = newAst("LinRel_stm",4,$1,$2,$3,$4); existVar($3); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| LinRel LP id COMMA id RP { $$ = newAst("LinRel_stm",6,$1,$2,$3,$4,$5,$6); existVar($3); existVar($5); 
	if (strcmp($3->type, "AXISPOS") && strcmp($3->type, "CARTPOS")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }}
	;

StopRobot_stm:
	StopRobot LP id RP { $$ = newAst("StopRobot_stm",4,$1,$2,$3,$4);
	if (strcmp($3->content, "HARDSTOP") && strcmp($3->content, "SOFTSTOP"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	;

RefRobotAxis_stm:
	RefRobotAxis LP id RP {  $$ = newAst("RefRobotAxis_stm",4,$1,$2,$3,$4); 
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| RefRobotAxis LP id COMMA real RP {  $$ = newAst("RefRobotAxis_stm",6,$1,$2,$3,$4,$5,$6);
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| RefRobotAxis LP id COMMA id RP {  $$ = newAst("RefRobotAxis_stm",6,$1,$2,$3,$4,$5,$6); existVar($5);
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "INTEGER") && strcmp($5->type, "FLOAT") && strcmp($5->type, "DYNAMIC")) 
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }}
	| RefRobotAxis LP id COMMA real COMMA id RP {  $$ = newAst("RefRobotAxis_stm",8,$1,$2,$3,$4,$5,$6,$7,$8); existVar($7);
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($7->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $7->content); flag = 1; }}
	| RefRobotAxis LP id COMMA id COMMA id RP {  $$ = newAst("RefRobotAxis_stm",8,$1,$2,$3,$4,$5,$6,$7,$8); existVar($5); existVar($7);
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "INTEGER") && strcmp($5->type, "FLOAT"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }
	if (strcmp($7->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $7->content); flag = 1; }} 
	;

RefRobotAxisAsync_stm:
	RefRobotAxisAsync LP RP {  $$ = newAst("RefRobotAxisAsync_stm",3,$1,$2,$3); }
	| RefRobotAxisAsync LP id RP {  $$ = newAst("RefRobotAxisAsync_stm",4,$1,$2,$3,$4); existVar($3); 
	if (strcmp($3->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	;

MoveRobotAxis_stm:
	MoveRobotAxis LP id COMMA id RP {  $$ = newAst("MoveRobotAxis_stm",6,$1,$2,$3,$4,$5,$6); existVar($5);
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "INTEGER") && strcmp($5->type, "FLOAT"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }}
	| MoveRobotAxis LP id COMMA real RP {  $$ = newAst("MoveRobotAxis_stm",6,$1,$2,$3,$4,$5,$6); 
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| MoveRobotAxis LP id COMMA id COMMA id RP {  $$ = newAst("MoveRobotAxis_stm",8,$1,$2,$3,$4,$5,$6,$7,$8); existVar($5); existVar($7);
	if (strcmp($3->content, "A1") && strcmp($3->content, "A2") && strcmp($3->content, "A3") && strcmp($3->content, "A4") && strcmp($3->content, "A5") && strcmp($3->content, "A6"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }
	if (strcmp($5->type, "INTEGER") && strcmp($5->type, "FLOAT"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $5->content); flag = 1; }
	if (strcmp($7->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $7->content); flag = 1; }}
	;

Dyn_stm:
	Dyn LP id RP {  $$ = newAst("Dyn_stm",4,$1,$2,$3,$4); existVar($3);
	if (strcmp($3->type, "DYNAMIC"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	;

Dynovr_stm:
	Dynovr LP id RP {  $$ = newAst("Dynovr_stm",4,$1,$2,$3,$4); existVar($3);
	if ((strcmp($3->type, "INTEGER") && strcmp($3->type, "FLOAT")) || (!strcmp($3->type, "INTEGER") && $3->intgr < 0) || (!strcmp($3->type, "FLOAT") && $3->flt < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| Dynovr LP real RP {  $$ = newAst("Dynovr_stm",4,$1,$2,$3,$4); }
	;

Ramp_stm:
	Ramp LP id RP { $$ = newAst("Ramp_stm",4,$1,$2,$3,$4); 
	if (strcmp($3->content, "T") && strcmp($3->content, "S"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	;

Refsys_stm:
	Refsys LP id RP { $$ = newAst("RefSys_stm",4,$1,$2,$3,$4); existVar($3);
	if (strcmp($3->type, "CARTREFSYS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| Refsys LP World RP { $$ = newAst("RefSys_stm",4,$1,$2,$3,$4); }
	;

Tool_stm:
	Tool LP id RP { $$ = newAst("Tool_stm",4,$1,$2,$3,$4); existVar($3);
	if (strcmp($3->type, "CARTSYS"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	;

WaitTime_stm:
	WaitTime LP intgr RP { $$ = newAst("WaitTime_stm",4,$1,$2,$3,$4); }
	| WaitTime LP flt RP { $$ = newAst("WaitTime_stm",4,$1,$2,$3,$4); }
	| WaitTime LP id RP { $$ = newAst("WaitTime_stm",4,$1,$2,$3,$4); existVar($3);
	if ((strcmp($3->type, "INTEGER") && strcmp($3->type, "FLOAT")) || (!strcmp($3->type, "INTEGER") && $3->intgr < 0) || (!strcmp($3->type, "FLOAT") && $3->flt < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	;

Stop_stm:
	Stop LP id RP { $$ = newAst("Stop_stm",4,$1,$2,$3,$4);
	if (strcmp($3->content, "HARDSTOP") && strcmp($3->content, "SOFTSTOP"))
	{ printf("Error at Line %d: The statement has no parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	;

Notice_stm:
	Notice LP id RP { $$ = newAst("Notice_stm",4,$1,$2,$3,$4); 
	if (strcmp($3->type, "STRING"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| Notice LP str RP { $$ = newAst("Notice_stm",4,$1,$2,$3,$4); }
	;

Warning_stm:
	Warning LP id RP { $$ = newAst("Warning_stm",4,$1,$2,$3,$4); 
	if (strcmp($3->type, "STRING"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| Warning LP str RP { $$ = newAst("Warning_stm",4,$1,$2,$3,$4); }
	;

Error_stm:
	Error LP id RP { $$ = newAst("Error_stm",4,$1,$2,$3,$4); 
	if (strcmp($3->type, "STRING"))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $3->content); flag = 1; }}
	| Error LP str RP { $$ = newAst("Error_stm",4,$1,$2,$3,$4); }
	;

Condition:
	Expression { isBool($1); $$ = newAst("Condition",1,$1); }
	| ASSIGN_stm { isBool($1); $$ = newAst("Condition",1,$1); }
	;

CALL_stm:
	CALL id LP RP { $$ = newAst("CALL_stm",4,$1,$2,$3,$4); 
	char *progFilePath = new char[projName.size() + strlen($2->content) + 40];
	sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", $2->content, ".prog");
	FILE *progFile = fopen(progFilePath, "r");
	delete[]progFilePath;
	if (!progFile)
	{ 
	  printf("The subprogram '%s' dose not exist.\n", $2->content); flag = 1;
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
		if (!strcmp(varProg, $2->content))
		{
		  firstCompile = false;
		  break;
		}
	  }
	  if (firstCompile)
	  {
		varProgQueue.push($2->content);
	  }}}
	;

WAIT_stm:
	WAIT Condition { $$ = newAst("WAIT_stm",2,$1,$2); }
	;

IF_stm:
	IF Condition THEN StatementList ELSEIF_stm { $$ = newAst("IF_stm",5,$1,$2,$3,$4,$5); }
	| IF Condition THEN StatementList ELSE_stm { $$ = newAst("IF_stm",5,$1,$2,$3,$4,$5); }
	| IF Condition THEN StatementList END_IF { $$ = newAst("IF_stm",5,$1,$2,$3,$4,$5); }
	| IF Condition THEN ELSEIF_stm { $$ = newAst("IF_stm",4,$1,$2,$3,$4); }
	| IF Condition THEN ELSE_stm { $$ = newAst("IF_stm",4,$1,$2,$3,$4); }
	| IF Condition THEN END_IF { $$ = newAst("IF_stm",4,$1,$2,$3,$4); }
	;

ELSEIF_stm:
	ELSEIF Condition THEN StatementList ELSEIF_stm { $$ = newAst("ELSEIF_stm",5,$1,$2,$3,$4,$5); }
	| ELSEIF Condition THEN StatementList ELSE_stm { $$ = newAst("ELSEIF_stm",5,$1,$2,$3,$4,$5); }
	| ELSEIF Condition THEN StatementList END_IF { $$ = newAst("ELSEIF_stm",5,$1,$2,$3,$4,$5); }
	| ELSEIF Condition THEN ELSEIF_stm { $$ = newAst("ELSEIF_stm",4,$1,$2,$3,$4); }
	| ELSEIF Condition THEN ELSE_stm { $$ = newAst("ELSEIF_stm",4,$1,$2,$3,$4); }
	| ELSEIF Condition THEN END_IF { $$ = newAst("ELSEIF_stm",4,$1,$2,$3,$4); }
	;

ELSE_stm:
	ELSE StatementList END_IF { $$ = newAst("ELSE_stm",3,$1,$2,$3); }
	| ELSE END_IF { $$ = newAst("ELSE_stm",2,$1,$2); }
	;

WHILE_stm:
	WHILE Condition DO StatementList END_WHILE { $$ = newAst("WHILE_stm",5,$1,$2,$3,$4,$5); }
	| WHILE Condition DO END_WHILE { $$ = newAst("WHILE_stm",4,$1,$2,$3,$4); }
	;

LOOP_stm:
	LOOP intgr DO StatementList END_LOOP { $$ = newAst("LOOP_stm",5,$1,$2,$3,$4,$5); }
	| LOOP id DO StatementList END_LOOP { $$ = newAst("LOOP_stm",5,$1,$2,$3,$4,$5); existVar($2);
	if (strcmp($2->type, "INTEGER") ||  (!strcmp($2->type, "INTEGER") && $2->intgr < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $2->content); flag = 1; }}
	| LOOP intgr DO END_LOOP { $$ = newAst("LOOP_stm",4,$1,$2,$3,$4); }
	| LOOP id DO END_LOOP { $$ = newAst("LOOP_stm",4,$1,$2,$3,$4); existVar($2);
	if (strcmp($2->type, "INTEGER") ||  (!strcmp($2->type, "INTEGER") && $2->intgr < 0))
	{ printf("Error at Line %d: Type mismatched for parameter '%s'.\n", yylineno, $2->content); flag = 1; }}
	;

RUN_stm:
	RUN id LP RP { $$ = newAst("RUN_stm",4,$1,$2,$3,$4);
	char *progFilePath = new char[projName.size() + strlen($2->content) + 40];
	sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", $2->content, ".prog");
	FILE *progFile = fopen(progFilePath, "r");
	delete[]progFilePath;
	if (!progFile)
	{ 
	  printf("The subprogram '%s' dose not exist.\n", $2->content); flag = 1;
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
		if (!strcmp(varProg, $2->content))
		{
		  firstCompile = false;
		  break;
		}
	  }
	  if (firstCompile)
	  {
		varProgQueue.push($2->content);
	  }}}
	;

KILL_stm:
	KILL id LP RP { $$ = newAst("KILL_stm",4,$1,$2,$3,$4);
	char *progFilePath = new char[projName.size() + strlen($2->content) + 40];
	sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", $2->content, ".prog");
	FILE *progFile = fopen(progFilePath, "r");
	delete[]progFilePath;
	if (!progFile)
	{ 
	  printf("The subprogram '%s' dose not exist.\n", $2->content); flag = 1;
	}
	else
	{
	  fclose(progFile);
	}}
	;

RETURN_stm:
	RETURN { $$ = newAst("RETURN_stm",1,$1); }
	;

GOTO_stm:
	GOTO id { $$ = newAst("GOTO_stm",2,$1,$2); }
	| IF Condition GOTO id { $$ = newAst("GOTO_stm",4,$1,$2,$3,$4); }
	;

LABEL_stm:
	id COLON { $$ = newAst("LABEL_stm",2,$1,$2); newLabel($1); }
	;

DOT_expr:
	id DOT id { $$ = newAst("DOT_expr",3,$1,$2,$3); existVar($1); dot_var2ast($1,$3,$$); }
	;

ASSIGN_stm:
	id ASSIGN Expression { $$ = newAst("ASSIGN_stm",3,$1,$2,$3); existVar($1); assignment($1,$3); ast2ast($1,$$); ast2var($1); }
	| DOT_expr ASSIGN Expression { $$ = newAst("ASSIGN_stm",3,$1,$2,$3); assignment($1,$3); ast2ast($1,$$); dot_ast2var($1->l,$1->l->r->r,$1); }
	;

Expression:	
	Expression AND Expression { $$ = newAst("Expression",3,$1,$2,$3); logical($1,$2,$3,$$); }
	| Expression OR Expression { $$ = newAst("Expression",3,$1,$2,$3); logical($1,$2,$3,$$); }
	| Expression XOR Expression { $$ = newAst("Expression",3,$1,$2,$3); logical($1,$2,$3,$$); }
	| Expression MUL Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }	
	| Expression DIV Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| Expression PLUS Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }	
	| Expression MINUS Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| Expression EQ Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| Expression NE Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| Expression LE Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| Expression LT Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| Expression GE Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| Expression GT Expression { $$ = newAst("Expression",3,$1,$2,$3); arithmetic($1,$2,$3,$$); }
	| MINUS Expression %prec UMINUS { $$ = newAst("Expression",2,$1,$2); minusOperator($2,$$); }
	| NOT Expression { $$ = newAst("Expression",2,$1,$2); notOperator($2,$$); }	
	| LP Expression RP { $$ = newAst("Expression",3,$1,$2,$3); ast2ast($2,$$); }	
	| LP ASSIGN_stm RP { $$ = newAst("Expression",3,$1,$2,$3); ast2ast($2,$$); }	
	| DOT_expr { $$ = newAst("Expression",1,$1); }
	| id { existVar($1); $$ = newAst("Expression",1,$1); }
	| intgr { $$ = newAst("Expression",1,$1); }
	| flt { $$ = newAst("Expression",1,$1); }
	| str { $$ = newAst("Expression",1,$1); }
	| bl { $$ = newAst("Expression",1,$1); }
	;
%%