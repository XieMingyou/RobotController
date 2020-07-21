#ifndef DataDeclaration_H
#define DataDeclaration_H

#include <vector>
#define PI 3.1415926535
#define PATH_DIFF 0.1  //插补空间轨迹上相邻两点的最大距离
#define DEVIATION 1e-6 //距离零的偏差
using namespace std;

//机器人在轴关节坐标系下的位置坐标
struct AXISPOS
{
	double a1, a2, a3, a4, a5, a6, aux1, aux2, aux3, aux4, aux5;
};

//机器人在世界坐标系下的位置坐标
struct CARTPOS
{
	double x, y, z, a, b, c, aux1, aux2, aux3, aux4, aux5;
	int mode;
};

//机器人辅助轴的坐标
struct AUXAXISPOS
{
	double aux1, aux2, aux3, aux4, aux5;
};

//机器人伺服电机的位置坐标
struct DRIVEPOS
{
	double d1, d2, d3, d4, d5, d6;
};

//直角坐标系
struct CARTSYS
{
	double x, y, z, a, b, c;
};

//直角参考坐标系
struct CARTREFSYS
{
	char *baseRefSys;
	double x, y, z, a, b, c;

};

//机器人运动参数
struct DYNAMIC
{
	double velAxis, accAxis, decAxis, jerkAxis, velPath, accPath, decPath, jerkPath, velOri, accOri, decOri, jerkOri;
};

//示教器发送给控制器的数据
extern int emergeStop; //机器人是否急停，0：未急停，1：急停
extern int enableState; //机器人使能状态，0：未使能，1：使能
extern int operateMode; //机器人操作模式，0：手动，1：自动
extern int activeState; //程序的激活状态，0：未激活，1：激活
extern int runState; //程序的运行状态，0：暂停，1：运行中
extern int step; //程序的执行方式，0：连续，1：单步
extern int jog; //手动示教时所选坐标系，0：轴关节坐标系，1：世界坐标系，2：工具手坐标系
extern int coordinate; //手动示教时选中的坐标，0：未示教，1-6：第x个坐标
extern int upOrDown; //手动示教时对选中坐标的增大或减小，0：减小，1：增大
extern int ovr; //相对最大运动参数的百分比
extern int progLine; //程序执行到的行数
extern int transferZip; //是否传输文件压缩包，0：不传输，1：传输
extern int zipSize; //压缩包大小
extern string projName; //主程序所在项目的名称
extern string varProgName; //主程序名称

//控制器发送给示教器的数据
extern struct AXISPOS axisPos; //机器人在轴关节坐标系下的位置坐标
extern struct CARTPOS cartPos; //机器人在世界坐标系下的位置坐标
extern struct DRIVEPOS drivePos; //机器人伺服电机的位置坐标
extern int activeProg; //是否激活程序，0：否，1：是
extern int runProg; //是否运行程序，0：否，1：是
extern int hasReachSingularity; //是否到达机器人的奇异点，0：否，1：是。用于控制示教时，机器人在直角坐标系下到达奇异点后将不再移动
extern vector<pair<int, string>> infoReport; //信息报告的内容

extern struct DYNAMIC curDynamic; //当前的机器人运动参数
extern struct DYNAMIC retDynamic; //保留的运动参数
extern struct DYNAMIC tmpDynamic; //暂存的运动参数
extern int selectDyn; //选择使用的运动参数，0：手动&点位，1：手动&轨迹，2：自动&点位，3：自动&轨迹
extern struct CARTSYS curTool; //当前的工具坐标系
extern unsigned long contiRunState; //机器人插补运动状态

#endif //DataDeclaration_H