/*Function:�������ű�&����������&��������*/
#define _CRT_SECURE_NO_WARNINGS
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include<stdarg.h>//�䳤�������������ͷ�ļ�
# include"lexicon.h"
# include"syntax.h"
# include"semantics.h"
# include"robotAlgorithm.h"

struct AST *mainProgRoot; //�������Ӧ�����
queue<char*> varProgQueue; //��Ҫ����ı����ͳ����ļ�����
char *curVarProg; //��ǰ���ڱ���ı����ͳ����ļ�����
struct AST *rootHead, *rootTail; //�������ͷָ���βָ��
struct VAR *varHead, *varTail; //���ű��ͷָ���βָ��
struct LABEL *labelHead, *labelTail; //��ǩ�����ͷָ���βָ��
struct CARTSYS worldRefSys; //��������ϵ
int flag;//�ı������Ƿ�����ǣ�0��ʾû�д�������ֵ��ʾ�д���


struct AST *newAst(char *name, int num, ...)//�����﷨������
{
	va_list valist; //����䳤�����б�
	struct AST *a = new struct AST();//�����ɵĸ����
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
	a->name = name;//�﷨��Ԫ����
	va_start(valist, num);//��ʼ���䳤����Ϊnum��Ĳ���

	if (num > 0)//num>0Ϊ���ս�����䳤������Ϊ�﷨����㣬�����ֵܱ�ʾ��
	{
		struct AST *temp = va_arg(valist, struct AST *);//ȡ�䳤�����б��еĵ�һ�������Ϊa������
		temp->f = a;//������㸳ֵ���ӽ��
		a->l = temp;
		a->line = temp->line;//�����a���кŵ������ӵ��к�
		if (num == 1)//ֻ��һ������
		{
			ast2ast(temp, a);
		}
		else //���Թ�Լ��a���﷨��Ԫ>=2
		{
			for (int i = 0; i < num - 1; ++i)//ȡ�䳤�����б��е�ʣ���㣬�������ó��ֵܽ��
			{
				temp->r = va_arg(valist, struct AST *);
				temp = temp->r;
				temp->f = a;//������㸳ֵ���ӽ��
			}
			a->content = "";
			a->type = "";
		}
	}
	else  //num==0Ϊ�ս��������յ��﷨��Ԫ����1���䳤������ʾ�кţ������յ��﷨��Ԫ�к�Ϊ-1
	{
		int t = va_arg(valist, int); //ȡ��1���䳤����
		a->line = t;
		char *s = new char[strlen(yytext) + 1];
		strcpy(s, yytext);//�洢�ʷ���Ԫ������ֵ
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

/*�������﷨�����ӽ��ֵ���������*/
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

void traverse(struct AST *a, int level)//������������﷨��
{
	if (a != NULL)
	{
		for (int i = 1; i < level; i++)//���ӽ����Ը��������2���ո�
		{
			printf("  ");
		}
		printf("%s ", a->name);//��ӡ�﷨��Ԫ���֣�id/intgr/flt/bl/strҪ��ӡyytext��ֵ
		if ((!strcmp(a->name, "id")) || (!strcmp(a->name, "str")) || (!strcmp(a->name, "bl")) || (!strcmp(a->name, "intgr")) || (!strcmp(a->name, "flt")))
		{
			printf(": %s ", a->content);
		}
		else
		{
			printf("(%d)", a->line);
		}
		printf("\n");
		traverse(a->l, level + 1);//����������
		traverse(a->r, level);//����������
	}
}

/*====�������ű�Ľ����Ͳ�ѯ================*/
void newVar(struct AST *a1, struct AST *a2)//�����������ű�
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

int  findVar(struct AST *a)//���ұ����Ƿ��Ѿ����壬�Ƿ���1���񷵻�0
{
	struct VAR *v;
	v = varHead->next;
	while (v != NULL)
	{
		if (!strcmp(v->content, a->content))
		{
			return 1;//���ڷ���1
		}
		v = v->next;
	}
	return 0;//�����ڷ���0
}

/*�����ű�ı���ֵ��ֵ�������﷨����id���*/
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

/*�������﷨����id���ֵ��ֵ�����ű�ı���*/
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

/*�����ű�ĳ�Ա����ֵ��ֵ�������﷨����DOT_expr���*/
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

/*�������﷨����DOT_expr���ֵ��ֵ�����ű�ĳ�Ա����*/
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

/*=====��ǩ����========================*/
/*������ǩ����*/
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

/*���ұ�ǩ�Ƿ��Ѿ�����,�Ƿ���1���񷵻�0*/
int  findLabel(struct AST *a)
{
	struct LABEL *l;
	l = labelHead->next;
	while (l != NULL)
	{
		if (!strcmp(l->labelName, a->content))
		{
			return 1;//���ڷ���1
		}
		l = l->next;
	}
	return 0;//�����ڷ���0
}

/*====��������================*/
/*�����������������Ͳ�ƥ��*/
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



/*��������ļ����������Ƿ���ȷ*/
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

/*�������ļ��еı����Ƿ��Ѷ���*/
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

/*����������ʽ�������Ƿ�ΪBOOL*/
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

void yyerror(char *s, ...) //�䳤������������
{
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "Error at Line %d: ", yylineno);//�����к�
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
	va_end(ap);
	flag = 1;
}

/*��������ͳ����ļ�*/
int varProgCompile()
{
	while (!varProgQueue.empty())
	{
		curVarProg = varProgQueue.front(); //��ǰ��Ҫ����ı����ͳ�������
		varProgQueue.pop();
		varHead = new struct VAR();//�������ű�ͷָ��
		varTail = varHead;//�������ű�βָ��
		struct VAR initialVar = { 0 };
		*varHead = initialVar;
		labelHead = new struct LABEL();//�������ű�ͷָ��
		labelTail = labelHead;//�������ű�βָ��
		struct LABEL initialLabel = { 0 };
		*labelHead = initialLabel;
		flag = 0;
		char *varProgFilePath = new char[strlen(curVarProg) + 10];
		sprintf(varProgFilePath, "%s%s", curVarProg, ".var.prog");
		FILE *varProgFile = fopen(varProgFilePath, "w");
		if (!varProgFile)
		{
			perror("���ļ�ʧ�ܣ�");
			return -1;
		}
		char *varFilePath = new char[projName.size() + strlen(curVarProg) + 40];
		sprintf(varFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\var\\", projName.c_str(), "\\", curVarProg, ".var");
		FILE *varFile = fopen(varFilePath, "r");
		if (!varFile)
		{
			perror("���ļ�ʧ�ܣ�");
			return -1;
		}
		delete[]varFilePath;
		char *progFilePath = new char[projName.size() + strlen(curVarProg) + 40];
		sprintf(progFilePath, "%s%s%s%s%s", ".\\prog_var_xml\\prog\\", projName.c_str(), "\\", curVarProg, ".prog");
		FILE *progFile = fopen(progFilePath, "r");
		if (!progFile)
		{
			perror("���ļ�ʧ�ܣ�");
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
		flag = yyparse() || flag; //flagΪ0ʱ��ʾ����ͨ��������ͨ��
		//�ͷŷ��ű�̬������ڴ棬��ֹ�ڴ�й©
		while (varHead != NULL)
		{
			struct VAR *temp = varHead->next;
			delete varHead;
			varHead = temp;
		}
		//�ͷű�ǩ��̬������ڴ棬��ֹ�ڴ�й©
		while (labelHead != NULL)
		{
			struct LABEL *temp = labelHead->next;
			delete labelHead;
			labelHead = temp;
		}
		fclose(varProgFile);
		remove(varProgFilePath); //ɾ���ļ�
		delete[]varProgFilePath;
	}
	return flag;
}

/*�ͷ������������̬������ڴ棬��ֹ�ڴ�й©*/
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

/*��������µ������ӽ���thisRootָ�����㱾��*/
void setThisRoot(struct AST *a)
{
	if (a != NULL)
	{
		a->thisRoot = rootTail;
		setThisRoot(a->l);
		setThisRoot(a->r);
	}
}

/*����ο�����ϵ����������ϵ�µ�λ��*/
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