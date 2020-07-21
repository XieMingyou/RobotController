/*Function:创建符号表&抽象语义树&错误处理函数*/
#define _CRT_SECURE_NO_WARNINGS
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include<stdarg.h>//变长参数函数所需的头文件
# include"lexicon.h"
# include"syntax.h"
# include"semantics.h"
# include"robotAlgorithm.h"

struct AST *mainProgRoot; //主程序对应根结点
queue<char*> varProgQueue; //需要编译的变量和程序文件队列
char *curVarProg; //当前正在编译的变量和程序文件名称
struct AST *rootHead, *rootTail; //根结点表的头指针和尾指针
struct VAR *varHead, *varTail; //符号表的头指针和尾指针
struct LABEL *labelHead, *labelTail; //标签链表的头指针和尾指针
struct CARTSYS worldRefSys; //世界坐标系
int flag;//文本程序是否出错标记，0表示没有错误，其他值表示有错误


struct AST *newAst(char *name, int num, ...)//抽象语法树建立
{
	va_list valist; //定义变长参数列表
	struct AST *a = new struct AST();//新生成的父结点
	if (a == NULL)
	{
		printf("Failed to apply for memory dynamically");
		flag = 1;
		return a;
	}	
	struct AST initial = { 0 };
	*a = initial;
	if (!a)
	{
		yyerror("out of space");
		exit(0);
	}
	a->name = name;//语法单元名字
	va_start(valist, num);//初始化变长参数为num后的参数

	if (num > 0)//num>0为非终结符：变长参数均为语法树结点，孩子兄弟表示法
	{
		struct AST *temp = va_arg(valist, struct AST *);//取变长参数列表中的第一个结点设为a的左孩子
		temp->f = a;//将父结点赋值给子结点
		a->l = temp;
		a->line = temp->line;//父结点a的行号等于左孩子的行号
		if (num == 1)//只有一个孩子
		{
			ast2ast(temp, a);
		}
		else //可以规约到a的语法单元>=2
		{
			for (int i = 0; i < num - 1; ++i)//取变长参数列表中的剩余结点，依次设置成兄弟结点
			{
				temp->r = va_arg(valist, struct AST *);
				temp = temp->r;
				temp->f = a;//将父结点赋值给子结点
			}
			a->content = "";
			a->type = "";
		}
	}
	else  //num==0为终结符或产生空的语法单元：第1个变长参数表示行号，产生空的语法单元行号为-1
	{
		int t = va_arg(valist, int); //取第1个变长参数
		a->line = t;
		char *s = new char[strlen(yytext) + 1];
		strcpy(s, yytext);//存储词法单元的语义值
		a->content = s;
		a->type = "";
		if(!strcmp(a->name, "intgr"))
		{
			a->type = "INTEGER";
			a->intgr = atoi(a->content);
		}
		else if (!strcmp(a->name, "flt"))
		{
			a->type = "FLOAT";
			a->flt = atof(a->content);
		}
		else if (!strcmp(a->name, "str"))
		{
			a->type = "STRING";
			a->str = a->content;
		}
		else if (!strcmp(a->name, "bl"))
		{
			a->type = "BOOL";
			if (!(strcmp(a->content, "TRUE") && strcmp(a->content, "true")))
			{
				a->bl = 1;
			}
			else if (!(strcmp(a->content, "FALSE") && strcmp(a->content, "false")))
			{
				a->bl = 0;
			}
		}
		else
		{
			a->type = "";
		}
	}
	return a;
}

/*将抽象语法树的子结点值赋给父结点*/
void ast2ast(struct AST *a1, struct AST *a2)
{
	a2->content = a1->content;
	a2->type = a1->type;
	a2->intgr = a1->intgr;
	a2->flt = a1->flt;
	a2->str = a1->str;
	a2->bl = a1->bl;
	a2->axisPos = a1->axisPos;
	a2->cartPos = a1->cartPos;
	a2->cartSys = a1->cartSys;
	a2->cartRefSys = a1->cartRefSys;
	a2->dynamic = a1->dynamic;
}

void traverse(struct AST *a, int level)//先序遍历抽象语法树
{
	if (a != NULL)
	{
		for (int i = 1; i < level; i++)//孩子结点相对父结点缩进2个空格
		{
			printf("  ");
		}
		printf("%s ", a->name);//打印语法单元名字，id/intgr/flt/bl/str要打印yytext的值
		if ((!strcmp(a->name, "id")) || (!strcmp(a->name, "str")) || (!strcmp(a->name, "bl")) || (!strcmp(a->name, "intgr")) || (!strcmp(a->name, "flt")))
		{
			printf(": %s ", a->content);
		}
		else
		{
			printf("(%d)", a->line);
		}
		printf("\n");
		traverse(a->l, level + 1);//遍历左子树
		traverse(a->r, level);//遍历右子树
	}
}

/*====变量符号表的建立和查询================*/
void newVar(struct AST *a1, struct AST *a2)//创建变量符号表
{
	if (findVar(a1))
	{
		printf("Error at Line %d: Redefined Variable '%s'.\n", yylineno, a1->content);
		flag = 1;
	}
	else
	{
		struct VAR *v = new struct VAR();
		if (v == NULL)
		{
			printf("Failed to apply for memory dynamically");
			flag = 1;
			return;
		}
		struct VAR initial = { 0 };
		*v = initial;
		v->content = a1->content;
		v->type = a2->type;
		v->intgr = a2->intgr;
		v->flt = a2->flt;
		v->str = a2->str;
		v->bl = a2->bl;
		v->axisPos = a2->axisPos;
		v->cartPos = a2->cartPos;
		v->cartSys = a2->cartSys;
		v->cartRefSys = a2->cartRefSys;
		v->dynamic = a2->dynamic;
		varTail->next = v;
		varTail = v;
	}
}

int  findVar(struct AST *a)//查找变量是否已经定义，是返回1，否返回0
{
	struct VAR *v;
	v = varHead->next;
	while (v != NULL)
	{
		if (!strcmp(v->content, a->content))
		{
			return 1;//存在返回1
		}
		v = v->next;
	}
	return 0;//不存在返回0
}

/*将符号表的变量值赋值给抽象语法树的id结点*/
void var2ast(struct AST *a)
{
	struct VAR *v;
	v = varHead->next;
	while (v != NULL)
	{
		if (!strcmp(v->content, a->content))
		{
			a->type = v->type;
			a->intgr = v->intgr;
			a->flt = v->flt;
			a->str = v->str;
			a->bl = v->bl;
			a->axisPos = v->axisPos;
			a->cartPos = v->cartPos;
			a->cartSys = v->cartSys;
			a->cartRefSys = v->cartRefSys;
			a->dynamic = v->dynamic;
		}
		v = v->next;
	}
}

/*将抽象语法树的id结点值赋值给符号表的变量*/
void ast2var(struct AST *a)
{
	struct VAR *v;
	v = varHead->next;
	while (v != NULL)
	{
		if (!strcmp(v->content, a->content))
		{
			v->intgr = a->intgr;
			v->flt = a->flt;
			v->str = a->str;
			v->bl = a->bl;
			v->axisPos = a->axisPos;
			v->cartPos = a->cartPos;
			v->cartSys = a->cartSys;
			v->cartRefSys = a->cartRefSys;
			v->dynamic = a->dynamic;
		}
		v = v->next;
	}
}

/*将符号表的成员变量值赋值给抽象语法树的DOT_expr结点*/
void dot_var2ast(struct AST *a1, struct AST *a2, struct AST *a3)
{
	if (!strcmp(a1->type, "NULL"))
	{
		a3->type = "NULL";
		return;
	}
	else if ((!strcmp(a1->type, "INTEGER")) || (!strcmp(a1->type, "FLOAT")) || (!strcmp(a1->type, "BOOL")) || (!strcmp(a1->type, "STRING")))
	{
		printf("Error at Line %d: '%s' is not a variable.\n", yylineno, a1->content);
		flag = 1;
	}
	else
	{
		struct VAR *v;
		v = varHead->next;
		while (v != NULL)
		{
			if (!strcmp(v->content, a1->content))
			{
				if (!strcmp(a1->type, "AXISPOS"))
				{
					a3->type = "FLOAT";
					if (!strcmp(a2->content, "a1"))
					{
						a3->flt = v->axisPos.a1;
					}
					else if (!strcmp(a2->content, "a2"))
					{
						a3->flt = v->axisPos.a2;
					}
					else if (!strcmp(a2->content, "a3"))
					{
						a3->flt = v->axisPos.a3;
					}
					else if (!strcmp(a2->content, "a4"))
					{
						a3->flt = v->axisPos.a4;
					}
					else if (!strcmp(a2->content, "a5"))
					{
						a3->flt = v->axisPos.a5;
					}
					else if (!strcmp(a2->content, "a6"))
					{
						a3->flt = v->axisPos.a6;
					}
					else if (!strcmp(a2->content, "aux1"))
					{
						a3->flt = v->axisPos.aux1;
					}
					else if (!strcmp(a2->content, "aux2"))
					{
						a3->flt = v->axisPos.aux2;
					}
					else if (!strcmp(a2->content, "aux3"))
					{
						a3->flt = v->axisPos.aux3;
					}
					else if (!strcmp(a2->content, "aux4"))
					{
						a3->flt = v->axisPos.aux4;
					}
					else if (!strcmp(a2->content, "aux5"))
					{
						a3->flt = v->axisPos.aux5;
					}
					else
					{
						printf("Error at Line %d: Struct variable '%s' has no member '%s'.\n", yylineno, a1->content, a2->content);
						flag = 1;
					}
				}
				else if (!strcmp(a1->type, "CARTPOS"))
				{
					a3->type = "FLOAT";
					if (!strcmp(a2->content, "x"))
					{
						a3->flt = v->cartPos.x;
					}
					else if (!strcmp(a2->content, "y"))
					{
						a3->flt = v->cartPos.y;
					}
					else if (!strcmp(a2->content, "z"))
					{
						a3->flt = v->cartPos.z;
					}
					else if (!strcmp(a2->content, "a"))
					{
						a3->flt = v->cartPos.a;
					}
					else if (!strcmp(a2->content, "b"))
					{
						a3->flt = v->cartPos.b;
					}
					else if (!strcmp(a2->content, "c"))
					{
						a3->flt = v->cartPos.c;
					}
					else if (!strcmp(a2->content, "aux1"))
					{
						a3->flt = v->cartPos.aux1;
					}
					else if (!strcmp(a2->content, "aux2"))
					{
						a3->flt = v->cartPos.aux2;
					}
					else if (!strcmp(a2->content, "aux3"))
					{
						a3->flt = v->cartPos.aux3;
					}
					else if (!strcmp(a2->content, "aux4"))
					{
						a3->flt = v->cartPos.aux4;
					}
					else if (!strcmp(a2->content, "aux5"))
					{
						a3->flt = v->cartPos.aux5;
					}
					else if (!strcmp(a2->content, "mode"))
					{
						a3->type = "INTEGER";
						a3->intgr = v->cartPos.mode;
					}
					else
					{
						printf("Error at Line %d: Struct variable '%s' has no member '%s'.\n", yylineno, a1->content, a2->content);
						flag = 1;
					}
				}
				else if (!strcmp(a1->type, "CARTSYS"))
				{
					a3->type = "FLOAT";
					if (!strcmp(a2->content, "x"))
					{
						a3->flt = v->cartSys.x;
					}
					else if (!strcmp(a2->content, "y"))
					{
						a3->flt = v->cartSys.y;
					}
					else if (!strcmp(a2->content, "z"))
					{
						a3->flt = v->cartSys.z;
					}
					else if (!strcmp(a2->content, "a"))
					{
						a3->flt = v->cartSys.a;
					}
					else if (!strcmp(a2->content, "b"))
					{
						a3->flt = v->cartSys.b;
					}
					else if (!strcmp(a2->content, "c"))
					{
						a3->flt = v->cartSys.c;
					}
					else
					{
						printf("Error at Line %d: Struct variable '%s' has no member '%s'.\n", yylineno, a1->content, a2->content);
						flag = 1;
					}
				}
				else if (!strcmp(a1->type, "CARTREFSYS"))
				{
					a3->type = "FLOAT";
					if (!strcmp(a2->content, "x"))
					{
						a3->flt = v->cartRefSys.x;
					}
					else if (!strcmp(a2->content, "y"))
					{
						a3->flt = v->cartRefSys.y;
					}
					else if (!strcmp(a2->content, "z"))
					{
						a3->flt = v->cartRefSys.z;
					}
					else if (!strcmp(a2->content, "a"))
					{
						a3->flt = v->cartRefSys.a;
					}
					else if (!strcmp(a2->content, "b"))
					{
						a3->flt = v->cartRefSys.b;
					}
					else if (!strcmp(a2->content, "c"))
					{
						a3->flt = v->cartRefSys.c;
					}
					else if (!strcmp(a2->content, "baseRefSys"))
					{
						if (!strcmp(v->cartRefSys.baseRefSys, "worldRefSys"))
						{
							a3->type = "CARTSYS";
							a3->cartSys = worldRefSys;
						}
						else
						{
							a3->type = "CARTREFSYS";
							struct VAR *p;
							p = varHead->next;
							while (p != NULL)
							{
								if (!strcmp(p->content, a2->content))
								{
									a3->cartRefSys = p->cartRefSys;
								}
								p = p->next;
							}
						}
					}
					else
					{
						printf("Error at Line %d: Struct variable '%s' has no member '%s'.\n", yylineno, a1->content, a2->content);
						flag = 1;
					}
				}
				else if (!strcmp(a1->type, "DYNAMIC"))
				{
					a3->type = "FLOAT";
					if (!strcmp(a2->content, "velAxis"))
					{
						a3->flt = v->dynamic.velAxis;
					}
					else if (!strcmp(a2->content, "accAxis"))
					{
						a3->flt = v->dynamic.accAxis;
					}
					else if (!strcmp(a2->content, "decAxis"))
					{
						a3->flt = v->dynamic.decAxis;
					}
					else if (!strcmp(a2->content, "jerkAxis"))
					{
						a3->flt = v->dynamic.jerkAxis;
					}
					else if (!strcmp(a2->content, "velPath"))
					{
						a3->flt = v->dynamic.velPath;
					}
					else if (!strcmp(a2->content, "accPath"))
					{
						a3->flt = v->dynamic.accPath;
					}
					else if (!strcmp(a2->content, "decPath"))
					{
						a3->flt = v->dynamic.decPath;
					}
					else if (!strcmp(a2->content, "jerkPath"))
					{
						a3->flt = v->dynamic.jerkPath;
					}
					else if (!strcmp(a2->content, "velOri"))
					{
						a3->flt = v->dynamic.velOri;
					}
					else if (!strcmp(a2->content, "accOri"))
					{
						a3->flt = v->dynamic.accOri;
					}
					else if (!strcmp(a2->content, "decOri"))
					{
						a3->flt = v->dynamic.decOri;
					}
					else if (!strcmp(a2->content, "jerkOri"))
					{
						a3->flt = v->dynamic.jerkOri;
					}
					else
					{
						printf("Error at Line %d: Struct variable '%s' has no member '%s'.\n", yylineno, a1->content, a2->content);
						flag = 1;
					}
				}
			}
			v = v->next;
		}
	}
}

/*将抽象语法树的DOT_expr结点值赋值给符号表的成员变量*/
void dot_ast2var(struct AST *a1, struct AST *a2, struct AST *a3)
{
	if (!strcmp(a1->type, "NULL"))
	{
		return;
	}
	else if ((!strcmp(a1->type, "INTEGER")) || (!strcmp(a1->type, "FLOAT")) || (!strcmp(a1->type, "BOOL")) || (!strcmp(a1->type, "STRING")))
	{
		return;
	}
	else
	{
		struct VAR *v;
		v = varHead->next;
		while (v != NULL)
		{
			if (!strcmp(v->content, a1->content))
			{
				if (!strcmp(a1->type, "AXISPOS"))
				{
					if (!strcmp(a2->content, "a1"))
					{
						v->axisPos.a1 = a3->flt;
					}
					else if (!strcmp(a2->content, "a2"))
					{
						v->axisPos.a2 = a3->flt;
					}
					else if (!strcmp(a2->content, "a3"))
					{
						v->axisPos.a3 = a3->flt;
					}
					else if (!strcmp(a2->content, "a4"))
					{
						 v->axisPos.a4 = a3->flt;
					}
					else if (!strcmp(a2->content, "a5"))
					{
						 v->axisPos.a5 = a3->flt;
					}
					else if (!strcmp(a2->content, "a6"))
					{
						 v->axisPos.a6 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux1"))
					{
						 v->axisPos.aux1 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux2"))
					{
						v->axisPos.aux2 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux3"))
					{
						 v->axisPos.aux3 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux4"))
					{
						 v->axisPos.aux4 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux5"))
					{
						 v->axisPos.aux5 = a3->flt;
					}
				}
				else if (!strcmp(a1->type, "CARTPOS"))
				{
					if (!strcmp(a2->content, "x"))
					{
						 v->cartPos.x = a3->flt;
					}
					else if (!strcmp(a2->content, "y"))
					{
						 v->cartPos.y = a3->flt;
					}
					else if (!strcmp(a2->content, "z"))
					{
						 v->cartPos.z = a3->flt;
					}
					else if (!strcmp(a2->content, "a"))
					{
						 v->cartPos.a = a3->flt;
					}
					else if (!strcmp(a2->content, "b"))
					{
						 v->cartPos.b = a3->flt;
					}
					else if (!strcmp(a2->content, "c"))
					{
						v->cartPos.c = a3->flt;
					}
					else if (!strcmp(a2->content, "aux1"))
					{
						v->cartPos.aux1 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux2"))
					{
						v->cartPos.aux2 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux3"))
					{
						v->cartPos.aux3 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux4"))
					{
						v->cartPos.aux4 = a3->flt;
					}
					else if (!strcmp(a2->content, "aux5"))
					{
						v->cartPos.aux5 = a3->flt;
					}
					else if (!strcmp(a2->content, "mode"))
					{
						 v->cartPos.mode = a3->intgr;
					}
				}
				else if (!strcmp(a1->type, "CARTSYS"))
				{
					if (!strcmp(a2->content, "x"))
					{
						 v->cartSys.x = a3->flt;
					}
					else if (!strcmp(a2->content, "y"))
					{
						v->cartSys.y = a3->flt;
					}
					else if (!strcmp(a2->content, "z"))
					{
						v->cartSys.z = a3->flt;
					}
					else if (!strcmp(a2->content, "a"))
					{
						v->cartSys.a = a3->flt;
					}
					else if (!strcmp(a2->content, "b"))
					{
						v->cartSys.b = a3->flt;
					}
					else if (!strcmp(a2->content, "c"))
					{
						v->cartSys.c = a3->flt;
					}
				}
				else if (!strcmp(a1->type, "CARTREFSYS"))
				{
					if (!strcmp(a2->content, "x"))
					{
						v->cartRefSys.x = a3->flt;
					}
					else if (!strcmp(a2->content, "y"))
					{
						v->cartRefSys.y = a3->flt;
					}
					else if (!strcmp(a2->content, "z"))
					{
						v->cartRefSys.z = a3->flt;
					}
					else if (!strcmp(a2->content, "a"))
					{
						v->cartRefSys.a = a3->flt;
					}
					else if (!strcmp(a2->content, "b"))
					{
						v->cartRefSys.b = a3->flt;
					}
					else if (!strcmp(a2->content, "c"))
					{
						v->cartRefSys.c = a3->flt;
					}
					else if (!strcmp(a2->content, "baseRefSys"))
					{
						if (!strcmp(v->cartRefSys.baseRefSys, "worldRefSys"))
						{
							 worldRefSys = a3->cartSys;
						}
						else
						{
							struct VAR *p;
							p = varHead->next;
							while (p != NULL)
							{
								if (!strcmp(p->content, a2->content))
								{
									 p->cartRefSys = a3->cartRefSys;
								}
								p = p->next;
							}
						}
					}
				}
				else if (!strcmp(a1->type, "DYNAMIC"))
				{
					if (!strcmp(a2->content, "velAxis"))
					{
						 v->dynamic.velAxis = a3->flt;
					}
					else if (!strcmp(a2->content, "accAxis"))
					{
						v->dynamic.accAxis = a3->flt;
					}
					else if (!strcmp(a2->content, "decAxis"))
					{
						v->dynamic.decAxis = a3->flt;
					}
					else if (!strcmp(a2->content, "jerkAxis"))
					{
						v->dynamic.jerkAxis = a3->flt;
					}
					else if (!strcmp(a2->content, "velPath"))
					{
						v->dynamic.velPath = a3->flt;
					}
					else if (!strcmp(a2->content, "accPath"))
					{
						v->dynamic.accPath = a3->flt;
					}
					else if (!strcmp(a2->content, "decPath"))
					{
						v->dynamic.decPath = a3->flt;
					}
					else if (!strcmp(a2->content, "jerk"))
					{
						v->dynamic.jerkPath = a3->flt;
					}
					else if (!strcmp(a2->content, "velOri"))
					{
						v->dynamic.velOri = a3->flt;
					}
					else if (!strcmp(a2->content, "accOri"))
					{
						v->dynamic.accOri = a3->flt;
					}
					else if (!strcmp(a2->content, "decOri"))
					{
						v->dynamic.decOri = a3->flt;
					}
					else if (!strcmp(a2->content, "jerkOri"))
					{
						v->dynamic.jerkOri = a3->flt;
					}
				}
			}
			v = v->next;
		}
	}
}

/*=====标签链表========================*/
/*建立标签链表*/
void newLabel(struct AST *a)
{
	if (findVar(a))
	{
		printf("Error at Line %d: Label '%s' has been existed.\n", yylineno, a->content);
		flag = 1;
	}
	else
	{
		struct LABEL *l = new struct LABEL();
		if (l == NULL)
		{
			printf("Failed to apply for memory dynamically");
			flag = 1;
			return;
		}
		struct LABEL initial = { 0 };
		*l = initial;
		l->labelName = a->content;
		labelTail->next = l;
		labelTail = l;
	}
}

/*查找标签是否已经存在,是返回1，否返回0*/
int  findLabel(struct AST *a)
{
	struct LABEL *l;
	l = labelHead->next;
	while (l != NULL)
	{
		if (!strcmp(l->labelName, a->content))
		{
			return 1;//存在返回1
		}
		l = l->next;
	}
	return 0;//不存在返回0
}

/*====错误类型================*/
/*操作符左右两边类型不匹配*/
void assignment(struct AST *a1, struct AST *a2)
{
	if ((strcmp(a1->type, "INTEGER") && strcmp(a1->type, "FLOAT") && strcmp(a1->type, "BOOL") && strcmp(a1->type, "STRING")) || (strcmp(a2->type, "INTEGER") && strcmp(a2->type, "FLOAT") && strcmp(a2->type, "BOOL") && strcmp(a2->type, "STRING")))
	{
		printf("Error at Line %d: Type mismatched for assignment operand.\n", yylineno); 
		flag = 1;
	}
	else if (strcmp(a1->type, a2->type) && ((!strcmp(a1->type, "STRING")) || (!strcmp(a2->type, "STRING"))))
	{
		printf("Error at Line %d: Type mismatched for assignment operand.\n", yylineno);
		flag = 1;
	}
	else
	{
		if ((!strcmp(a1->type, "INTEGER")) && (!strcmp(a2->type, "INTEGER")))
		{
			a1->intgr = a2->intgr;
		}
		else if ((!strcmp(a1->type, "INTEGER")) && (!strcmp(a2->type, "FLOAT")))
		{
			a1->intgr = a2->flt;
		}
		else if ((!strcmp(a1->type, "INTEGER")) && (!strcmp(a2->type, "BOOL")))
		{
			a1->intgr = a2->bl;
		}
		else if ((!strcmp(a1->type, "FLOAT")) && (!strcmp(a2->type, "INTEGER")))
		{
			a1->flt = a2->intgr;
		}
		else if ((!strcmp(a1->type, "FLOAT")) && (!strcmp(a2->type, "FLOAT")))
		{
			a1->flt = a2->flt;
		}
		else if ((!strcmp(a1->type, "FLOAT")) && (!strcmp(a2->type, "BOOL")))
		{
			a1->flt = a2->bl;
		}
		else if ((!strcmp(a1->type, "BOOL")) && (!strcmp(a2->type, "INTEGER")))
		{
			if ((a2->intgr) == 0)
			{
				a1->bl = 0;
			}
			else
			{
				a1->bl = 1;
			}
		}
		else if ((!strcmp(a1->type, "BOOL")) && (!strcmp(a2->type, "FLOAT")))
		{
			if ((a2->flt) == 0)
			{
				a1->bl = 0;
			}
			else
			{
				a1->bl = 1;
			}
		}
		else if ((!strcmp(a1->type, "BOOL")) && (!strcmp(a2->type, "BOOL")))
		{
			if ((a2->bl) == 0)
			{
				a1->bl = 0;
			}
			else
			{
				a1->bl = 1;
			}
		}
		else if ((!strcmp(a1->type, "STRING")) && (!strcmp(a2->type, "STRING")))
		{
			a1->str = a2->str;
		}
	}
}

void logical(struct AST *a1, struct AST *a2, struct AST *a3, struct AST *a4)
{
	a4->type = "BOOL";
	if ((strcmp(a1->type, "INTEGER") && strcmp(a1->type, "FLOAT") && strcmp(a1->type, "BOOL")) || (strcmp(a3->type, "INTEGER") && strcmp(a3->type, "FLOAT") && strcmp(a3->type, "BOOL")))
	{
		printf("Error at Line %d: Type mismatched for logical operand.\n", yylineno); 
		flag = 1;
	}
	else if (!strcmp(a2->content, "&&"))
	{
		if (((!strcmp(a1->type, "INTEGER")) && (a1->intgr == 0)) || ((!strcmp(a1->type, "FLOAT")) && (a1->flt == 0)) || ((!strcmp(a1->type, "BOOL")) && (a1->bl == 0)) || ((!strcmp(a2->type, "INTEGER")) && (a2->intgr == 0)) || ((!strcmp(a2->type, "FLOAT")) && (a2->flt == 0)) || ((!strcmp(a2->type, "BOOL")) && (a2->bl == 0)))
		{
			a4->bl = 0;
		}
		else
		{
			a4->bl = 1;
		}
	}
	else if (!strcmp(a2->content, "||"))
	{
		if (((!strcmp(a1->type, "INTEGER")) && (a1->intgr != 0)) || ((!strcmp(a1->type, "FLOAT")) && (a1->flt != 0)) || ((!strcmp(a1->type, "BOOL")) && (a1->bl != 0)) || ((!strcmp(a2->type, "INTEGER")) && (a2->intgr != 0)) || ((!strcmp(a2->type, "FLOAT")) && (a2->flt != 0)) || ((!strcmp(a2->type, "BOOL")) && (a2->bl != 0)))
		{
			a4->bl = 1;
		}
		else
		{
			a4->bl = 0;
		}
	}
	else if (!strcmp(a2->content, "^"))
	{
		if ((((!strcmp(a1->type, "INTEGER")) && (a1->intgr == 0)) || ((!strcmp(a1->type, "FLOAT")) && (a1->flt == 0)) || ((!strcmp(a1->type, "BOOL")) && (a1->bl == 0)) && ((!strcmp(a2->type, "INTEGER")) && (a2->intgr != 0)) || ((!strcmp(a2->type, "FLOAT")) && (a2->flt != 0)) || ((!strcmp(a2->type, "BOOL")) && (a2->bl != 0))) \
			|| (((!strcmp(a1->type, "INTEGER")) && (a1->intgr != 0)) || ((!strcmp(a1->type, "FLOAT")) && (a1->flt != 0)) || ((!strcmp(a1->type, "BOOL")) && (a1->bl != 0)) && ((!strcmp(a2->type, "INTEGER")) && (a2->intgr == 0)) || ((!strcmp(a2->type, "FLOAT")) && (a2->flt == 0)) || ((!strcmp(a2->type, "BOOL")) && (a2->bl == 0))))
		{
			a4->bl = 1;
		}
		else
		{
			a4->bl = 0;
		}
	}
}

void arithmetic(struct AST *a1, struct AST *a2, struct AST *a3, struct AST *a4)
{
	a4->type = "BOOL";
	if ((!strcmp(a2->content, "==")) && ((strcmp(a1->type, "INTEGER") && strcmp(a1->type, "FLOAT") && strcmp(a1->type, "BOOL") && strcmp(a1->type, "STRING")) || (strcmp(a3->type, "INTEGER") && strcmp(a3->type, "FLOAT") && strcmp(a3->type, "BOOL") && strcmp(a3->type, "STRING"))))
	{
		printf("Error at Line %d: Type mismatched for arithmetic operand.\n", yylineno);
		flag = 1;
	}
	else if ((!strcmp(a2->content, "==")) && (strcmp(a1->type, a3->type) && ((!strcmp(a1->type, "STRING")) || (!strcmp(a3->type, "STRING")))))
	{
		printf("Error at Line %d: Type mismatched for arithmetic operand.\n", yylineno);
		flag = 1;
	}
	else if ((strcmp(a1->type, "INTEGER") && strcmp(a1->type, "FLOAT") && strcmp(a1->type, "BOOL")) || (strcmp(a3->type, "INTEGER") && strcmp(a3->type, "FLOAT") && strcmp(a3->type, "BOOL")))
	{
		printf("Error at Line %d: Type mismatched for arithmetic operand.\n", yylineno);
		flag = 1;
	}
	else
	{
		if ((!strcmp(a1->type, "INTEGER")) && (!strcmp(a3->type, "INTEGER")))
		{
			a4->type = "INTEGER";
			if (!strcmp(a2->content, "*"))
			{
				a4->intgr = (a1->intgr) * (a3->intgr);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->intgr = (a1->intgr) * (a3->intgr);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->intgr = (a1->intgr) + (a3->intgr);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->intgr = (a1->intgr) - (a3->intgr);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->intgr) == (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->intgr) != (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->intgr) > (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->intgr) >= (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->intgr) < (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->intgr) <= (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "INTEGER")) && (!strcmp(a3->type, "FLOAT")))
		{
			a4->type = "FLOAT";
			if (!strcmp(a2->content, "*"))
			{
				a4->flt = (a1->intgr) * (a3->flt);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->flt = (a1->intgr) * (a3->flt);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->flt = (a1->intgr) + (a3->flt);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->flt = (a1->intgr) - (a3->flt);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->intgr) == (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->intgr) != (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->intgr) > (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->intgr) >= (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->intgr) < (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->intgr) <= (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "INTEGER")) && (!strcmp(a3->type, "BOOL")))
		{
			a4->type = "INTEGER";
			if (!strcmp(a2->content, "*"))
			{
				a4->intgr = (a1->intgr) * (a3->bl);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->intgr = (a1->intgr) * (a3->bl);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->intgr = (a1->intgr) + (a3->bl);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->intgr = (a1->intgr) - (a3->bl);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->intgr) == (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->intgr) != (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->intgr) > (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->intgr) >= (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->intgr) < (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->intgr) <= (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "FLOAT")) && (!strcmp(a3->type, "INTEGER")))
		{
			a4->type = "FLOAT";
			if (!strcmp(a2->content, "*"))
			{
				a4->flt = (a1->flt) * (a3->intgr);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->flt = (a1->flt) * (a3->intgr);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->flt = (a1->flt) + (a3->intgr);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->flt = (a1->flt) - (a3->intgr);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->flt) == (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->flt) != (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->flt) > (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->flt) >= (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->flt) < (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->flt) <= (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "FLOAT")) && (!strcmp(a3->type, "FLOAT")))
		{
			a4->type = "FLOAT";
			if (!strcmp(a2->content, "*"))
			{
				a4->flt = (a1->flt) * (a3->flt);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->flt = (a1->flt) * (a3->flt);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->flt = (a1->flt) + (a3->flt);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->flt = (a1->flt) - (a3->flt);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->flt) == (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->flt) != (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->flt) > (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->flt) >= (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->flt) < (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->flt) <= (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "FLOAT")) && (!strcmp(a3->type, "BOOL")))
		{
			a4->type = "FLOAT";
			if (!strcmp(a2->content, "*"))
			{
				a4->flt = (a1->flt) * (a3->bl);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->flt = (a1->flt) * (a3->bl);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->flt = (a1->flt) + (a3->bl);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->flt = (a1->flt) - (a3->bl);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->flt) == (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->flt) != (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->flt) > (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->flt) >= (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->flt) < (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->flt) <= (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "BOOL")) && (!strcmp(a3->type, "INTEGER")))
		{
			a4->type = "INTEGER";
			if (!strcmp(a2->content, "*"))
			{
				a4->intgr = (a1->bl) * (a3->intgr);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->intgr = (a1->bl) * (a3->intgr);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->intgr = (a1->bl) + (a3->intgr);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->intgr = (a1->bl) - (a3->intgr);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->bl) == (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->bl) != (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->bl) > (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->bl) >= (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->bl) < (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->bl) <= (a3->intgr))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "BOOL")) && (!strcmp(a3->type, "FLOAT")))
		{
			a4->type = "FLOAT";
			if (!strcmp(a2->content, "*"))
			{
				a4->flt = (a1->bl) * (a3->flt);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->flt = (a1->bl) * (a3->flt);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->flt = (a1->bl) + (a3->flt);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->flt = (a1->bl) - (a3->flt);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->bl) == (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->bl) != (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->bl) > (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->bl) >= (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->bl) < (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->bl) <= (a3->flt))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "BOOL")) && (!strcmp(a3->type, "BOOL")))
		{
			a4->type = "INTEGER";
			if (!strcmp(a2->content, "*"))
			{
				a4->intgr = (a1->bl) * (a3->bl);
			}
			else if (!strcmp(a2->content, "/"))
			{
				a4->intgr = (a1->bl) * (a3->bl);
			}
			else if (!strcmp(a2->content, "+"))
			{
				a4->intgr = (a1->bl) + (a3->bl);
			}
			else if (!strcmp(a2->content, "-"))
			{
				a4->intgr = (a1->bl) - (a3->bl);
			}
			else
			{
				a4->type = "BOOL";
				if (!strcmp(a2->content, "=="))
				{
					if ((a1->bl) == (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "!="))
				{
					if ((a1->bl) != (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">"))
				{
					if ((a1->bl) > (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, ">="))
				{
					if ((a1->bl) >= (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<"))
				{
					if ((a1->bl) < (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
				else if (!strcmp(a2->content, "<="))
				{
					if ((a1->bl) <= (a3->bl))
					{
						a4->bl = 1;
					}
					else
					{
						a4->bl = 0;
					}
				}
			}
		}
		else if ((!strcmp(a1->type, "STRING")) && (!strcmp(a3->type, "STRING")))
		{
			a4->type = "BOOL";
			if ((!strcmp(a2->content, "==")))
			{
				if ((!strcmp(a1->str, a3->str)))
				{
					a4->bl = 1;
				}
				else
				{
					a4->bl = 0;
				}
			}
		}
	}
}

void minusOperator(struct AST *a1, struct AST *a2)
{
	if (strcmp(a1->type, "INTEGER") && strcmp(a1->type, "FLOAT") && strcmp(a1->type, "BOOL"))
	{
		printf("Error at Line %d: Type mismatched for minus operand.\n", yylineno);
		flag = 1;
	}
	ast2ast(a1, a2);
	if (!strcmp(a1->type, "INTEGER"))
	{
		a2->intgr = -(a1->intgr);
	}
	else if (!strcmp(a1->type, "FLOAT"))
	{
		a2->flt = -(a1->flt);
	}
	else if (!strcmp(a1->type, "BOOL"))
	{
		a2->intgr = -(a1->bl);
	}
}

void notOperator(struct AST *a1, struct AST *a2)
{
	if (strcmp(a1->type, "INTEGER") && strcmp(a1->type, "FLOAT") && strcmp(a1->type, "BOOL"))
	{
		printf("Error at Line %d: Type mismatched for logical operand.\n", yylineno);
		flag = 1;
	}
	ast2ast(a1, a2);
	a2->type = "BOOL";
	if (((!strcmp(a1->type, "INTEGER")) && (a1->intgr == 0)) || ((!strcmp(a1->type, "FLOAT")) && (a1->flt == 0)) || ((!strcmp(a1->type, "BOOL")) && (a1->bl == 0)))
	{
		a2->bl = 1;
	}
	else
	{
		a2->bl = 0;
	}
}



/*检查数据文件定义类型是否正确*/
void defTypeError(struct AST *a1, struct AST *a2)
{
	if (strcmp(a1->content, a2->type))
	{
		if (!(((!strcmp(a1->content, "TOOL")) || (!strcmp(a1->content, "WORLDREFSYS"))) && (!strcmp(a2->type, "CARTSYS"))))
		{
			printf("Error at Line %d: Definition type mismatched.\n", yylineno);
			flag = 1;
		}
	}
}

/*检查程序文件中的变量是否已定义*/
void existVar(struct AST *a)
{
	if (!findVar(a))
	{
		printf("Error at Line %d: Undefined variable '%s'.\n", yylineno, a->content);
		flag = 1;
		a->type = "NULL";
	}
	else
	{
		var2ast(a);
	}
}

/*检查条件表达式的类型是否为BOOL*/
void isBool(struct AST *a)
{
	if (strcmp(a->type, "BOOL") && strcmp(a->type, "INTEGER") && strcmp(a->type, "FLOAT"))
	{
		printf("Error at Line %d: The type of conditional expression is not 'BOOL'.\n", yylineno);
		flag = 1;
	}
	else
	{
		
		if (!strcmp(a->type, "BOOL"))
		{
			if ((a->bl) == 0)
			{
				a->bl = 0;
			}
			else
			{
				a->bl = 1;
			}
		}
		else if (!strcmp(a->type, "INTEGER"))
		{
			if ((a->intgr) == 0)
			{
				a->bl = 0;
			}
			else
			{
				a->bl = 1;
			}
		}
		else if (!strcmp(a->type, "FLOAT"))
		{
			if ((a->flt) == 0)
			{
				a->bl = 0;
			}
			else
			{
				a->bl = 1;
			}
		}
		a->type = "BOOL";
	}
}

void yyerror(char *s, ...) //变长参数错误处理函数
{
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "Error at Line %d: ", yylineno);//错误行号
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
	va_end(ap);
	flag = 1;
}

/*编译变量和程序文件*/
int varProgCompile()
{
	while (!varProgQueue.empty())
	{
		curVarProg = varProgQueue.front(); //当前将要编译的变量和程序名称
		varProgQueue.pop();
		varHead = new struct VAR();//变量符号表头指针
		varTail = varHead;//变量符号表尾指针
		struct VAR initialVar = { 0 };
		*varHead = initialVar;
		labelHead = new struct LABEL();//变量符号表头指针
		labelTail = labelHead;//变量符号表尾指针
		struct LABEL initialLabel = { 0 };
		*labelHead = initialLabel;
		flag = 0;
		char *varProgFilePath = new char[strlen(curVarProg) + 10];
		sprintf(varProgFilePath, "%s%s", curVarProg, ".var.prog");
		FILE *varProgFile = fopen(varProgFilePath, "w");
		if (!varProgFile)
		{
			perror("打开文件失败！");
			return -1;
		}
		char *varFilePath = new char[projName.size() + strlen(curVarProg) + 40];
		sprintf(varFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\var\\", projName.c_str(), "\\", curVarProg, ".var");
		FILE *varFile = fopen(varFilePath, "r");
		if (!varFile)
		{
			perror("打开文件失败！");
			return -1;
		}
		delete[]varFilePath;
		char *progFilePath = new char[projName.size() + strlen(curVarProg) + 40];
		sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", curVarProg, ".prog");
		FILE *progFile = fopen(progFilePath, "r");
		if (!progFile)
		{
			perror("打开文件失败！");
			return -1;
		}
		delete[]progFilePath;
		char ch;
		while ((ch = fgetc(varFile)) != EOF)
		{
			fputc(ch, varProgFile);
		}
		fclose(varProgFile);
		varProgFile = fopen(varProgFilePath, "a+");
		while ((ch = fgetc(progFile)) != EOF)
		{
			fputc(ch, varProgFile);
		}
		fclose(varFile);
		fclose(progFile);
		fclose(varProgFile);
		varProgFile = fopen(varProgFilePath, "r");
		yylineno = 1;
		yyrestart(varProgFile);
		flag = yyparse() || flag; //flag为0时表示编译通过，否则不通过
		//释放符号表动态申请的内存，防止内存泄漏
		while (varHead != NULL)
		{
			struct VAR *temp = varHead->next;
			delete varHead;
			varHead = temp;
		}
		//释放标签表动态申请的内存，防止内存泄漏
		while (labelHead != NULL)
		{
			struct LABEL *temp = labelHead->next;
			delete labelHead;
			labelHead = temp;
		}
		fclose(varProgFile);
		remove(varProgFilePath); //删除文件
		delete[]varProgFilePath;
	}
	return flag;
}

/*释放语义分析树动态申请的内存，防止内存泄漏*/
void deleteAst(struct AST *a)
{
	if (a != NULL)
	{
		deleteAst(a->l);
		deleteAst(a->r);
		delete a;
		a = NULL;
	}
}

/*将根结点下的所有子结点的thisRoot指向根结点本身*/
void setThisRoot(struct AST *a)
{
	if (a != NULL)
	{
		a->thisRoot = rootTail;
		setThisRoot(a->l);
		setThisRoot(a->r);
	}
}

/*计算参考坐标系在世界坐标系下的位姿*/
void calculateCartSys(struct AST *a1, struct AST *a2)
{
	struct CARTPOS cartPos1, cartPos2;
	cartPos1.x = a2->cartSys.x; cartPos1.y = a2->cartSys.y; cartPos1.z = a2->cartSys.z;
	cartPos1.a = a2->cartSys.a; cartPos1.b = a2->cartSys.b; cartPos1.c = a2->cartSys.c;
	cartPos2.x = a1->cartSys.x; cartPos2.y = a1->cartSys.y; cartPos2.z = a1->cartSys.z;
	cartPos2.a = a1->cartSys.a; cartPos2.b = a1->cartSys.b; cartPos2.c = a1->cartSys.c;
	Matrix4d T1 = pose2Matrix(cartPos1);
	Matrix4d T2 = pose2Matrix(cartPos2);
	Matrix4d T = T1 * T2;
	struct CARTPOS cartPos = matrix2Pose(T);
	a1->cartSys.x = cartPos.x; a1->cartSys.y = cartPos.y; a1->cartSys.z = cartPos.z;
	a1->cartSys.a = cartPos.a; a1->cartSys.b = cartPos.b; a1->cartSys.c = cartPos.c;
}