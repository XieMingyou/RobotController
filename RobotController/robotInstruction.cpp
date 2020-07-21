#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include "robotInstruction.h"
#include "robotConfig.h"
#include "dataDeclaration.h"
#include "robotConfig.h"
#include "robotAlgorithm.h"
#include "IPMCMOTION.h"
#include <Windows.h>

int callFlag = 0; //���ñ�־���ж�ĳ��ָ���Ƿ񱻵�ָ��һָ�����

//�����˳�ʼ��
void robotInitial()
{
	for (int i = 0; i < 6; ++i)
	{
		//���������λ
		IPMCSetAxisSoftLimit(i, 0, (maxPos[i] + offset2[i]) / pulseEquivalent[i], (minPos[i] + offset2[i]) / pulseEquivalent[i]);
		IPMCEnableSoftlimit(i, 1);
		//�������λ��ģʽ
		IPMCSetAxisPositionMode(i, 1); //Ĭ��Ϊ����λ��ģʽ
		////�����ٶ�����T/S
		//IPMCSetAxisVProfile(i, 0); //Ĭ��ΪS�ٶ�����
		////����������ٶȺͼ��ٶ�����
		//IPMCSetAxisVMaxParams(i, maxVel[i] / pulseEquivalent[i] / 1000, maxAcc[i] / pulseEquivalent[i] / pow(1000, 2));
	}
	//����岹����ٶȺͼ��ٶ�����
	//IPMCSetInterpolationMaxParams(maxSyntheticVel / averagePulseEquivalent / 1000, maxSyntheticAcc / averagePulseEquivalent / pow(1000, 2));
	//���û������˶���̬���ʲ���Ĭ��ֵ
	ovr = 20;
	//����Ĭ�ϵĻ������˶�����
	retDynamic = dynamic;
	tmpDynamic = dynamic;
	if (operateMode == 0)
	{
		curDynamic = jogSpeed;
	}
	else if (operateMode == 1)
	{
		curDynamic = retDynamic;
	}
	Dyn_();
	//��Ĭ�ϵ�tool��ֵ����ǰ��������ϵ
	Tool_(tool);
}

//����λ�õ����ͺ��Ƿ�����dynamic�������˶�ָ���м��ֲ�ͬ����ʽ
void PTP_AP(struct AXISPOS pos)
{
	if (callFlag == 0)
	{
		if (operateMode == 0)
		{
			selectDyn = 0;
		}
		else if (operateMode == 1)
		{
			selectDyn = 2;
		}
		Dyn_();
	}
	unsigned long ulAxisList[6] = { 0, 1, 2, 3, 4, 5 };
	long lTargetPos[6] = { (pos.a1 + offset2[0]) / pulseEquivalent[0], (pos.a2 + offset2[1]) / pulseEquivalent[1], (pos.a3 + offset2[2]) / pulseEquivalent[2],   \
		(pos.a4 + offset2[3]) / pulseEquivalent[3], (pos.a5 + offset2[4]) / pulseEquivalent[4], (pos.a6 + offset2[5]) / pulseEquivalent[5] };
	IPMCContiLineUnit(0, 6, ulAxisList, lTargetPos, 1, 0);
	IPMCContiStartList(0);
}
void PTP_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	PTP_AP(pos);
	callFlag = 0;
}
void PTP_CP(struct CARTPOS pos)
{
	struct AXISPOS desAxisPos = inverseKinematics(pos, axisPos);
	PTP_AP(desAxisPos);
}
void PTP_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	PTP_CP(pos);
	callFlag = 0;
}

void Lin_AP(struct AXISPOS pos)
{
	struct CARTPOS desCartPos = forwardKinematics(pos);
	Lin_CP(desCartPos);
}
void Lin_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	Lin_AP(pos);
	callFlag = 0;
}
void Lin_CP(struct CARTPOS pos)
{
	if (callFlag == 0)
	{
		if (operateMode == 0)
		{
			selectDyn = 1;
		}
		else if (operateMode == 1)
		{
			selectDyn = 3;
		}
		Dyn_();
	}
	double L = sqrt(pow(pos.x - cartPos.x, 2) + pow(pos.y - cartPos.y, 2) + pow(pos.z - cartPos.z, 2));
	int N = int(L / PATH_DIFF) + 1;
	//����λ������
	double diff[6];
	diff[0] = (pos.x - cartPos.x) / N; diff[1] = (pos.y - cartPos.y) / N; diff[2] = (pos.z - cartPos.z) / N;
	diff[3] = (pos.a - cartPos.a) / N; diff[4] = (pos.b - cartPos.b) / N; diff[5] = (pos.c - cartPos.c) / N;
	struct AXISPOS newAxisPos = axisPos, desAxisPos;
	struct CARTPOS newCartPos = cartPos, desCartPos;
	for (int i = 0; i < N; i++)
	{
		desCartPos.x = newCartPos.x + (i + 1) * diff[0];
		desCartPos.y = newCartPos.y + (i + 1) * diff[1];
		desCartPos.z = newCartPos.z + (i + 1) * diff[2];
		desCartPos.a = newCartPos.a + (i + 1) * diff[3];
		desCartPos.b = newCartPos.b + (i + 1) * diff[4];
		desCartPos.c = newCartPos.c + (i + 1) * diff[5];
		desAxisPos = inverseKinematics(desCartPos, newAxisPos);
		unsigned long ulAxisList[6] = { 0, 1, 2, 3, 4, 5 };
		long lTargetPos[6] = { (desAxisPos.a1 + offset2[0]) / pulseEquivalent[0], (desAxisPos.a2 + offset2[1]) / pulseEquivalent[1], (desAxisPos.a3 + offset2[2]) / pulseEquivalent[2],   \
			(desAxisPos.a4 + offset2[3]) / pulseEquivalent[3], (desAxisPos.a5 + offset2[4]) / pulseEquivalent[4], (desAxisPos.a6 + offset2[5]) / pulseEquivalent[5] };
		IPMCContiLineUnit(0, 6, ulAxisList, lTargetPos, 1, 0);
		newAxisPos = desAxisPos;
	}
	IPMCContiStartList(0);
}
void Lin_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	Lin_CP(pos);
	callFlag = 0;
}

void Circ_AP_AP(struct AXISPOS pos1, struct AXISPOS pos2)
{
	struct CARTPOS desCartPos1 = forwardKinematics(pos1);
	struct CARTPOS desCartPos2 = forwardKinematics(pos2);
	Circ_CP_CP(desCartPos1, desCartPos2);
}
void Circ_AP_CP(struct AXISPOS pos1, struct CARTPOS pos2)
{
	struct CARTPOS desCartPos1 = forwardKinematics(pos1);
	Circ_CP_CP(desCartPos1, pos2);
}
void Circ_CP_AP(struct CARTPOS pos1, struct AXISPOS pos2)
{
	struct CARTPOS desCartPos2 = forwardKinematics(pos2);
	Circ_CP_CP(pos1, desCartPos2);
}
void Circ_CP_CP(struct CARTPOS pos1, struct CARTPOS pos2)
{
	//if (callFlag == 0)
	//{
	//	if (operateMode == 0)
	//	{
	//		selectDyn = 0;
	//	}
	//	else if (operateMode == 1)
	//	{
	//		selectDyn = 2;
	//	}
	//	Dyn_();
	//}
	//struct CARTPOS newCartPos = cartPos;
	//
	////��֪�ռ�����������P1(x1,y1,z1) P2(x2,y2,z2) P3(x3,y3,z3)
	//double x1 = newCartPos.x; double y1 = newCartPos.y; double z1 = newCartPos.z;
	//double x2 = pos1.x; double y2 = pos1.y; double z2 = pos1.z;
	//double x3 = pos2.x; double y3 = pos2.y; double z3 = pos2.z;

	////�ж��Ƿ����ĳ�����غϵ����
	//if ((fabs(x2 - x1) < DEVIATION && fabs(y2 - y1) < DEVIATION && fabs(z2 - z1) < DEVIATION) || \
	//	(fabs(x3 - x1) < DEVIATION && fabs(y3 - y1) < DEVIATION && fabs(z3 - z1) < DEVIATION) || \
	//	(fabs(x3 - x2) < DEVIATION && fabs(y3 - y2) < DEVIATION && fabs(z3 - z2) < DEVIATION))
	//{
	//	cout << "�켣��������Բ����㡢�����㡢�յ��غϵ������" << endl;
	//	return;
	//}
	////�ж��Ƿ�������㹲�ߵ����
	//if ((fabs(x2 - x1) / fabs(y2 - y1) - fabs(x3 - x2) / fabs(y3 - y2) < DEVIATION) && \
	//	(fabs(y2 - y1) / fabs(z2 - z1) - fabs(y3 - y2) / fabs(z3 - z2) < DEVIATION))
	//{
	//	cout << "�켣��������Բ����㡢�����㡢�յ㹲�ߵ������" << endl;
	//	return;
	//}
	//
	////����ռ�����P1 P2 P3����Բ����Բ������P0(x0,y0,z0)
	//double aa1 = x2 - x1;
	//double aa2 = x3 - x2;
	//double aa3 = x3 - x1;
	//double bb1 = y2 - y1;
	//double bb2 = y3 - y2;
	//double bb3 = y3 - y1;
	//double cc1 = z2 - z1;
	//double cc2 = z3 - z2;
	//double cc3 = z3 - z1;
	//double dd1 = ((y1 - y3)*(z2 - z3) - (y2 - y3)*(z1 - z3))*x3 + ((x2 - x3)*(z1 - z3) - (x1 - x3)*(z2 - z3))*y3 + ((x1 - x3)*(y2 - y3) - (x2 - x3)*(y1 - y3))*z3;
	//double dd2 = (0.5)*(x1 + x2)*(x2 - x1) + (0.5)*(y1 + y2)*(y2 - y1) + (0.5)*(z1 + z2)*(z2 - z1);
	//double dd3 = (0.5)*(x2 + x3)*(x3 - x2) + (0.5)*(y2 + y3)*(y3 - y2) + (0.5)*(z2 + z3)*(z3 - z2);
	//double ee1 = bb3 * cc2 - bb2 * cc3;
	//double ee2 = aa2 * cc3 - aa3 * cc2;
	//double ee3 = aa3 * bb2 - aa2 * bb3;

	////Բ������(x0,y0,z0)
	//double x0 = (bb1*cc2 - cc1 * bb2) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd1 + (-ee2 * cc2 + ee3 * bb2) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd2 - (-ee2 * cc1 + ee3 * bb1) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd3;
	//double y0 = -(aa1*cc2 - cc1 * aa2) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd1 - (-ee1 * cc2 + ee3 * aa2) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd2 + (-ee1 * cc1 + ee3 * aa1) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd3;
	//double z0 = (aa1*bb2 - bb1 * aa2) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd1 - (ee1*bb2 - ee2 * aa2) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd2 - (-ee1 * bb1 + ee2 * aa1) / (ee1*bb1*cc2 - ee1 * cc1*bb2 - aa1 * ee2*cc2 + aa1 * ee3*bb2 + aa2 * ee2*cc1 - aa2 * ee3*bb1)*dd3;

	//// Բ���뾶Radius
	//double Radius = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) + (z1 - z0) * (z1 - z0));

	////��P0P1Ϊ������ϵ��UX��
	//double ux = (x1 - x0) / sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0) + (z1 - z0)*(z1 - z0));
	//double uy = (y1 - y0) / sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0) + (z1 - z0)*(z1 - z0));
	//double uz = (z1 - z0) / sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0) + (z1 - z0)*(z1 - z0));

	////ȡ��ֱ��P1P2��P2P3��������ƽ��ķ���ΪWX��
	//double wx = ((y1 - y3)*(z2 - z3) - (y2 - y3)*(z1 - z3)) / sqrt((-(y1 - y3)*(z2 - z3) + (y2 - y3)*(z1 - z3))*(-(y1 - y3)*(z2 - z3) + (y2 - y3)*(z1 - z3)) + (-(x2 - x3)*(z1 - z3) + (x1 - x3)*(z2 - z3))*(-(x2 - x3)*(z1 - z3) + (x1 - x3)*(z2 - z3)) + (-(x1 - x3)*(y2 - y3) + (x2 - x3)*(y1 - y3))*(-(x1 - x3)*(y2 - y3) + (x2 - x3)*(y1 - y3)));
	//double wy = ((x2 - x3)*(z1 - z3) - (x1 - x3)*(z2 - z3)) / sqrt((-(y1 - y3)*(z2 - z3) + (y2 - y3)*(z1 - z3))*(-(y1 - y3)*(z2 - z3) + (y2 - y3)*(z1 - z3)) + (-(x2 - x3)*(z1 - z3) + (x1 - x3)*(z2 - z3))*(-(x2 - x3)*(z1 - z3) + (x1 - x3)*(z2 - z3)) + (-(x1 - x3)*(y2 - y3) + (x2 - x3)*(y1 - y3))*(-(x1 - x3)*(y2 - y3) + (x2 - x3)*(y1 - y3)));
	//double wz = ((x1 - x3)*(y2 - y3) - (x2 - x3)*(y1 - y3)) / sqrt((-(y1 - y3)*(z2 - z3) + (y2 - y3)*(z1 - z3))*(-(y1 - y3)*(z2 - z3) + (y2 - y3)*(z1 - z3)) + (-(x2 - x3)*(z1 - z3) + (x1 - x3)*(z2 - z3))*(-(x2 - x3)*(z1 - z3) + (x1 - x3)*(z2 - z3)) + (-(x1 - x3)*(y2 - y3) + (x2 - x3)*(y1 - y3))*(-(x1 - x3)*(y2 - y3) + (x2 - x3)*(y1 - y3)));

	//double ax1_1 = wx;
	//double ay1_1 = wy;
	//double az1_1 = wz;

	////����ѡ��Ӷ�ʹ��ֱƽ�����ϵķ���Ϊ��������
	//double ax1, ay1, az1;
	//if (az1_1 >= 0)
	//{
	//	ax1 = ax1_1;
	//	ay1 = ay1_1;
	//	az1 = az1_1;
	//}
	//else
	//{
	//	ax1 = -ax1_1;
	//	ay1 = -ay1_1;
	//	az1 = -az1_1;
	//}

	////������ϵ�µ�VX�᷽������ΪU����W��Ĳ�� 

	//double vx = uy * az1 - uz * ay1;
	//double vy = uz * ax1 - ux * az1;
	//double vz = ux * ay1 - uy * ax1;
	////P1 P2 P3��������ϵ�µ�����ΪP11(P1x,P1y,P1z) P21(P2x,P2y,P2z) P31(P3x,P3y,P3z)
	////�任����Tr= [ux vx ax1 x0;uy vy ay1 y0;uz vz az1 z0;0 0 0 1]  //Tr= [ux vx wx x0;uy vy wy y0;uz vz wz z0;0 0 0 1]

	//double P1x = (vy*az1 - vz * ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x1 - (vx*az1 - vz * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y1 + (vx*ay1 - vy * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z1 - (vx*ay1*z0 - vx * y0*az1 - vy * ax1*z0 + vy * x0*az1 + vz * ax1*y0 - vz * x0*ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);
	//double P1y = -(uy*az1 - uz * ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x1 + (ux*az1 - uz * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y1 - (ux*ay1 - uy * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z1 + (ux*ay1*z0 - ux * y0*az1 - uy * ax1*z0 + uy * x0*az1 + uz * ax1*y0 - uz * x0*ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);
	//double P1z = (uy*vz - uz * vy) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x1 - (ux*vz - uz * vx) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y1 + (ux*vy - uy * vx) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z1 - (ux*vy*z0 - ux * y0*vz - uy * vx*z0 + uy * x0*vz + uz * vx*y0 - uz * x0*vy) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);

	//double P2x = (vy*az1 - vz * ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x2 - (vx*az1 - vz * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y2 + (vx*ay1 - vy * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z2 - (vx*ay1*z0 - vx * y0*az1 - vy * ax1*z0 + vy * x0*az1 + vz * ax1*y0 - vz * x0*ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);
	//double P2y = -(uy*az1 - uz * ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x2 + (ux*az1 - uz * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y2 - (ux*ay1 - uy * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z2 + (ux*ay1*z0 - ux * y0*az1 - uy * ax1*z0 + uy * x0*az1 + uz * ax1*y0 - uz * x0*ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);
	//double P2z = (uy*vz - uz * vy) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x2 - (ux*vz - uz * vx) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y2 + (ux*vy - uy * vx) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z2 - (ux*vy*z0 - ux * y0*vz - uy * vx*z0 + uy * x0*vz + uz * vx*y0 - uz * x0*vy) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);

	//double P3x = (vy*az1 - vz * ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x3 - (vx*az1 - vz * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y3 + (vx*ay1 - vy * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z3 - (vx*ay1*z0 - vx * y0*az1 - vy * ax1*z0 + vy * x0*az1 + vz * ax1*y0 - vz * x0*ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);
	//double P3y = -(uy*az1 - uz * ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x3 + (ux*az1 - uz * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y3 - (ux*ay1 - uy * ax1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z3 + (ux*ay1*z0 - ux * y0*az1 - uy * ax1*z0 + uy * x0*az1 + uz * ax1*y0 - uz * x0*ay1) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);
	//double P3z = (uy*vz - uz * vy) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*x3 - (ux*vz - uz * vx) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*y3 + (ux*vy - uy * vx) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1)*z3 - (ux*vy*z0 - ux * y0*vz - uy * vx*z0 + uy * x0*vz + uz * vx*y0 - uz * x0*vy) / (ux*vy*az1 - ux * vz*ay1 - uy * vx*az1 + uy * vz*ax1 + uz * vx*ay1 - uz * vy*ax1);

	////Բ����P0P1��P0P2֮��ļн�ΪangleP2
	////����P1P2֮�����LDis2
	//double LDis2 = fabs(CRMath::PreRead_sqrtr((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1)));//��λmm
	//double angleP2 = 2.0*(asin(LDis2 / (2.0*Radius))*Rad2Deg);//��ʱ����ĽǶ�ֵΪ�ӻ���Ӧ�ĽǶ�<180��

	////Բ����P0P1��P0P3֮��ļн�ΪangleP3
	////����P1P3֮�����LDis3
	//double LDis3 = fabs(CRMath::PreRead_sqrtr((x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1) + (z3 - z1)*(z3 - z1)));//��λmm
	//double angleP3 = 2.0*(asin(LDis3 / (2.0*Radius))*Rad2Deg);//��ʱ����ĽǶ�ֵΪ�ӻ���Ӧ�ĽǶ�<180��

	////��P1��P3��P2�ĽǶȴ�С
	//double angle;

	//if (0 <= P2y && 0 <= P3y || 0 > P2y && 0 > P3y)//�ж������Ƕ��Ƿ�ͬ��
	//{
	//	if (angleP2 > angleP3)
	//	{
	//		angle = angleP2;
	//	}
	//	else
	//	{
	//		angle = 360 - angleP2;
	//	}
	//}
	//else
	//{
	//	angle = 360 - angleP2;
	//}

	////�ȽǶȲ岹

	//double ArcLength = m_step;  //�����������õĲ���
	//double Incangle = 180.0*ArcLength / (PI*Radius);

	//Arc_SegNum = (int)abs(angle / Incangle);

	//double T_total = (angle*PI*Radius / 180.0) / EndPoint.Interpo_Jog_Home_Vel;   //�ö�������ʱ��
	//double T_segment = ArcLength / EndPoint.Interpo_Jog_Home_Vel;  //С�߶�����ʱ��
	//double T_end;
	//double step_RZ;
	//if (Arc_SegNum < 2)
	//{
	//	T_end = T_total;   //ĩ������ʱ��
	//}
	//else
	//{
	//	T_end = T_total - (Arc_SegNum - 1)*T_segment;   //ĩ������ʱ��
	//	step_RZ = (finish_RZ - start_RZ) / Arc_SegNum;
	//}

	//double newangle = 0.0;//Բ���켣�ϵ�ǰ��ĽǶ�ֵ


	////ѭ���岹
	//for (int n = 0; n < Arc_SegNum - 1; n++)
	//{
	//	newangle += Incangle;

	//	//���㵱ǰ����������ϵ�µ�����Pnew(xnew,ynew,znew)
	//	double xnew, ynew, znew;

	//	if (angle < 180)//ȷ��ת�ǵķ���
	//	{
	//		if (P2y > 0)
	//		{
	//			xnew = Radius * cos(newangle*Deg2Rad);
	//			ynew = Radius * sin(newangle*Deg2Rad);

	//		}
	//		else
	//		{
	//			xnew = Radius * cos(-newangle * Deg2Rad);
	//			ynew = Radius * sin(-newangle * Deg2Rad);
	//		}
	//	}
	//	else if (angle == 180)
	//	{
	//		if (P3y > 0)
	//		{
	//			xnew = Radius * cos(newangle*Deg2Rad);
	//			ynew = Radius * sin(newangle*Deg2Rad);

	//		}
	//		else
	//		{
	//			xnew = Radius * cos(-newangle * Deg2Rad);
	//			ynew = Radius * sin(-newangle * Deg2Rad);
	//		}
	//	}
	//	else
	//	{
	//		if (P2y > 0)
	//		{
	//			xnew = Radius * cos(-newangle * Deg2Rad);
	//			ynew = Radius * sin(-newangle * Deg2Rad);

	//		}
	//		else
	//		{
	//			xnew = Radius * cos(newangle*Deg2Rad);
	//			ynew = Radius * sin(newangle*Deg2Rad);
	//		}
	//	}

	//	znew = 0.0;

	//	//����Pnew��ԭ����ϵ�е�����ֵPbase(xbase,ybase,zbase)
	//	double xbase = ux * xnew + vx * ynew + wx * znew + x0;
	//	double ybase = uy * xnew + vy * ynew + wy * znew + y0;
	//	double zbase = uz * xnew + vz * ynew + wz * znew + z0;
	//	start_RZ = start_RZ + step_RZ;


	//	//����ͼ�νⷨ
	//	double A = ((m_BigArmLength*m_BigArmLength - m_SmallArmLength * m_SmallArmLength + xbase * xbase + ybase * ybase) / (2 * m_BigArmLength*CRMath::PreRead_sqrtr(xbase*xbase + ybase * ybase)));
	//	if ((A - 1) > 0 && (A - 1) < 5e-5)
	//	{
	//		A = 1;
	//	}
	//	A = acos(A);
	//	double B = atan2(ybase, xbase);
	//	double C = ((m_BigArmLength*m_BigArmLength + m_SmallArmLength * m_SmallArmLength - xbase * xbase - ybase * ybase) / (2 * m_BigArmLength*m_SmallArmLength));
	//	if (C - (-1) < 0 && (-5e-5) < C - (-1))
	//	{
	//		C = -1;
	//	}
	//	C = acos(C);

	//	double angle1;
	//	double angle2;

	//	if (StartPoint.config == LEFTY)
	//	{
	//		angle1 = (B + A)*Rad2Deg;
	//		angle2 = (C - PI)*Rad2Deg;
	//	}
	//	else /*if(StartPoint.config == RIGHTY)*/
	//	{
	//		angle1 = (B - A)*Rad2Deg;
	//		angle2 = (PI - C)*Rad2Deg;
	//	}
	//	//else
	//	//{
	//	//	if (EndPoint.config==LEFTY)
	//	//	{
	//	//		angle1=(B+A)*Rad2Deg;
	//	//		angle2=(C-PI)*Rad2Deg;
	//	//	} 
	//	//	else
	//	//	{
	//	//		angle1=(B-A)*Rad2Deg;
	//	//		angle2=(PI-C)*Rad2Deg;
	//	//	}
	//	//}
	//	double length3 = zbase;
	//	double angle4 = start_RZ;

	//	if (m_AxisMinPos[0] <= angle1 && angle1 <= m_AxisMaxPos[0] && \
	//		m_AxisMinPos[1] <= angle2 && angle2 <= m_AxisMaxPos[1] && \
	//		m_AxisMinPos[2] - 0.000001 <= length3 && length3 <= m_AxisMaxPos[2] + 0.000001&&\
	//		m_AxisMinPos[3] <= angle4 && angle4 <= m_AxisMaxPos[3])

	//	{
	//		Interpo_Param Joint;
	//		Joint.Interpotype = G01;
	//		Joint.EndPosOrLen1 = angle1;
	//		Joint.EndPosOrLen2 = angle2;
	//		Joint.EndPosOrLen3 = length3;
	//		Joint.EndPosOrLen4 = angle4;

	//		Joint.InterpoStartVel = 0;		//��ʼ�ٶ�Ϊ��
	//		Joint.InterpoEndVel = 0;			//��ֹ�ٶ�Ϊ��

	//		if (n == 0)
	//		{
	//			double v1 = (Joint.EndPosOrLen1 - StartJoint.EndPosOrLen1) / T_segment;
	//			double v2 = (Joint.EndPosOrLen2 - StartJoint.EndPosOrLen2) / T_segment;
	//			double v3 = (Joint.EndPosOrLen3 - StartJoint.EndPosOrLen3) / T_segment;
	//			double v4 = (Joint.EndPosOrLen4 - StartJoint.EndPosOrLen4) / T_segment;
	//			Joint.Interpo_Jog_Home_Vel = CRMath::PreRead_sqrtr(v1*v1 + v2 * v2 + v3 * v3 + v4 * v4);

	//			Joint.Length = CRMath::PreRead_sqrtr((Joint.EndPosOrLen1 - StartJoint.EndPosOrLen1)*(Joint.EndPosOrLen1 - StartJoint.EndPosOrLen1) +
	//				(Joint.EndPosOrLen2 - StartJoint.EndPosOrLen2)*(Joint.EndPosOrLen2 - StartJoint.EndPosOrLen2) +
	//				(Joint.EndPosOrLen3 - StartJoint.EndPosOrLen3)*(Joint.EndPosOrLen3 - StartJoint.EndPosOrLen3) +
	//				(Joint.EndPosOrLen4 - StartJoint.EndPosOrLen4)*(Joint.EndPosOrLen4 - StartJoint.EndPosOrLen4));
	//			Joint.Ratio[0] = (Joint.EndPosOrLen1 - StartJoint.EndPosOrLen1) / Joint.Length;
	//			Joint.Ratio[1] = (Joint.EndPosOrLen2 - StartJoint.EndPosOrLen2) / Joint.Length;
	//			Joint.Ratio[2] = (Joint.EndPosOrLen3 - StartJoint.EndPosOrLen3) / Joint.Length;
	//			Joint.Ratio[3] = (Joint.EndPosOrLen4 - StartJoint.EndPosOrLen4) / Joint.Length;
	//		}
	//		else
	//		{
	//			double v1 = (Joint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1) / T_segment;
	//			double v2 = (Joint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2) / T_segment;
	//			double v3 = (Joint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3) / T_segment;
	//			double v4 = (Joint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4) / T_segment;
	//			Joint.Interpo_Jog_Home_Vel = CRMath::PreRead_sqrtr(v1*v1 + v2 * v2 + v3 * v3 + v4 * v4);


	//			Joint.Length = CRMath::PreRead_sqrtr((Joint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1)*(Joint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1) +
	//				(Joint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2)*(Joint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2) +
	//				(Joint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3)*(Joint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3) +
	//				(Joint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4)*(Joint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4));

	//			Joint.Ratio[0] = (Joint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1) / Joint.Length;
	//			Joint.Ratio[1] = (Joint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2) / Joint.Length;
	//			Joint.Ratio[2] = (Joint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3) / Joint.Length;
	//			Joint.Ratio[3] = (Joint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4) / Joint.Length;
	//		}

	//		Joint.SegmentAcc = EndPoint.SegmentAcc;

	//		//���������ٶ�

	//		if (Joint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[0] / Joint.Ratio[0]))
	//		{
	//			Joint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[0] / Joint.Ratio[0]);
	//		}
	//		if (Joint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[1] / Joint.Ratio[1]))
	//		{
	//			Joint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[1] / Joint.Ratio[1]);
	//		}
	//		if (Joint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[2] / Joint.Ratio[2]))
	//		{
	//			Joint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[2] / Joint.Ratio[2]);
	//		}
	//		if (Joint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[3] / Joint.Ratio[3]))
	//		{
	//			Joint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[3] / Joint.Ratio[3]);
	//		}

	//		//�������ڼ��ٶ�

	//		if (Joint.SegmentAcc > ABS(m_AxisMaxAcc[0] / Joint.Ratio[0]))
	//		{
	//			Joint.SegmentAcc = ABS(m_AxisMaxAcc[0] / Joint.Ratio[0]);
	//		}
	//		if (Joint.SegmentAcc > ABS(m_AxisMaxAcc[1] / Joint.Ratio[1]))
	//		{
	//			Joint.SegmentAcc = ABS(m_AxisMaxAcc[1] / Joint.Ratio[1]);
	//		}
	//		if (Joint.SegmentAcc > ABS(m_AxisMaxAcc[2] / Joint.Ratio[2]))
	//		{
	//			Joint.SegmentAcc = ABS(m_AxisMaxAcc[2] / Joint.Ratio[2]);
	//		}
	//		if (Joint.SegmentAcc > ABS(m_AxisMaxAcc[3] / Joint.Ratio[3]))
	//		{
	//			Joint.SegmentAcc = ABS(m_AxisMaxAcc[3] / Joint.Ratio[3]);
	//		}

	//		m_vecTrajectory.push_back(Joint);
	//	}
	//	else
	//	{
	//		AfxMessageBox("�켣�����ö�Բ�������м�㳬���˶���Χ", MB_OK | MB_ICONEXCLAMATION);

	//		return FALSE;
	//	}
	//}
	////�����Ǳ�֤�岹�������յ�Ϊ������յ�

	//EndJoint.InterpoStartVel = 0;		//��ʼ�ٶ�Ϊ��
	//EndJoint.InterpoEndVel = 0;			//��ֹ�ٶ�Ϊ��
	//if (Arc_SegNum < 2)
	//{
	//	double v1 = (EndJoint.EndPosOrLen1 - StartJoint.EndPosOrLen1) / T_end;
	//	double v2 = (EndJoint.EndPosOrLen2 - StartJoint.EndPosOrLen2) / T_end;
	//	double v3 = (EndJoint.EndPosOrLen3 - StartJoint.EndPosOrLen3) / T_end;
	//	double v4 = (EndJoint.EndPosOrLen4 - StartJoint.EndPosOrLen4) / T_end;
	//	EndJoint.Interpo_Jog_Home_Vel = CRMath::PreRead_sqrtr(v1*v1 + v2 * v2 + v3 * v3 + v4 * v4);

	//	EndJoint.Length = CRMath::PreRead_sqrtr((EndJoint.EndPosOrLen1 - StartJoint.EndPosOrLen1)*(EndJoint.EndPosOrLen1 - StartJoint.EndPosOrLen1) +
	//		(EndJoint.EndPosOrLen2 - StartJoint.EndPosOrLen2)*(EndJoint.EndPosOrLen2 - StartJoint.EndPosOrLen2) +
	//		(EndJoint.EndPosOrLen3 - StartJoint.EndPosOrLen3)*(EndJoint.EndPosOrLen3 - StartJoint.EndPosOrLen3) +
	//		(EndJoint.EndPosOrLen4 - StartJoint.EndPosOrLen4)*(EndJoint.EndPosOrLen4 - StartJoint.EndPosOrLen4));
	//	EndJoint.Ratio[0] = (EndJoint.EndPosOrLen1 - StartJoint.EndPosOrLen1) / EndJoint.Length;
	//	EndJoint.Ratio[1] = (EndJoint.EndPosOrLen2 - StartJoint.EndPosOrLen2) / EndJoint.Length;
	//	EndJoint.Ratio[2] = (EndJoint.EndPosOrLen3 - StartJoint.EndPosOrLen3) / EndJoint.Length;
	//	EndJoint.Ratio[3] = (EndJoint.EndPosOrLen4 - StartJoint.EndPosOrLen4) / EndJoint.Length;
	//}
	//else
	//{
	//	double v1 = (EndJoint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1) / T_end;
	//	double v2 = (EndJoint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2) / T_end;
	//	double v3 = (EndJoint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3) / T_end;
	//	double v4 = (EndJoint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4) / T_end;
	//	EndJoint.Interpo_Jog_Home_Vel = CRMath::PreRead_sqrtr(v1*v1 + v2 * v2 + v3 * v3 + v4 * v4);


	//	EndJoint.Length = CRMath::PreRead_sqrtr((EndJoint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1)*(EndJoint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1) +
	//		(EndJoint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2)*(EndJoint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2) +
	//		(EndJoint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3)*(EndJoint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3) +
	//		(EndJoint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4)*(EndJoint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4));

	//	EndJoint.Ratio[0] = (EndJoint.EndPosOrLen1 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen1) / EndJoint.Length;
	//	EndJoint.Ratio[1] = (EndJoint.EndPosOrLen2 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen2) / EndJoint.Length;
	//	EndJoint.Ratio[2] = (EndJoint.EndPosOrLen3 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen3) / EndJoint.Length;
	//	EndJoint.Ratio[3] = (EndJoint.EndPosOrLen4 - m_vecTrajectory.at(m_vecTrajectory.size() - 1).EndPosOrLen4) / EndJoint.Length;
	//}

	//EndJoint.SegmentAcc = EndPoint.SegmentAcc;

	////���������ٶ�

	//if (EndJoint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[0] / EndJoint.Ratio[0]))
	//{
	//	EndJoint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[0] / EndJoint.Ratio[0]);
	//}
	//if (EndJoint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[1] / EndJoint.Ratio[1]))
	//{
	//	EndJoint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[1] / EndJoint.Ratio[1]);
	//}
	//if (EndJoint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[2] / EndJoint.Ratio[2]))
	//{
	//	EndJoint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[2] / EndJoint.Ratio[2]);
	//}
	//if (EndJoint.Interpo_Jog_Home_Vel > ABS(m_AxisMaxSpeed[3] / EndJoint.Ratio[3]))
	//{
	//	EndJoint.Interpo_Jog_Home_Vel = ABS(m_AxisMaxSpeed[3] / EndJoint.Ratio[3]);
	//}

	////�������ڼ��ٶ�

	//if (EndJoint.SegmentAcc > ABS(m_AxisMaxAcc[0] / EndJoint.Ratio[0]))
	//{
	//	EndJoint.SegmentAcc = ABS(m_AxisMaxAcc[0] / EndJoint.Ratio[0]);
	//}
	//if (EndJoint.SegmentAcc > ABS(m_AxisMaxAcc[1] / EndJoint.Ratio[1]))
	//{
	//	EndJoint.SegmentAcc = ABS(m_AxisMaxAcc[1] / EndJoint.Ratio[1]);
	//}
	//if (EndJoint.SegmentAcc > ABS(m_AxisMaxAcc[2] / EndJoint.Ratio[2]))
	//{
	//	EndJoint.SegmentAcc = ABS(m_AxisMaxAcc[2] / EndJoint.Ratio[2]);
	//}
	//if (EndJoint.SegmentAcc > ABS(m_AxisMaxAcc[3] / EndJoint.Ratio[3]))
	//{
	//	EndJoint.SegmentAcc = ABS(m_AxisMaxAcc[3] / EndJoint.Ratio[3]);
	//}


	//m_vecTrajectory.push_back(EndJoint);

	//return TRUE;

}
void Circ_AP_AP_DYN(struct AXISPOS pos1, struct AXISPOS pos2, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	Circ_AP_AP(pos1, pos2);
	callFlag = 0;
}
void Circ_AP_CP_DYN(struct AXISPOS pos1, struct CARTPOS pos2, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	Circ_AP_CP(pos1, pos2);
	callFlag = 0;
}
void Circ_CP_AP_DYN(struct CARTPOS pos1, struct AXISPOS pos2, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	Circ_CP_AP(pos1, pos2);
	callFlag = 0;
}
void Circ_CP_CP_DYN(struct CARTPOS pos1, struct CARTPOS pos2, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	Circ_CP_CP(pos1, pos2);
	callFlag = 0;
}

//PTP�岹���ƫ��ָ��
void PTPRel_AP(struct AXISPOS pos)
{
	struct AXISPOS desAxisPos;
	desAxisPos.a1 = axisPos.a1 + pos.a1; desAxisPos.a2 = axisPos.a2 + pos.a2; desAxisPos.a3 = axisPos.a3 + pos.a3;
	desAxisPos.a4 = axisPos.a4 + pos.a4; desAxisPos.a5 = axisPos.a5 + pos.a5; desAxisPos.a6 = axisPos.a6 + pos.a6;
	PTP_AP(desAxisPos);
}
void PTPRel_CP(struct CARTPOS pos)
{
	struct CARTPOS desCartPos;
	desCartPos.x = cartPos.x + pos.x; desCartPos.y = cartPos.y + pos.y; desCartPos.z = cartPos.z + pos.z;
	desCartPos.a = cartPos.a + pos.a; desCartPos.b = cartPos.b + pos.b; desCartPos.c = cartPos.c + pos.c;
	PTP_CP(desCartPos);
}
void PTPRel_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	PTPRel_AP(pos);
	callFlag = 0;
}
void PTPRel_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	PTPRel_CP(pos);
	callFlag = 0;
}

//Lin�岹���ƫ��ָ��
void LinRel_AP(struct AXISPOS pos)
{
	struct AXISPOS desAxisPos;
	desAxisPos.a1 = axisPos.a1 + pos.a1; desAxisPos.a2 = axisPos.a2 + pos.a2; desAxisPos.a3 = axisPos.a3 + pos.a3;
	desAxisPos.a4 = axisPos.a4 + pos.a4; desAxisPos.a5 = axisPos.a5 + pos.a5; desAxisPos.a6 = axisPos.a6 + pos.a6;
	Lin_AP(desAxisPos);
}
void LinRel_CP(struct CARTPOS pos)
{
	struct CARTPOS desCartPos;
	desCartPos.x = cartPos.x + pos.x; desCartPos.y = cartPos.y + pos.y; desCartPos.z = cartPos.z + pos.z;
	desCartPos.a = cartPos.a + pos.a; desCartPos.b = cartPos.b + pos.b; desCartPos.c = cartPos.c + pos.c;
	Lin_CP(desCartPos);
}
void LinRel_AP_DYN(struct AXISPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	LinRel_AP(pos);
	callFlag = 0;
}
void LinRel_CP_DYN(struct CARTPOS pos, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	LinRel_CP(pos);
	callFlag = 0;
}

//ֹͣ�������˶����Ҷ����Ѿ�����õĲ岹·��,stopMode=0ʱ����������ֹͣ��stopMode=1ʱ�����˼���ֹͣ
void StopRobot_(int stopMode)
{
	if (stopMode == 0)
	{
		IPMCContiStopList(0, 0); //����ֹͣ
	}
	else if (stopMode == 1)
	{
		IPMCContiStopList(0, 1);; //����ֹͣ
	}
}

//�궨����λ�ã���Ե�һ�ᡣ�������˵������󣬱��浱ǰ��������λ����Ϊ�������λ,�Ƕȵ�λΪ�㡣���δ���ýǶȲ�������ѵ�ǰ��λ����Ϊ��λ��
void RefRobotAxis_(int axis)
{
	RefRobotAxis_AG(axis, 0);
}
void RefRobotAxis_AG(int axis, double angle)
{
	int i = axis - 1;
	IPMCEnableSoftlimit(i, 0);
	double singleAxisPos;
	if (axis == 1) singleAxisPos = axisPos.a1;
	else if (axis == 2) singleAxisPos = axisPos.a2;
	else if (axis == 3) singleAxisPos = axisPos.a3;
	else if (axis == 4) singleAxisPos = axisPos.a4;
	else if (axis == 5) singleAxisPos = axisPos.a5;
	else if (axis == 6) singleAxisPos = axisPos.a6;
	//����offset2������
	offset2[i] = offset2[i] + singleAxisPos;
	doc.LoadFile();
	rootElem = doc.RootElement();
	robot = nullptr;
	//�ҵ���ǰ���������ƶ�Ӧ��ʵ��
	getElementByName(rootElem, robotName, &robot);
	TiXmlElement *pElem = nullptr;
	getElementByName(rootElem, "offset2", &pElem);
	char axisName[6];
	sprintf(axisName, "%s%d", "axis", axis);
	char offset2_str[20];
	sprintf(offset2_str, "%.8lf", offset2[i]);
	pElem->SetAttribute(axisName, offset2_str);
	doc.SaveFile();
	//����������������λ��������λ�õ����ò�׼ȷ
	IPMCSetAxisSoftLimit(i, 0, (maxPos[i] + offset2[i]) / pulseEquivalent[i], (minPos[i] + offset2[i]) / pulseEquivalent[i]);
	IPMCEnableSoftlimit(i, 1);
	MoveRobotAxis_(axis, angle);
}
void RefRobotAxis_DYN(int axis, struct DYNAMIC dyn)
{
	RefRobotAxis_AG_DYN(axis, 0, dyn);
}
void RefRobotAxis_AG_DYN(int axis, double angle, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	RefRobotAxis_AG(axis, angle);
	callFlag = 0;
}

//�������ͬʱ���㣬�ѵ�ǰ������������λ����Ϊ�������λ
void RefRobotAxisAsync_()
{
	for (int i = 1; i <= 6; i++)
	{
		RefRobotAxis_AG(i, 0);
	}
}
void RefRobotAxisAsync_DYN(struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	RefRobotAxisAsync_();
	callFlag = 0;
}

//�Ի����˵ĵ�һ������˶�
void MoveRobotAxis_(int axis, double angle)
{
	struct AXISPOS desAxisPos;
	if (axis == 1) desAxisPos.a1 = angle;
	else if (axis == 2) desAxisPos.a2 = angle;
	else if (axis == 3) desAxisPos.a3 = angle;
	else if (axis == 4) desAxisPos.a4 = angle;
	else if (axis == 5) desAxisPos.a5 = angle;
	else if (axis == 6) desAxisPos.a6 = angle;
	PTP_AP(desAxisPos);
}
void MoveRobotAxis_DYN(int axis, double angle, struct DYNAMIC dyn)
{
	Dyn_DYN(dyn, 1);
	callFlag = 1;
	MoveRobotAxis_(axis, angle);
	callFlag = 0;
}

//����ָ����

//����Ĭ�ϵ��˶�����
void Dyn_()
{
	if (selectDyn == 0) //�ֶ�&��λ
	{
		curDynamic = jogSpeed;

	}
	else if (selectDyn == 1) //�ֶ�&�켣
	{
		curDynamic = jogSpeed;

	}
	for (int i = 0; i < 6; ++i)
	{
		//�������Ĭ���ٶ�
		double targetVel = maxVel[i] * curDynamic.velAxis / 100 * ovr / 100 / pulseEquivalent[i] / 1000;
		IPMCSetAxisVel(i, 0, fabs(targetVel), 0);
		//������Ӽ��ٶ�
		double acc = maxAcc[i] * curDynamic.accAxis / 100 * ovr / 100 / pulseEquivalent[i] / pow(1000, 2);
		double dec = maxDec[i] * curDynamic.decAxis / 100 * ovr / 100 / pulseEquivalent[i] / pow(1000, 2);
		IPMCSetAxisAcc(i, fabs(acc), fabs(dec));
		//������Ӽ��ٶ�
		double jerk = maxJerk[i] * curDynamic.jerkAxis / 100 * ovr / 100 / pulseEquivalent[i] / pow(1000, 3);
		IPMCSetAxisJerk(i, fabs(jerk), fabs(jerk));
	}

	if (selectDyn == 0 || selectDyn == 2) //��λ�˶�
	{
		//���ò岹���˶��ٶ�
		double targetVel = maxSyntheticVel * curDynamic.velAxis * ovr / 100 / averagePulseEquivalent / 1000;
		IPMCSetInterpolationVel(0, fabs(targetVel), 0);
		IPMCContiSetTargetVel(0, fabs(targetVel)); //�����������Ӧ����һ����
		//���ò岹�ļ��ٶȺͼ��ٶ�
		double acc = maxSyntheticAcc * curDynamic.accAxis * ovr / 100 / averagePulseEquivalent / pow(1000, 2);
		double dec = maxSyntheticAcc * curDynamic.decAxis * ovr / 100 / averagePulseEquivalent / pow(1000, 2);
		IPMCSetInterpolationAcc(fabs(acc), fabs(dec));
		//���ò岹���߼Ӽ��ٶȺͼ����ٶ�
		double jerk = maxSyntheticJerk * curDynamic.jerkAxis * ovr / 100 / averagePulseEquivalent / pow(1000, 3);
		IPMCSetInterpolationJerk(fabs(jerk), fabs(jerk));
	}
	else if (selectDyn == 1 || selectDyn == 3) //�켣�˶�
	{
		//���ò岹���˶��ٶ�
		double targetVel = curDynamic.velPath * ovr / 100 / averagePulseEquivalent / 1000;
		IPMCSetInterpolationVel(0, fabs(targetVel), 0);
		IPMCContiSetTargetVel(0, fabs(targetVel)); //�����������Ӧ����һ����
		//���ò岹�ļ��ٶȺͼ��ٶ�
		double acc = curDynamic.accPath * ovr / 100 / averagePulseEquivalent / pow(1000, 2);
		double dec = curDynamic.decPath * ovr / 100 / averagePulseEquivalent / pow(1000, 2);
		IPMCSetInterpolationAcc(fabs(acc), fabs(dec));
		//���ò岹���߼Ӽ��ٶȺͼ����ٶ�
		double jerk = curDynamic.jerkPath * ovr / 100 / averagePulseEquivalent / pow(1000, 3);
		IPMCSetInterpolationJerk(fabs(jerk), fabs(jerk));
	}
}

//����dyn���������˶�����
void Dyn_DYN(struct DYNAMIC dyn, int mode)
{
	if (mode == 0)
	{
		retDynamic = dyn;
	}
	tmpDynamic = dyn;
	curDynamic = dyn;
	Dyn_();
}

//���û������˶��Ķ�̬���ʲ���
void Dynovr_(int newOvr)
{
	ovr = newOvr;
	//�����˶��ٶ�
	Dyn_();
}

//�����ٶȹ滮��ʽ��0ΪS���ٶȹ滮��Ĭ�ϣ���1Ϊ�����ٶȹ滮
void Ramp_(int type)
{
	//if (type == 0)
	//{
	//	IPMCSetAxisVProfile(i, 0);
	//}
	//else if (type == 1)
	//{
	//	IPMCSetAxisVProfile(i, 1);
	//}
}

//���òο�ϵ��Ϊ�������е�λ��ָ���趨Ϊһ���µĲο�����ϵ�����������û���趨�ο�����ϵ��ϵͳĬ�ϲο�ϵΪ��������ϵ
void Refsys_(struct CARTREFSYS crs)
{

}

//���ù�������ϵ��Է����̵�λ��
void Tool_(struct CARTSYS cs)
{
	curTool = cs;
}

//ϵͳ����ָ����

//���û����˵ȴ�ʱ��
void WaitTime_(double duration)
{
	Sleep(duration);
}

//ֹͣ���м�������ִ�У�stopMode==0ʱ����������ֹͣ��stopMode==1ʱ�����˼���ֹͣ
void Stop_(int stopMode)
{
	activeState = 0;
}

//����һ��֪ͨ,��Ϣ��ʾ����Ϣ��������
void Notice_(char *text)
{
	cout << text << endl;
}

//����һ��������Ϣ
void Warning_(char *text)
{
	cout << text << endl;
}

//����һ��������Ϣ
void Error_(char *text)
{
	cout << text << endl;
}