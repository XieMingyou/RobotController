#include <Eigen/Dense>
using namespace Eigen;

//绕轴旋转得到旋转矩阵
Matrix4d rot(double angle, int axis);

//沿轴平移得到平移矩阵
Matrix4d trans(double distance, int axis);

//由位姿坐标转换为齐次变换矩阵
Matrix4d pose2Matrix(struct CARTPOS cartPos);

//由齐次变换矩阵转换为位姿坐标
struct CARTPOS matrix2Pose(Matrix4d matrix);

//机器人正解
struct CARTPOS forwardKinematics(struct AXISPOS);

//机器人逆解，axisPos为上一次计算得到的逆解，以便求出距离上次逆解最近的新逆解
struct AXISPOS inverseKinematics(struct CARTPOS cartPos, struct AXISPOS axisPos);