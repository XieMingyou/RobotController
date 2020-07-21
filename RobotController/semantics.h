/*Function:创建符号表&抽象语义树&错误处理函数*/
#ifndef Semantics_H
#define Semantics_H
#include <queue>
#include "dataDeclaration.h"

using namespace std;
extern struct AST *mainProgRoot; //主程序对应根结点
extern queue<char*> varProgQueue; //需要编译的变量和程序文件队列
extern char *curVarProg; //当前正在编译的变量和程序文件名称
extern struct AST *rootHead, *rootTail; //根结点表的头指针和尾指针
extern struct VAR *varHead, *varTail; //符号表的头指针和尾指针
extern struct LABEL *labelHead, *labelTail; //标签链表的头指针和尾指针
extern struct CARTSYS worldRefSys; //世界坐标系
extern int flag;//文本程序是否出错标记，0表示没有错误，其他值表示有错误

/*抽象语法树的结点*/
struct AST
{
	struct AST *l;//孩子结点
	struct AST *r;//兄弟结点
	struct AST *f;//父亲结点
	int line; //行号
	char *name;//语法单元的名字
	char *content;//语法单元语义值(记录id、intgr、flt、str和bl的内容)
	char *type;//语法单元数据类型:主要用于操作符左右类型匹配判断，数据类型包括：INTEGER REAL STRING BOOL AXISPOS CARTPOS ROBSXISPOS ROBCARTPOS WORLDREFSYS CARTREFSYS TOOL DYNAMIC
	int intgr;
	double flt;
	char *str;
	bool bl;
	struct AXISPOS axisPos;
	struct CARTPOS cartPos;
	struct AUXAXISPOS auxAxisPos;
	struct CARTSYS cartSys;
	struct CARTREFSYS cartRefSys;
	struct DYNAMIC dynamic;
	struct AST *next;//根结点指针
	struct AST *thisRoot; //结点的根结点指针
	int activeProg; //判断根结点对应的程序是否被激活，activeProg==0时终止程序，activeProg==1时激活程序
	int runProg; //判断根结点对应的程序是否被执行，runProg==0时停止程序，runProg==1时继续程序
	char *varProgName; //用于记录根结点对应的变量和程序文件
	int hasRun;//判断语句是否已经解释
};

/*变量符号表的结点*/
struct VAR
{
	char *content;//变量名
	char *type;//变量类型
	int intgr;
	double flt;
	char *str;
	bool bl;
	struct AXISPOS axisPos;
	struct CARTPOS cartPos;
	struct CARTSYS cartSys;
	struct CARTREFSYS cartRefSys;
	struct DYNAMIC dynamic;
	struct VAR *next;//指针
};

struct LABEL
{
	char *labelName; //标签名
	struct LABEL *next; //链表指针
};

/*=====抽象语法树========================*/
/*构造抽象语法树,变长参数，name:语法单元名字；num:变长参数中语法结点个数*/
struct AST *newAst(char *name, int num, ...);

/*将抽象语法树的子结点值赋给父结点*/
void ast2ast(struct AST *a1, struct AST *a2);

/*遍历抽象语法树，level为树的层数*/
void traverse(struct AST*, int level);

/*=====变量符号表========================*/
/*建立变量符号表*/
void newVar(struct AST*, struct AST*);

/*查找变量是否已经定义,是返回1，否返回0*/
int  findVar(struct AST *a);

/*查找变量类型*/
char *typeVar(struct VAR *a);

/*将符号表的变量值赋值给抽象语法树的id结点*/
void var2ast(struct AST *a);

/*将抽象语法树的id结点值赋值给符号表的变量*/
void ast2var(struct AST *a);

/*将符号表的成员变量值赋值给抽象语法树的DOT_expr结点*/
void dot_var2ast(struct AST *a1, struct AST *a2, struct AST *a3);

/*将抽象语法树的DOT_expr结点值赋值给符号表的成员变量*/
void dot_ast2var(struct AST *a1, struct AST *a2, struct AST *a3);

/*=====标签链表========================*/
/*建立标签链表*/
void newLabel(struct AST *a);

/*查找标签是否已经存在,是返回1，否返回0*/
int  findLabel(struct AST *a);

/*====错误类型================*/
/*检查操作符左右两边类型是否匹配*/
void assignment(struct AST *a1, struct AST *a2);
void logical(struct AST *a1, struct AST *a2, struct AST *a3, struct AST *a4);
void arithmetic(struct AST *a1, struct AST *a2, struct AST *a3, struct AST *a4);
void minusOperator(struct AST *a1, struct AST *a2);
void notOperator(struct AST *a1, struct AST *a2);

/*检查数据文件定义类型是否正确*/
void defTypeError(struct AST *a1, struct AST *a2);

/*检查程序文件中的变量是否已定义*/
void existVar(struct AST *a);

/*检查条件表达式的类型是否为BOOL*/
void isBool(struct AST *a);

/*其他错误处理函数*/
void yyerror(char *s, ...);

/*编译变量和程序文件*/
int varProgCompile();

/*释放语义分析树动态申请的内存，防止内存泄漏*/
void deleteAst(struct AST *a);

/*将根结点下的所有子结点的thisRoot指向根结点本身*/
void setThisRoot(struct AST *a);

/*计算参考坐标系在世界坐标系下的位姿*/
void calculateCartSys(struct AST *a1, struct AST *a2);

#endif // Semantics_H