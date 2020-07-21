#ifndef RobotConfig_H
#define RobotConfig_H

#include "tinystr.h"
#include "tinyxml.h"
#include <vector>


struct COUPLING
{
	double axis4ToAxis5;
	double axis4ToAxis6;
	double axis5ToAxis6;
};

extern TiXmlDocument doc; //xml�����ļ�
extern TiXmlElement *rootElem; //xml�����ļ������
extern TiXmlElement *robot; //��ǰ�Ļ�����
extern vector<const char *> robotNameList; //���õĻ����������б�
extern const char *robotName; //��ǰ���صĻ����˵�����
extern double alpha[6]; //��е������Ť��
extern double a_[6]; //��е�����˳���  //Ϊ������flex�е�a��ͻ
extern double d[6]; //��е������ƫ��
extern double offset1[6]; //�ؽڽ����ƫ����
extern double maxPos[6]; //�����������Ƕ�
extern double minPos[6]; //���Ḻ�����Ƕ�
extern double maxVel[6]; //��������ٶ�
extern double maxAcc[6]; //���������ٶ�
extern double maxDec[6]; //���������ٶ�
extern double maxJerk[6]; //�������Ӽ��ٶ�
extern double offset2[6]; //����ؽ��������ŷ�����ƫ����
extern double direction[6]; //������˶�����
extern double ratio[6]; //����������ļ��ٱ�
extern double encoder[6]; //�������ı������ֱ���
extern COUPLING coupling; //�����˸�������Ϲ�ϵ
extern DYNAMIC dynamic; //���������Զ�ģʽ�µ��˶�����
extern DYNAMIC jogSpeed; //���������ֶ�ģʽ��ʾ�̵��˶�����
extern CARTSYS base; //�����˻�����ϵ
extern CARTSYS tool; //�����˹�������ϵ

extern double pulseEquivalent[6]; //ÿ��������嵱��
extern double averagePulseEquivalent; //�����ƽ�����嵱��
extern double maxSyntheticVel; //�����ϳ��ٶ�
extern double maxSyntheticAcc; //�����ϳɼ��ٶ�
extern double maxSyntheticJerk; //�����ϳɼӼ��ٶ�

//���ػ����������ļ�
bool loadRobotConfigFile();
//���������ļ�����robotNameͬ���Ļ���������
void loadRobotConfig(const char *robotName);
//���һ���������xml�ļ��е�Ԫ��
bool getElementByName(TiXmlElement *rootElem, const char *destElemName, TiXmlElement **destElem);
//ͨ��xml�ļ���ȡ�����˸��������ֵ
void getAxisAttribute(TiXmlElement *pElem, double attribute[6]);
//ͨ��xml�ļ���ȡ�������˶�����
void getMotionParam(TiXmlElement *pElem, DYNAMIC& dyn);
//ͨ��xml�ļ���ȡ�����˻�����ϵ�͹�������ϵ
void getCoordinate(CARTSYS cartSys, TiXmlElement *pElem);

#endif //RobotConfig_H