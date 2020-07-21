#include "dataDeclaration.h"
#include "IPMCMOTION.h"
# include "semantics.h"
# include "interpreter.h"
# include "robotInstruction.h"
# include "robotConfig.h"
# include <thread>

//�����������̣߳������Գ���ı����ִ��
void compileAndRun()
{
	rootHead = (AST *)malloc(sizeof(AST));//������ͷָ��
	rootTail = rootHead;//������βָ��
	AST initial = { 0 };
	*rootHead = initial;
	char *varProgName = (char*)::varProgName.data();
	varProgQueue.push(varProgName);
	if (!varProgCompile())
	{
		mainProgRoot = rootHead->next;
		//��ʼ���������˶�����������
		robotInitial();
		//��ʼִ�г���
		progRun(mainProgRoot); //rootTail����������ĸ����
		//�ͷ����н��������ڴ棬��ֹ�ڴ�й©
		while (rootHead != NULL)
		{
			AST *temp = rootHead->next;
			deleteAst(rootHead);
			rootHead = temp;
		}
	}
	else
	{
		printf("���벻ͨ����");
	}
}

void robotControl()
{
	varProgName = "program1";
	projName = "project1";
	mainProgRoot = nullptr;
	int hasEnable = 0; //�ж��Ƿ��Ѿ��ϵ�
	int manual2Auto = 0; //�ж��Ƿ���ֶ�ģʽ�л�Ϊ�Զ�ģʽ
	int auto2Manual = 0; //�ж��Ƿ���Զ�ģʽ�л�Ϊ�ֶ�ģʽ
	int activeFromInactive = 1; //�ж��Ƿ�ӳ���δ����״̬��Ϊ���򼤻�״̬
	int inactiveFromActive = 0; //�ж��Ƿ�ӳ��򼤻�״̬��Ϊ����δ����״̬
	int startFromActive = 1; //�ж��Ƿ�ӳ��򼤻�״̬��Ϊ��������״̬
	int startFromStop = 0; //�ж��Ƿ�ӳ���ֹͣ״̬��Ϊ��������״̬
	int stopFromStart = 0; //�ж��Ƿ�ӳ�������״̬��Ϊ����ֹͣ״̬
	int keepTeach = 0; //�ж��Ƿ񱣳ֵ㶯ʾ�̣�����Jog�������ظ�����
	while(true)
	{
		if (emergeStop == 0)
		{
			//���û����˵Ķ�̬���ʲ���,ͬʱ�����˶�����
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
				//�Գ����ִ�в���
				//����ǳ�����غ󡢳�����ֹ�󡢳����޸ĺ󣬳��򻹴���δ����״̬����ʱ������ʼ����ť����򼤻�
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
						IPMCContiOpenList(0, 6, ulAxisList6, ulMaxACC); //�򿪲岹������
						IPMCContiSetLookaheadMode(0, 1, 100, 1); //����ǰհ���������û���Ƿ�Ҳ���ԣ�
					}
					else if (activeFromInactive == 0)
					{
						//���򼤻��״̬����ʱ������Ӧ
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
							//���򼤻�״̬�£�ͬʱ�����Ϊ����״̬ʱ�����������������̣߳������Գ���ı����ִ��
							thread runThread(compileAndRun);
							runThread.detach();
						}
						else if (startFromActive == 0)
						{
							if (startFromStop == 1)
							{
								startFromStop = 0;
								//���򼤻�״̬�£��ӳ���ֹͣ״̬��Ϊ��������״̬ʱ�ָ������˵��˶��ͳ����ִ��
								IPMCContiStartList(0);
							}
							else if (startFromStop == 1)
							{
								//���򼤻�״̬�£���������״̬����ʱ������Ӧ
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
							//���򼤻�״̬�£��ӳ�������״̬��Ϊ����ֹͣ״̬ʱ��ͣ�����˵��˶��ͳ����ִ��
							IPMCContiPauseList(0);
						}
						else if (stopFromStart == 0)
						{
							//���򼤻�״̬�£�����ֹͣ״̬����ʱ������Ӧ
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
						//����δ�����״̬����ʱ������Ӧ
					}
				}
				//ʾ�̲���
				if (operateMode == 0)
				{
					curDynamic = jogSpeed;
					if (coordinate != 0) //��ʼʾ��
					{
						if (keepTeach == 0)
						{
							keepTeach = 1;
							if (jog == 1) //��ؽ�����ϵ
							{
								selectDyn = 0;
								Dyn_();
								int dir; //�˶�����
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
							else if (jog == 2) //��������ϵ
							{
								selectDyn = 1;
								Dyn_();

							}
							else if (jog == 3) //��������ϵ
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

