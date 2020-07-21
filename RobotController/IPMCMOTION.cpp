#include "IPMCMOTION.h"
#include <cstdlib>

long IPMCOpenDevice()
{
	long i = 0;
	return i;
}

long IPMCContiOpenList(unsigned long Crd, unsigned long AxisNum, unsigned long * AxisList, unsigned long * MaxAcc)
{
	long i = 0;
	return i;
}

long IPMCContiSetLookaheadMode(unsigned long Crd, unsigned long enable, unsigned long LookaheadSegments, double PathError)
{
	long i = 0;
	return i;
}

long IPMCContiStartList(unsigned long Crd)
{
	long i = 0;
	return i;
}

long IPMCContiPauseList(unsigned long Crd)
{
	long i = 0;
	return i;
}

long IPMCContiStopList(unsigned long Crd, unsigned long stop_mode)
{
	long i = 0;
	return i;
}

long IPMCContiCloseList(unsigned long Crd)
{
	long i = 0;
	return i;
}

long IPMCStopAllAxis(unsigned long mode)
{
	long i = 0;
	return i;
}

long IPMCSetAxisJogParam(unsigned long nAxis, double TargetVel, double LowVel, double Acc, double Jerk)
{
	long i = 0;
	return i;
}

long IPMCJog(unsigned long nAxis, long Dir)
{
	long i = 0;
	return i;
}

long IPMCCloseDevice()
{
	long i = 0;
	return i;
}

long IPMCEmergeStop_()
{
	long i = 0;
	return i;
}

long IPMCGetAxisPosition(unsigned long nAxis, long *Position)
{
	long i = 0;
	*Position = long(rand() % 10000);
	return i;
}

long IPMCContiGetContiRunState(unsigned long Crd, unsigned long * RunState)
{
	long i = 0;
	return i;
}

long IPMCSetAxisSoftLimit(unsigned long nAxis, unsigned long StopType, long Limp, long  Limn)
{
	long i = 0;
	return i;
}

long IPMCEnableSoftlimit(unsigned long nAxis, unsigned long Enable)
{
	long i = 0;
	return i;
}

long IPMCSetAxisPositionMode(unsigned long nAxis, unsigned long PositionMode)
{
	long i = 0;
	return i;
}

long IPMCSetAxisVel(unsigned long nAxis, double StartV, double TargetV, double EndV)
{
	long i = 0;
	return i;
}

long IPMCSetAxisAcc(unsigned long nAxis, double Acc, double Dec)
{
	long i = 0;
	return i;
}

long IPMCSetAxisJerk(unsigned long nAxis, double AccJerk, double DecJerk)
{
	long i = 0;
	return i;
}

long IPMCSetInterpolationVel(double StartV, double TargetV, double EndV)
{
	long i = 0;
	return i;
}

long IPMCContiSetTargetVel(unsigned long Crd, double speed)
{
	long i = 0;
	return i;
}

long IPMCSetInterpolationAcc(double InterpAcc, double InterpDec)
{
	long i = 0;
	return i;
}

long IPMCSetInterpolationJerk(double AccJerk, double DecJerk)
{
	long i = 0;
	return i;
}

long IPMCContiLineUnit(unsigned long Crd, unsigned long AxisNum, unsigned long * AxisList, long*Target_Pos, unsigned long posi_mode, long mark)
{
	long i = 0;
	return i;
}