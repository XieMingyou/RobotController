#include <string>
#include "robotInstruction.h"
#include "dataDeclaration.h"
#include "tinystr.h"
#include "tinyxml.h"
#include <thread>

//示教器发送给控制器的数据
int emergeStop; //机器人是否急停，0：未急停，1：急停
int enableState; //机器人使能状态，0：未使能，1：使能
int operateMode; //机器人操作模式，0：手动，1：自动
int activeState; //程序的激活状态，0：未激活，1：激活
int runState; //程序的运行状态，0：暂停，1：运行中
int step; //程序的执行方式，0：连续，1：单步
int jog; //手动示教时所选坐标系，0：轴关节坐标系，1：世界坐标系，2：工具手坐标系
int coordinate; //手动示教时选中的坐标，0：未示教，1-6：第x个坐标
int upOrDown; //手动示教时对选中坐标的增大或减小，0：减小，1：增大
int ovr; //相对最大运动参数的百分比
int progLine; //程序执行到的行数
int transferZip; //是否传输文件压缩包，0：不传输，1：传输
int zipSize; //压缩包大小
string projName; //主程序所在项目的名称
string varProgName; //主程序名称

//控制器发送给示教器的数据
struct AXISPOS axisPos; //机器人在轴关节坐标系下的位置坐标
struct CARTPOS cartPos; //机器人在世界坐标系下的位置坐标
struct DRIVEPOS drivePos; //机器人伺服电机的位置坐标
int activeProg; //是否激活程序，0：否，1：是
int runProg; //是否运行程序，0：否，1：是
int hasReachSingularity; //是否到达机器人的奇异点，0：否，1：是。用于控制示教时，机器人在直角坐标系下到达奇异点后将不再移动
vector<pair<int, string>> infoReport; //信息报告的内容

struct DYNAMIC curDynamic; //当前的机器人运动参数
struct DYNAMIC retDynamic; //保留的运动参数
struct DYNAMIC tmpDynamic; //暂存的运动参数
int selectDyn; //选择使用的运动参数，0：手动&点位，1：手动&轨迹，2：自动&点位，3：自动&轨迹
struct CARTSYS curTool; //当前的工具坐标系
unsigned long contiRunState; //机器人插补运动状态


bool loadRobotConfigFile();
void robotInitial();
void dataTransfer();
void robotControl();
void getRobotState();

int main()
{
	//加载机器人配置文件
	if (!loadRobotConfigFile())
	{
		return -1;
	}
	//创建数据传输线程
	thread transferThread(dataTransfer);
	//创建机器人控制线程
	thread controlThread(robotControl);
	//创建读取机器人状态线程
	thread robotStateThread(getRobotState);
	//阻塞主线程
	transferThread.join();
	controlThread.join();
	robotStateThread.join();
	return 0;	
}
