#ifndef RobotInstruction_H
#define RobotInstruction_H

#include "dataDeclaration.h"

//�����˳�ʼ��
void robotInitial();

//PTP��λ�˶�ָ��
void PTP_AP(struct AXISPOS pos);
void PTP_CP(struct CARTPOS pos);
void PTP_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void PTP_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//Linֱ���˶�ָ��
void Lin_AP(struct AXISPOS pos);
void Lin_CP(struct CARTPOS pos);
void Lin_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void Lin_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//CircԲ���˶�ָ��
void Circ_AP_AP(struct AXISPOS pos1, struct AXISPOS pos2);
void Circ_AP_CP(struct AXISPOS pos1, struct CARTPOS pos2);
void Circ_CP_AP(struct CARTPOS pos1, struct AXISPOS pos2);
void Circ_CP_CP(struct CARTPOS pos1, struct CARTPOS pos2);
void Circ_AP_AP_DYN(struct AXISPOS pos1, struct AXISPOS pos2, struct DYNAMIC dyn);
void Circ_AP_CP_DYN(struct AXISPOS pos1, struct CARTPOS pos2, struct DYNAMIC dyn);
void Circ_CP_AP_DYN(struct CARTPOS pos1, struct AXISPOS pos2, struct DYNAMIC dyn);
void Circ_CP_CP_DYN(struct CARTPOS pos1, struct CARTPOS pos2, struct DYNAMIC dyn);

//PTP�岹���ƫ��ָ��
void PTPRel_AP(struct AXISPOS pos);
void PTPRel_CP(struct CARTPOS pos);
void PTPRel_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void PTPRel_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//Lin�岹���ƫ��ָ��StopRobot(
void LinRel_AP(struct AXISPOS pos);
void LinRel_CP(struct CARTPOS pos);
void LinRel_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn);
void LinRel_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn);

//ֹͣ�������˶����Ҷ����Ѿ�����õĲ岹·��,stopMode=0ʱ����������ֹͣ��stopMode=1ʱ�����˼���ֹͣ
void StopRobot_(int stopMode = 0);

//�궨����λ�ã���Ե�һ�ᡣ�������˵������󣬱��浱ǰ��������λ����Ϊ�������λ,�Ƕȵ�λΪ�㡣���δ���ýǶȲ�������ѵ�ǰ��λ����Ϊ��λ��
void RefRobotAxis_(int axis);
void RefRobotAxis_AG(int axis, double angle);
void RefRobotAxis_DYN(int axis, struct DYNAMIC dyn);
void RefRobotAxis_AG_DYN(int axis, double angle, struct DYNAMIC dyn);

//�������ͬʱ���㣬�ѵ�ǰ������������λ����Ϊ�������λ
void RefRobotAxisAsync_();
void RefRobotAxisAsync_DYN(struct DYNAMIC dyn);

//�Ի����˵ĵ�һ������˶�
void MoveRobotAxis_(int axis, double angle);
void MoveRobotAxis_DYN(int axis, double angle, struct DYNAMIC dyn);

//����ָ����

//���û������˶�����
void Dyn_(); 
void Dyn_DYN(struct DYNAMIC dyn, int mode); //mode==0ʱ,��dyn��ֵ��retDynamic�Թ�����ʹ��

//���û������˶��Ķ�̬���ʲ���
void Dynovr_(int ovr);

//�����ٶȹ滮��ʽ��0ΪS���ٶȹ滮��Ĭ�ϣ���1Ϊ�����ٶȹ滮
void Ramp_(int type);

//���òο�ϵ��Ϊ�������е�λ��ָ���趨Ϊһ���µĲο�����ϵ�������ŵ����û���趨�ο�����ϵ��ϵͳĬ�ϲݿ���Ϊ��������ϵ
void Refsys_(struct CARTREFSYS crs);

//���ù�������ϵ��Է����̵�λ��
void Tool_(struct CARTSYS cs);

//ϵͳ����ָ����

//���û����˵ȴ�ʱ��
void WaitTime_(double duration);

//ֹͣ���м�������ִ�У�stopMode==0ʱ����������ֹͣ��stopMode==1ʱ�����˼���ֹͣ
void Stop_(int stopMode = 0);

//����һ����Ϣ֪ͨ,��Ϣ��ʾ��Ϣ��������
void Notice_(char *text);

//����һ��������Ϣ
void Warning_(char *text);

//����һ��������Ϣ
void Error_(char *text);

#endif // !RobotInstruction_H