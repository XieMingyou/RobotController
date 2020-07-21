#include <Eigen/Dense>
using namespace Eigen;

//������ת�õ���ת����
Matrix4d rot(double angle, int axis);

//����ƽ�Ƶõ�ƽ�ƾ���
Matrix4d trans(double distance, int axis);

//��λ������ת��Ϊ��α任����
Matrix4d pose2Matrix(struct CARTPOS cartPos);

//����α任����ת��Ϊλ������
struct CARTPOS matrix2Pose(Matrix4d matrix);

//����������
struct CARTPOS forwardKinematics(struct AXISPOS);

//��������⣬axisPosΪ��һ�μ���õ�����⣬�Ա���������ϴ��������������
struct AXISPOS inverseKinematics(struct CARTPOS cartPos, struct AXISPOS axisPos);