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

extern TiXmlDocument doc; //xml配置文件
extern TiXmlElement *rootElem; //xml配置文件根结点
extern TiXmlElement *robot; //当前的机器人
extern vector<const char *> robotNameList; //可用的机器人名称列表
extern const char *robotName; //当前加载的机器人的名称
extern double alpha[6]; //机械臂连杆扭角
extern double a_[6]; //机械臂连杆长度  //为避免与flex中的a冲突
extern double d[6]; //机械臂连杆偏距
extern double offset1[6]; //关节角零点偏移量
extern double maxPos[6]; //各轴正向最大角度
extern double minPos[6]; //各轴负向最大角度
extern double maxVel[6]; //各轴最大速度
extern double maxAcc[6]; //各轴最大加速度
extern double maxDec[6]; //各轴最大减速度
extern double maxJerk[6]; //各轴最大加加速度
extern double offset2[6]; //各轴关节零点相对伺服零点的偏移量
extern double direction[6]; //各轴的运动方向
extern double ratio[6]; //各轴与电机间的减速比
extern double encoder[6]; //各轴电机的编码器分辨率
extern COUPLING coupling; //机器人各轴间的耦合关系
extern DYNAMIC dynamic; //机器人在自动模式下的运动参数
extern DYNAMIC jogSpeed; //机器人在手动模式下示教的运动参数
extern CARTSYS base; //机器人基坐标系
extern CARTSYS tool; //机器人工具坐标系

extern double pulseEquivalent[6]; //每个轴的脉冲当量
extern double averagePulseEquivalent; //六轴的平均脉冲当量
extern double maxSyntheticVel; //轴最大合成速度
extern double maxSyntheticAcc; //轴最大合成加速度
extern double maxSyntheticJerk; //轴最大合成加加速度

//加载机器人配置文件
bool loadRobotConfigFile();
//加载配置文件中与robotName同名的机器人配置
void loadRobotConfig(const char *robotName);
//查找机器人配置xml文件中的元素
bool getElementByName(TiXmlElement *rootElem, const char *destElemName, TiXmlElement **destElem);
//通过xml文件获取机器人各轴的属性值
void getAxisAttribute(TiXmlElement *pElem, double attribute[6]);
//通过xml文件获取机器人运动参数
void getMotionParam(TiXmlElement *pElem, DYNAMIC& dyn);
//通过xml文件获取机器人基坐标系和工具坐标系
void getCoordinate(CARTSYS cartSys, TiXmlElement *pElem);

#endif //RobotConfig_H