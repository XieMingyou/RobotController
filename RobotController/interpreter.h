/*Function:ʵ�ָ�ָ�����Ľ��ͣ������û������˶�����API*/
#include <windows.h>

//�ж��Ƿ�ֹͣ����ֹ����
void progStateCheck(struct AST *a);

//ִ��������Ĵ���
void endStm(struct AST *a);

//���������Ƿ�����˶�,�����˶�ָ��Ų���
void movingCheck(struct AST *a);

//�����ӳ���ĸ����
struct AST *findRoot(char *varProgName);

//��ʼִ�г���
void progRun(struct AST *a);

//�����͹���������hasRun��Ա��1
void changeHasRun(struct AST *a, int num);

//�˶�ָ����
void PTP_interpreter(struct AST *a);
void Lin_interpreter(struct AST *a);
void Circ_interpreter(struct AST *a);
void PTPRel_interpreter(struct AST *a);
void LinRel_interpreter(struct AST *a);
void StopRobot_interpreter(struct AST *a);
void RefRobotAxis_interpreter(struct AST *a);
void RefRobotAxisAsync_interpreter(struct AST *a);
void MoveRobotAxis_interpreter(struct AST *a);

//����ָ����
void Dyn_interpreter(struct AST *a);
void Dynovr_interpreter(struct AST *a);
void Ramp_interpreter(struct AST *a);
void Refsys_interpreter(struct AST *a);
void Tool_interpreter(struct AST *a);

//ϵͳ����ָ����
void WaitTime_interpreter(struct AST *a);
void Stop_interpreter(struct AST *a);
void Notice_interpreter(struct AST *a);
void Warning_interpreter(struct AST *a);
void Error_interpreter(struct AST *a);

//���̿���ָ����
void CALL_interpreter(struct AST *a);
void WAIT_interpreter(struct AST *a);
void IF_interpreter(struct AST *a);
void WHILE_interpreter(struct AST *a);
void LOOP_interpreter(struct AST *a);
void RUN_interpreter(struct AST *a);
void KILL_interpreter(struct AST *a);
void RETURN_interpreter(struct AST *a);
void GOTO_interpreter(struct AST *a);



