
long IPMCOpenDevice();

long IPMCContiOpenList(unsigned long Crd, unsigned long AxisNum, unsigned long * AxisList, unsigned long * MaxAcc);

long IPMCContiSetLookaheadMode(unsigned long Crd, unsigned long enable, unsigned long LookaheadSegments, double PathError);

long IPMCContiStartList(unsigned long Crd);

long IPMCContiPauseList(unsigned long Crd);

long IPMCContiStopList(unsigned long Crd, unsigned long stop_mode);

long IPMCContiCloseList(unsigned long Crd);

long IPMCStopAllAxis(unsigned long mode);

long IPMCSetAxisJogParam(unsigned long nAxis, double TargetVel, double LowVel, double Acc, double Jerk);

long IPMCJog(unsigned long nAxis, long Dir);

long IPMCCloseDevice();

long IPMCEmergeStop_();

long IPMCGetAxisPosition(unsigned long nAxis, long *Position);

long IPMCContiGetContiRunState(unsigned long Crd, unsigned long * RunState);

long IPMCSetAxisSoftLimit(unsigned long nAxis, unsigned long StopType, long Limp, long  Limn);

long IPMCEnableSoftlimit(unsigned long nAxis, unsigned long Enable);

long IPMCSetAxisPositionMode(unsigned long nAxis, unsigned long PositionMode);

long IPMCSetAxisVel(unsigned long nAxis, double StartV, double TargetV, double EndV);

long IPMCSetAxisAcc(unsigned long nAxis, double Acc, double Dec);

long IPMCSetAxisJerk(unsigned long nAxis, double AccJerk, double DecJerk);

long IPMCSetInterpolationVel(double StartV, double TargetV, double EndV);

long IPMCContiSetTargetVel(unsigned long Crd, double speed);

long IPMCSetInterpolationAcc(double InterpAcc, double InterpDec);

long IPMCSetInterpolationJerk(double AccJerk, double DecJerk);

long IPMCContiLineUnit(unsigned long Crd, unsigned long AxisNum, unsigned long * AxisList, long*Target_Pos, unsigned long posi_mode, long mark);

long IPMCContiStartList(unsigned long Crd);