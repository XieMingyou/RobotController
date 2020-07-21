#define _CRT_SECURE_NO_WARNINGS
#include "dataDeclaration.h"
#include "robotConfig.h"
#include <string>
#include <iostream>
#include <fstream>

TiXmlDocument doc; //xml配置文件
TiXmlElement *rootElem; //xml配置文件根结点
TiXmlElement *robot; //当前的机器人
vector<const char *> robotNameList; //可用的机器人名称列表
const char *robotName; //当前加载的机器人的名称
double alpha[6]; //机械臂连杆扭角
double a_[6]; //机械臂连杆长度  //为避免与flex中的a冲突
double d[6]; //机械臂连杆偏距
double offset1[6]; //关节角零点偏移量
double maxPos[6]; //各轴正向最大角度
double minPos[6]; //各轴负向最大角度
double maxVel[6]; //各轴最大速度
double maxAcc[6]; //各轴最大加速度
double maxDec[6]; //各轴最大减速度
double maxJerk[6]; //各轴最大加加速度
double offset2[6]; //各轴关节零点相对伺服零点的偏移量
double direction[6]; //各轴的运动方向
double ratio[6]; //各轴与电机间的减速比
double encoder[6]; //各轴电机的编码器分辨率
COUPLING coupling; //机器人各轴间的耦合关系
DYNAMIC dynamic; //机器人在自动模式下的运动参数
DYNAMIC jogSpeed; //机器人在手动模式下示教的运动参数
CARTSYS base; //机器人基坐标系
CARTSYS tool; //机器人工具坐标系

double pulseEquivalent[6]; //每个轴的脉冲当量
double averagePulseEquivalent; //六轴的平均脉冲当量
double maxSyntheticVel; //轴最大合成速度
double maxSyntheticAcc; //轴最大合成加速度
double maxSyntheticJerk; //轴最大合成加加速度

//加载机器人配置文件
bool loadRobotConfigFile()
{
	//判断RobotConfig.xml文件是否存在
	//fstream _file;
	//_file.open("RobotConfig.xml", ios::in);
	//if (!_file)
	//{
	//	cout << "RobotConfig.xml文件不存在!" << endl;
	//	return false;
	//}
	if (!doc.LoadFile(".//RobotConfig.xml"))
	{
		cout << "加载机器人配置文件失败！" << endl;
		return false;
	}
	rootElem = doc.RootElement();
	robot = nullptr;
	//找到配置文件中可用的机器人，其available属性为true
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
		cout << "没有可用的机器人配置!" << endl;
		return false;
	}
	//将第一个可用的机器人配置作为默认配置
	robotName = robotNameList[0];
	//加载配置文件中与robotName同名的机器人配置
	loadRobotConfig(robotName);
	doc.SaveFile();
	return true;
}

//加载配置文件中与robotName同名的机器人配置
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
	//计算各轴的脉冲当量
	averagePulseEquivalent = 0;
	for (int i = 0; i < 6; ++i)
	{
		pulseEquivalent[i] = 360 * direction[i] / ratio[i] / encoder[i];
		averagePulseEquivalent += fabs(pulseEquivalent[i]);
	}
	averagePulseEquivalent = averagePulseEquivalent / 6;

	//采用保守方法计算最大合成速度和最大合成加速度
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

//查找机器人配置xml文件中的元素
bool getElementByName(TiXmlElement *rootElem, const char *destElemName, TiXmlElement **destElem)
{
	//如何等于根节点则返回
	if (0 == strcmp(destElemName, rootElem->Value()))
	{
		*destElem = rootElem;
		return true;
	}

	TiXmlElement *pElem = nullptr;
	for (pElem = rootElem->FirstChildElement(); pElem; pElem = pElem->NextSiblingElement())
	{
		// 递归查找子元素返回元素指针
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

//通过xml文件获取机器人各轴的属性值
void getAxisAttribute(TiXmlElement *pElem, double attribute[6])
{
	for (int i = 0; i < 6; i++)
	{
		char axisName[6];
		sprintf(axisName, "%s%d", "axis", i + 1);
		attribute[i] = atof(pElem->Attribute(axisName));
	}
}

//通过xml文件获取机器人运动参数
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

//通过xml文件获取机器人基坐标系和工具坐标系
void getCoordinate(CARTSYS cartSys, TiXmlElement *pElem)
{
	cartSys.x = atof(pElem->Attribute("x"));
	cartSys.y = atof(pElem->Attribute("y"));
	cartSys.z = atof(pElem->Attribute("z"));
	cartSys.a = atof(pElem->Attribute("a"));
	cartSys.b = atof(pElem->Attribute("b"));
	cartSys.c = atof(pElem->Attribute("c"));
}