#include "dataDeclaration.h"
#include "IPMCMOTION.h"
# include "semantics.h"
# include "interpreter.h"
# include "robotInstruction.h"
# include "robotConfig.h"
# include <thread>

//机器人运行线程，启动对程序的编译和执行
void compileAndRun()
{
	rootHead = (AST *)malloc(sizeof(AST));//根结点表头指针
	rootTail = rootHead;//根结点表尾指针
	AST initial = { 0 };
	*rootHead = initial;
	char *varProgName = (char*)::varProgName.data();
	varProgQueue.push(varProgName);
	if (!varProgCompile())
	{
		mainProgRoot = rootHead->next;
		//初始化机器人运动参数及设置
		robotInitial();
		//开始执行程序
		progRun(mainProgRoot); //rootTail才是主程序的根结点
		//释放所有结点申请的内存，防止内存泄漏
		while (rootHead != NULL)
		{
			AST *temp = rootHead->next;
			deleteAst(rootHead);
			rootHead = temp;
		}
	}
	else
	{
		printf("编译不通过！");
	}
}

void robotControl()
{
	varProgName = "program1";
	projName = "project1";
	mainProgRoot = nullptr;
	int hasEnable = 0; //判断是否已经上电
	int manual2Auto = 0; //判断是否从手动模式切换为自动模式
	int auto2Manual = 0; //判断是否从自动模式切换为手动模式
	int activeFromInactive = 1; //判断是否从程序未激活状态变为程序激活状态
	int inactiveFromActive = 0; //判断是否从程序激活状态变为程序未激活状态
	int startFromActive = 1; //判断是否从程序激活状态变为程序运行状态
	int startFromStop = 0; //判断是否从程序停止状态变为程序运行状态
	int stopFromStart = 0; //判断是否从程序运行状态变为程序停止状态
	int keepTeach = 0; //判断是否保持点动示教，避免Jog函数的重复调用
	while(true)
	{
		if (emergeStop == 0)
		{
			//设置机器人的动态倍率参数,同时设置运动参数
			Dynovr_(ovr);
			if (operateMode == 1 && manual2Auto == 0)
			{
				curDynamic = tmpDynamic;
				manual2Auto = 1;
				auto2Manual = 0;
			}
			if (operateMode == 0 && auto2Manual == 0)
			{
				tmpDynamic = curDynamic;
				auto2Manual = 1;
				manual2Auto = 0;
			}
			if (enableState == 1)
			{
				if (hasEnable == 0)
				{
					IPMCOpenDevice();
					hasEnable = 1;
				}
				//对程序的执行操作
				//如果是程序加载后、程序终止后、程序修改后，程序还处于未激活状态，此时按“开始”按钮后程序激活
				if (activeState == 1)
				{
					if (mainProgRoot != nullptr)
					{
						mainProgRoot->activeProg = 1;
					}
					inactiveFromActive = 1;
					if (activeFromInactive == 1)
					{
						activeFromInactive = 0;
						unsigned long ulAxisList6[6] = { 0, 1, 2, 3, 4, 5 };
						unsigned long ulMaxACC[6];
						for (int i = 0; i < 6; ++i)
						{
							ulMaxACC[i] = unsigned long(fabs(maxAcc[i] / pulseEquivalent[i] / pow(1000, 2)));
						}
						IPMCContiOpenList(0, 6, ulAxisList6, ulMaxACC); //打开插补缓冲区
						IPMCContiSetLookaheadMode(0, 1, 100, 1); //设置前瞻参数，如果没有是否也可以？
					}
					else if (activeFromInactive == 0)
					{
						//程序激活的状态不变时不作响应
					}
					if (runState == 1)
					{
						if (mainProgRoot != nullptr)
						{
							mainProgRoot->runProg = 1;
						}
						stopFromStart = 1;
						if (startFromActive == 1)
						{
							startFromActive = 0;
							//程序激活状态下，同时程序变为运行状态时，创建机器人运行线程，启动对程序的编译和执行
							thread runThread(compileAndRun);
							runThread.detach();
						}
						else if (startFromActive == 0)
						{
							if (startFromStop == 1)
							{
								startFromStop = 0;
								//程序激活状态下，从程序停止状态变为程序运行状态时恢复机器人的运动和程序的执行
								IPMCContiStartList(0);
							}
							else if (startFromStop == 1)
							{
								//程序激活状态下，程序运行状态不变时不作响应
							}
						}
					}
					else if (runState == 0)
					{
						if (mainProgRoot != nullptr)
						{
							mainProgRoot->runProg = 0;
						}
						startFromStop = 1;
						if (stopFromStart == 1)
						{
							stopFromStart = 0;
							//程序激活状态下，从程序运行状态变为程序停止状态时暂停机器人的运动和程序的执行
							IPMCContiPauseList(0);
						}
						else if (stopFromStart == 0)
						{
							//程序激活状态下，程序停止状态不变时不作响应
						}
					}
				}
				else if (activeState == 0)
				{
					if (mainProgRoot != nullptr)
					{
						mainProgRoot->activeProg = 0;
					}
					activeFromInactive = 1;
					if (inactiveFromActive = 1)
					{
						inactiveFromActive = 0;
						IPMCContiStopList(0, 0);
						IPMCContiCloseList(0);
						IPMCStopAllAxis(0);
					}
					else if (inactiveFromActive = 0)
					{
						//程序未激活的状态不变时不作响应
					}
				}
				//示教操作
				if (operateMode == 0)
				{
					curDynamic = jogSpeed;
					if (coordinate != 0) //开始示教
					{
						if (keepTeach == 0)
						{
							keepTeach = 1;
							if (jog == 1) //轴关节坐标系
							{
								selectDyn = 0;
								Dyn_();
								int dir; //运动方向
								if (upOrDown == 0)
								{
									dir = -1;
								}
								else
								{
									dir = 1;
								}
								IPMCJog(coordinate - 1, dir);
							}
							else if (jog == 2) //世界坐标系
							{
								selectDyn = 1;
								Dyn_();

							}
							else if (jog == 3) //工具坐标系
							{
								selectDyn = 1;
								Dyn_();

							}
						}
					}
					else
					{
						IPMCStopAllAxis(0);
						keepTeach = 0;
					}
				}
			}
			else
			{
				IPMCContiStopList(0, 0);
				IPMCContiCloseList(0);
				IPMCStopAllAxis(0);
				IPMCCloseDevice();
				hasEnable = 0;
			}
		}
		else if (emergeStop == 1)
		{
			IPMCEmergeStop_();
			IPMCCloseDevice();
			return;
		}
	}
}

