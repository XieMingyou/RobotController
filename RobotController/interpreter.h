/*Function:实现各指令语句的解释，并调用机器人运动控制API*/
#include <windows.h>

//判断是否停止或终止程序
void progStateCheck(struct AST *a);

//执行完语句后的处理
void endStm(struct AST *a);

//检测机器人是否完成运动,对于运动指令才插入
void movingCheck(struct AST *a);

//查找子程序的根结点
struct AST *findRoot(char *varProgName);

//开始执行程序
void progRun(struct AST *a);

//将解释过的语句结点的hasRun成员置1
void changeHasRun(struct AST *a, int num);

//运动指令组
void PTP_interpreter(struct AST *a);
void Lin_interpreter(struct AST *a);
void Circ_interpreter(struct AST *a);
void PTPRel_interpreter(struct AST *a);
void LinRel_interpreter(struct AST *a);
void StopRobot_interpreter(struct AST *a);
void RefRobotAxis_interpreter(struct AST *a);
void RefRobotAxisAsync_interpreter(struct AST *a);
void MoveRobotAxis_interpreter(struct AST *a);

//设置指令组
void Dyn_interpreter(struct AST *a);
void Dynovr_interpreter(struct AST *a);
void Ramp_interpreter(struct AST *a);
void Refsys_interpreter(struct AST *a);
void Tool_interpreter(struct AST *a);

//系统功能指令组
void WaitTime_interpreter(struct AST *a);
void Stop_interpreter(struct AST *a);
void Notice_interpreter(struct AST *a);
void Warning_interpreter(struct AST *a);
void Error_interpreter(struct AST *a);

//流程控制指令组
void CALL_interpreter(struct AST *a);
void WAIT_interpreter(struct AST *a);
void IF_interpreter(struct AST *a);
void WHILE_interpreter(struct AST *a);
void LOOP_interpreter(struct AST *a);
void RUN_interpreter(struct AST *a);
void KILL_interpreter(struct AST *a);
void RETURN_interpreter(struct AST *a);
void GOTO_interpreter(struct AST *a);



