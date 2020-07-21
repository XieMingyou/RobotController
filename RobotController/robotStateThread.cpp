# include "IPMCMOTION.h"
# include "dataDeclaration.h"
# include "robotConfig.h"
# include "robotAlgorithm.h"


void getRobotState()
{
	while (true)
	{
		long lPosition[6] = { 0 };
		//获取轴关节坐标系的位置
		for (int i = 0; i < 6; ++i)
		{
			IPMCGetAxisPosition(i, &lPosition[i]);
		}
		axisPos.a1 = lPosition[0] * pulseEquivalent[0] - offset2[0];
		axisPos.a2 = lPosition[1] * pulseEquivalent[1] - offset2[1];
		axisPos.a3 = lPosition[2] * pulseEquivalent[2] - offset2[2];
		axisPos.a4 = lPosition[3] * pulseEquivalent[3] - offset2[3];
		axisPos.a5 = lPosition[4] * pulseEquivalent[4] - offset2[4];
		axisPos.a6 = lPosition[5] * pulseEquivalent[5] - offset2[5];
		axisPos.a5 += coupling.axis4ToAxis5 * axisPos.a4;
		axisPos.a6 += coupling.axis4ToAxis6 * axisPos.a4 + coupling.axis5ToAxis6 * axisPos.a5;
		//计算伺服电机的位置
		drivePos.d1 = axisPos.a1 * direction[0] * ratio[0];
		drivePos.d2 = axisPos.a2 * direction[1] * ratio[1];
		drivePos.d3 = axisPos.a3 * direction[2] * ratio[2];
		drivePos.d4 = axisPos.a4 * direction[3] * ratio[3];
		drivePos.d5 = axisPos.a5 * direction[4] * ratio[4];
		drivePos.d6 = axisPos.a6 * direction[5] * ratio[5];
		//计算工具坐标系相对世界坐标系的位置
		cartPos = forwardKinematics(axisPos);
		//读取连续插补运动状态
		IPMCContiGetContiRunState(0, &contiRunState);
	}
}