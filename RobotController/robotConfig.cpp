#define _CRT_SECURE_NO_WARNINGS
#include "dataDeclaration.h"
#include "robotConfig.h"
#include <string>
#include <iostream>
#include <fstream>

TiXmlDocument doc; //xml�����ļ�
TiXmlElement *rootElem; //xml�����ļ������
TiXmlElement *robot; //��ǰ�Ļ�����
vector<const char *> robotNameList; //���õĻ����������б�
const char *robotName; //��ǰ���صĻ����˵�����
double alpha[6]; //��е������Ť��
double a_[6]; //��е�����˳���  //Ϊ������flex�е�a��ͻ
double d[6]; //��е������ƫ��
double offset1[6]; //�ؽڽ����ƫ����
double maxPos[6]; //�����������Ƕ�
double minPos[6]; //���Ḻ�����Ƕ�
double maxVel[6]; //��������ٶ�
double maxAcc[6]; //���������ٶ�
double maxDec[6]; //���������ٶ�
double maxJerk[6]; //�������Ӽ��ٶ�
double offset2[6]; //����ؽ��������ŷ�����ƫ����
double direction[6]; //������˶�����
double ratio[6]; //����������ļ��ٱ�
double encoder[6]; //�������ı������ֱ���
COUPLING coupling; //�����˸�������Ϲ�ϵ
DYNAMIC dynamic; //���������Զ�ģʽ�µ��˶�����
DYNAMIC jogSpeed; //���������ֶ�ģʽ��ʾ�̵��˶�����
CARTSYS base; //�����˻�����ϵ
CARTSYS tool; //�����˹�������ϵ

double pulseEquivalent[6]; //ÿ��������嵱��
double averagePulseEquivalent; //�����ƽ�����嵱��
double maxSyntheticVel; //�����ϳ��ٶ�
double maxSyntheticAcc; //�����ϳɼ��ٶ�
double maxSyntheticJerk; //�����ϳɼӼ��ٶ�

//���ػ����������ļ�
bool loadRobotConfigFile()
{
	//�ж�RobotConfig.xml�ļ��Ƿ����
	//fstream _file;
	//_file.open("RobotConfig.xml", ios::in);
	//if (!_file)
	//{
	//	cout << "RobotConfig.xml�ļ�������!" << endl;
	//	return false;
	//}
	if (!doc.LoadFile(".//RobotConfig.xml"))
	{
		cout << "���ػ����������ļ�ʧ�ܣ�" << endl;
		return false;
	}
	rootElem = doc.RootElement();
	robot = nullptr;
	//�ҵ������ļ��п��õĻ����ˣ���available����Ϊtrue
	for (robot = rootElem->FirstChildElement(); robot; robot = robot->NextSiblingElement())
	{
		TiXmlElement *baseInfo = robot->FirstChildElement();
		if (!strcmp(baseInfo->Attribute("available"), "true"))
		{
			robotNameList.push_back(robot->Value());
		}
	}
	if (robotNameList.empty())
	{
		cout << "û�п��õĻ���������!" << endl;
		return false;
	}
	//����һ�����õĻ�����������ΪĬ������
	robotName = robotNameList[0];
	//���������ļ�����robotNameͬ���Ļ���������
	loadRobotConfig(robotName);
	doc.SaveFile();
	return true;
}

//���������ļ�����robotNameͬ���Ļ���������
void loadRobotConfig(const char *robotName)
{
	getElementByName(rootElem, robotName, &robot);
	TiXmlElement *pElem = nullptr;
	getElementByName(robot, "alpha", &pElem);
	getAxisAttribute(pElem, alpha);
	getElementByName(robot, "a", &pElem);
	getAxisAttribute(pElem, a_);
	getElementByName(robot, "d", &pElem);
	getAxisAttribute(pElem, d);
	getElementByName(robot, "offset1", &pElem);
	getAxisAttribute(pElem, offset1);
	getElementByName(robot, "maxPos", &pElem);
	getAxisAttribute(pElem, maxPos);
	getElementByName(robot, "minPos", &pElem);
	getAxisAttribute(pElem, minPos);
	getElementByName(robot, "maxVel", &pElem);
	getAxisAttribute(pElem, maxVel);
	getElementByName(robot, "maxAcc", &pElem);
	getAxisAttribute(pElem, maxAcc);
	getElementByName(robot, "maxDec", &pElem);
	getAxisAttribute(pElem, maxDec);
	getElementByName(robot, "maxJerk", &pElem);
	getAxisAttribute(pElem, maxJerk);
	getElementByName(robot, "offset2", &pElem);
	getAxisAttribute(pElem, offset2);
	getElementByName(robot, "direction", &pElem);
	getAxisAttribute(pElem, direction);
	getElementByName(robot, "ratio", &pElem);
	getAxisAttribute(pElem, ratio);
	getElementByName(robot, "encoder", &pElem);
	getAxisAttribute(pElem, encoder);
	getElementByName(robot, "coupling", &pElem);
	coupling.axis4ToAxis5 = atof(pElem->Attribute("axis4ToAxis5"));
	coupling.axis4ToAxis6 = atof(pElem->Attribute("axis4ToAxis6"));
	coupling.axis5ToAxis6 = atof(pElem->Attribute("axis5ToAxis6"));
	getElementByName(robot, "dynamic", &pElem);
	getMotionParam(pElem, dynamic);
	getElementByName(robot, "jogSpeed", &pElem);
	getMotionParam(pElem, jogSpeed);
	getElementByName(robot, "base", &pElem);
	getCoordinate(base, pElem);
	getElementByName(robot, "tool", &pElem);
	getCoordinate(tool, pElem);
	//�����������嵱��
	averagePulseEquivalent = 0;
	for (int i = 0; i < 6; ++i)
	{
		pulseEquivalent[i] = 360 * direction[i] / ratio[i] / encoder[i];
		averagePulseEquivalent += fabs(pulseEquivalent[i]);
	}
	averagePulseEquivalent = averagePulseEquivalent / 6;

	//���ñ��ط����������ϳ��ٶȺ����ϳɼ��ٶ�
	maxSyntheticVel = maxVel[0];
	maxSyntheticAcc = maxAcc[0];
	maxSyntheticJerk = maxJerk[0];
	for (int i = 1; i < 6; i++)
	{
		if (maxSyntheticVel > maxVel[i]) maxSyntheticVel = maxVel[i];
		if (maxSyntheticAcc > maxAcc[i]) maxSyntheticAcc = maxAcc[i];
		if (maxSyntheticJerk > maxJerk[i]) maxSyntheticJerk = maxJerk[i];
	}
}

//���һ���������xml�ļ��е�Ԫ��
bool getElementByName(TiXmlElement *rootElem, const char *destElemName, TiXmlElement **destElem)
{
	//��ε��ڸ��ڵ��򷵻�
	if (0 == strcmp(destElemName, rootElem->Value()))
	{
		*destElem = rootElem;
		return true;
	}

	TiXmlElement *pElem = nullptr;
	for (pElem = rootElem->FirstChildElement(); pElem; pElem = pElem->NextSiblingElement())
	{
		// �ݹ������Ԫ�ط���Ԫ��ָ��
		if (0 != strcmp(destElemName, pElem->Value()))
		{
			getElementByName(pElem, destElemName, destElem);
		}
		else
		{
			*destElem = pElem;
			return true;
		}
	}
	return false;
}

//ͨ��xml�ļ���ȡ�����˸��������ֵ
void getAxisAttribute(TiXmlElement *pElem, double attribute[6])
{
	for (int i = 0; i < 6; i++)
	{
		char axisName[6];
		sprintf(axisName, "%s%d", "axis", i + 1);
		attribute[i] = atof(pElem->Attribute(axisName));
	}
}

//ͨ��xml�ļ���ȡ�������˶�����
void getMotionParam(TiXmlElement *pElem, DYNAMIC& dyn)
{
	dyn.velAxis = atof(pElem->Attribute("velAxis"));
	dyn.accAxis = atof(pElem->Attribute("accAxis"));
	dyn.decAxis = -atof(pElem->Attribute("accAxis"));
	dyn.jerkAxis = atof(pElem->Attribute("jerkAxis"));
	dyn.velPath = atof(pElem->Attribute("velPath"));
	dyn.accPath = atof(pElem->Attribute("accPath"));
	dyn.decPath = -atof(pElem->Attribute("accPath"));
	dyn.jerkPath = atof(pElem->Attribute("jerkPath"));
	dyn.velOri = atof(pElem->Attribute("velOri"));
	dyn.accOri = atof(pElem->Attribute("accOri"));
	dyn.decOri = -atof(pElem->Attribute("accOri"));
	dyn.jerkOri = atof(pElem->Attribute("jerkOri"));
}

//ͨ��xml�ļ���ȡ�����˻�����ϵ�͹�������ϵ
void getCoordinate(CARTSYS cartSys, TiXmlElement *pElem)
{
	cartSys.x = atof(pElem->Attribute("x"));
	cartSys.y = atof(pElem->Attribute("y"));
	cartSys.z = atof(pElem->Attribute("z"));
	cartSys.a = atof(pElem->Attribute("a"));
	cartSys.b = atof(pElem->Attribute("b"));
	cartSys.c = atof(pElem->Attribute("c"));
}