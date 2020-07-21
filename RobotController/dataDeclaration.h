#ifndef DataDeclaration_H
#define DataDeclaration_H

#include <vector>
#define PI 3.1415926535
#define PATH_DIFF 0.1  //�岹�ռ�켣�����������������
#define DEVIATION 1e-6 //�������ƫ��
using namespace std;

//����������ؽ�����ϵ�µ�λ������
struct AXISPOS
{
	double a1, a2, a3, a4, a5, a6, aux1, aux2, aux3, aux4, aux5;
};

//����������������ϵ�µ�λ������
struct CARTPOS
{
	double x, y, z, a, b, c, aux1, aux2, aux3, aux4, aux5;
	int mode;
};

//�����˸����������
struct AUXAXISPOS
{
	double aux1, aux2, aux3, aux4, aux5;
};

//�������ŷ������λ������
struct DRIVEPOS
{
	double d1, d2, d3, d4, d5, d6;
};

//ֱ������ϵ
struct CARTSYS
{
	double x, y, z, a, b, c;
};

//ֱ�ǲο�����ϵ
struct CARTREFSYS
{
	char *baseRefSys;
	double x, y, z, a, b, c;

};

//�������˶�����
struct DYNAMIC
{
	double velAxis, accAxis, decAxis, jerkAxis, velPath, accPath, decPath, jerkPath, velOri, accOri, decOri, jerkOri;
};

//ʾ�������͸�������������
extern int emergeStop; //�������Ƿ�ͣ��0��δ��ͣ��1����ͣ
extern int enableState; //������ʹ��״̬��0��δʹ�ܣ�1��ʹ��
extern int operateMode; //�����˲���ģʽ��0���ֶ���1���Զ�
extern int activeState; //����ļ���״̬��0��δ���1������
extern int runState; //���������״̬��0����ͣ��1��������
extern int step; //�����ִ�з�ʽ��0��������1������
extern int jog; //�ֶ�ʾ��ʱ��ѡ����ϵ��0����ؽ�����ϵ��1����������ϵ��2������������ϵ
extern int coordinate; //�ֶ�ʾ��ʱѡ�е����꣬0��δʾ�̣�1-6����x������
extern int upOrDown; //�ֶ�ʾ��ʱ��ѡ�������������С��0����С��1������
extern int ovr; //�������˶������İٷֱ�
extern int progLine; //����ִ�е�������
extern int transferZip; //�Ƿ����ļ�ѹ������0�������䣬1������
extern int zipSize; //ѹ������С
extern string projName; //������������Ŀ������
extern string varProgName; //����������

//���������͸�ʾ����������
extern struct AXISPOS axisPos; //����������ؽ�����ϵ�µ�λ������
extern struct CARTPOS cartPos; //����������������ϵ�µ�λ������
extern struct DRIVEPOS drivePos; //�������ŷ������λ������
extern int activeProg; //�Ƿ񼤻����0����1����
extern int runProg; //�Ƿ����г���0����1����
extern int hasReachSingularity; //�Ƿ񵽴�����˵�����㣬0����1���ǡ����ڿ���ʾ��ʱ����������ֱ������ϵ�µ��������󽫲����ƶ�
extern vector<pair<int, string>> infoReport; //��Ϣ���������

extern struct DYNAMIC curDynamic; //��ǰ�Ļ������˶�����
extern struct DYNAMIC retDynamic; //�������˶�����
extern struct DYNAMIC tmpDynamic; //�ݴ���˶�����
extern int selectDyn; //ѡ��ʹ�õ��˶�������0���ֶ�&��λ��1���ֶ�&�켣��2���Զ�&��λ��3���Զ�&�켣
extern struct CARTSYS curTool; //��ǰ�Ĺ�������ϵ
extern unsigned long contiRunState; //�����˲岹�˶�״̬

#endif //DataDeclaration_H