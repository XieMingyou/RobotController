#ifndef RobotInstruction_H
#define RobotInstruction_H

#include "dataDeclaration.h"

//机器人初始化
void robotInitial();

//PTP点位运动指令
void PTP_AP(struct AXISPOS pos);
void PTP_CP(struct CARTPOS pos);
void PTP_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void PTP_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//Lin直线运动指令
void Lin_AP(struct AXISPOS pos);
void Lin_CP(struct CARTPOS pos);
void Lin_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void Lin_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//Circ圆弧运动指令
void Circ_AP_AP(struct AXISPOS pos1, struct AXISPOS pos2);
void Circ_AP_CP(struct AXISPOS pos1, struct CARTPOS pos2);
void Circ_CP_AP(struct CARTPOS pos1, struct AXISPOS pos2);
void Circ_CP_CP(struct CARTPOS pos1, struct CARTPOS pos2);
void Circ_AP_AP_DYN(struct AXISPOS pos1, struct AXISPOS pos2, struct DYNAMIC dyn);
void Circ_AP_CP_DYN(struct AXISPOS pos1, struct CARTPOS pos2, struct DYNAMIC dyn);
void Circ_CP_AP_DYN(struct CARTPOS pos1, struct AXISPOS pos2, struct DYNAMIC dyn);
void Circ_CP_CP_DYN(struct CARTPOS pos1, struct CARTPOS pos2, struct DYNAMIC dyn);

//PTP插补相对偏移指令
void PTPRel_AP(struct AXISPOS pos);
void PTPRel_CP(struct CARTPOS pos);
void PTPRel_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void PTPRel_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//Lin插补相对偏移指令StopRobot(
void LinRel_AP(struct AXISPOS pos);
void LinRel_CP(struct CARTPOS pos);
void LinRel_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void LinRel_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//停止机器人运动并且丢弃已经计算好的插补路径,stopMode=0时机器人立即停止，stopMode=1时机器人减速停止
void StopRobot_(int stopMode = 0);

//标定回零位置，针对单一轴。当机器人到达零点后，保存当前机器人轴位置作为该轴的零位,角度单位为°。如果未设置角度参数，则把当前轴位置设为零位。
void RefRobotAxis_(int axis);
void RefRobotAxis_AG(int axis, double angle);
void RefRobotAxis_DYN(int axis, struct DYNAMIC dyn);
void RefRobotAxis_AG_DYN(int axis, double angle, struct DYNAMIC dyn);

//允许多轴同时回零，把当前机器人所有轴位置作为各轴的零位
void RefRobotAxisAsync_();
void RefRobotAxisAsync_DYN(struct DYNAMIC dyn);

//对机器人的单一轴进行运动
void MoveRobotAxis_(int axis, double angle);
void MoveRobotAxis_DYN(int axis, double angle, struct DYNAMIC dyn);

//设置指令组

//设置机器人运动参数
void Dyn_(); 
void Dyn_DYN(struct DYNAMIC dyn, int mode); //mode==0时,将dyn赋值给retDynamic以供后面使用

//设置机器人运动的动态倍率参数
void Dynovr_(int ovr);

//设置速度规划方式，0为S型速度规划（默认），1为梯形速度规划
void Ramp_(int type);

//设置参考系，为后续运行的位置指令设定为一个新的参考坐标系，如果承诺需中没有设定参考坐标系，系统默认草考西为世界坐标系
void Refsys_(struct CARTREFSYS crs);

//设置工具坐标系相对法兰盘的位置
void Tool_(struct CARTSYS cs);

//系统功能指令组

//设置机器人等待时间
void WaitTime_(double duration);

//停止所有激活程序的执行，stopMode==0时机器人立即停止，stopMode==1时机器人减速停止
void Stop_(int stopMode = 0);

//发出一条信息通知,信息显示信息报告栏中
void Notice_(char *text);

//发出一条警告信息
void Warning_(char *text);

//发出一条错误消息
void Error_(char *text);

#endif // !RobotInstruction_H