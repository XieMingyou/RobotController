/*Function:�������ű�&����������&��������*/
#ifndef Semantics_H
#define Semantics_H
#include <queue>
#include "dataDeclaration.h"

using namespace std;
extern struct AST *mainProgRoot; //�������Ӧ�����
extern queue<char*> varProgQueue; //��Ҫ����ı����ͳ����ļ�����
extern char *curVarProg; //��ǰ���ڱ���ı����ͳ����ļ�����
extern struct AST *rootHead, *rootTail; //�������ͷָ���βָ��
extern struct VAR *varHead, *varTail; //���ű��ͷָ���βָ��
extern struct LABEL *labelHead, *labelTail; //��ǩ�����ͷָ���βָ��
extern struct CARTSYS worldRefSys; //��������ϵ
extern int flag;//�ı������Ƿ�����ǣ�0��ʾû�д�������ֵ��ʾ�д���

/*�����﷨���Ľ��*/
struct AST
{
	struct AST *l;//���ӽ��
	struct AST *r;//�ֵܽ��
	struct AST *f;//���׽��
	int line; //�к�
	char *name;//�﷨��Ԫ������
	char *content;//�﷨��Ԫ����ֵ(��¼id��intgr��flt��str��bl������)
	char *type;//�﷨��Ԫ��������:��Ҫ���ڲ�������������ƥ���жϣ��������Ͱ�����INTEGER REAL STRING BOOL AXISPOS CARTPOS ROBSXISPOS ROBCARTPOS WORLDREFSYS CARTREFSYS TOOL DYNAMIC
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
	struct AST *next;//�����ָ��
	struct AST *thisRoot; //���ĸ����ָ��
	int activeProg; //�жϸ�����Ӧ�ĳ����Ƿ񱻼��activeProg==0ʱ��ֹ����activeProg==1ʱ�������
	int runProg; //�жϸ�����Ӧ�ĳ����Ƿ�ִ�У�runProg==0ʱֹͣ����runProg==1ʱ��������
	char *varProgName; //���ڼ�¼������Ӧ�ı����ͳ����ļ�
	int hasRun;//�ж�����Ƿ��Ѿ�����
};

/*�������ű�Ľ��*/
struct VAR
{
	char *content;//������
	char *type;//��������
	int intgr;
	double flt;
	char *str;
	bool bl;
	struct AXISPOS axisPos;
	struct CARTPOS cartPos;
	struct CARTSYS cartSys;
	struct CARTREFSYS cartRefSys;
	struct DYNAMIC dynamic;
	struct VAR *next;//ָ��
};

struct LABEL
{
	char *labelName; //��ǩ��
	struct LABEL *next; //����ָ��
};

/*=====�����﷨��========================*/
/*��������﷨��,�䳤������name:�﷨��Ԫ���֣�num:�䳤�������﷨������*/
struct AST *newAst(char *name, int num, ...);

/*�������﷨�����ӽ��ֵ���������*/
void ast2ast(struct AST *a1, struct AST *a2);

/*���������﷨����levelΪ���Ĳ���*/
void traverse(struct AST*, int level);

/*=====�������ű�========================*/
/*�����������ű�*/
void newVar(struct AST*, struct AST*);

/*���ұ����Ƿ��Ѿ�����,�Ƿ���1���񷵻�0*/
int  findVar(struct AST *a);

/*���ұ�������*/
char *typeVar(struct VAR *a);

/*�����ű�ı���ֵ��ֵ�������﷨����id���*/
void var2ast(struct AST *a);

/*�������﷨����id���ֵ��ֵ�����ű�ı���*/
void ast2var(struct AST *a);

/*�����ű�ĳ�Ա����ֵ��ֵ�������﷨����DOT_expr���*/
void dot_var2ast(struct AST *a1, struct AST *a2, struct AST *a3);

/*�������﷨����DOT_expr���ֵ��ֵ�����ű�ĳ�Ա����*/
void dot_ast2var(struct AST *a1, struct AST *a2, struct AST *a3);

/*=====��ǩ����========================*/
/*������ǩ����*/
void newLabel(struct AST *a);

/*���ұ�ǩ�Ƿ��Ѿ�����,�Ƿ���1���񷵻�0*/
int  findLabel(struct AST *a);

/*====��������================*/
/*���������������������Ƿ�ƥ��*/
void assignment(struct AST *a1, struct AST *a2);
void logical(struct AST *a1, struct AST *a2, struct AST *a3, struct AST *a4);
void arithmetic(struct AST *a1, struct AST *a2, struct AST *a3, struct AST *a4);
void minusOperator(struct AST *a1, struct AST *a2);
void notOperator(struct AST *a1, struct AST *a2);

/*��������ļ����������Ƿ���ȷ*/
void defTypeError(struct AST *a1, struct AST *a2);

/*�������ļ��еı����Ƿ��Ѷ���*/
void existVar(struct AST *a);

/*����������ʽ�������Ƿ�ΪBOOL*/
void isBool(struct AST *a);

/*������������*/
void yyerror(char *s, ...);

/*��������ͳ����ļ�*/
int varProgCompile();

/*�ͷ������������̬������ڴ棬��ֹ�ڴ�й©*/
void deleteAst(struct AST *a);

/*��������µ������ӽ���thisRootָ�����㱾��*/
void setThisRoot(struct AST *a);

/*����ο�����ϵ����������ϵ�µ�λ��*/
void calculateCartSys(struct AST *a1, struct AST *a2);

#endif // Semantics_H