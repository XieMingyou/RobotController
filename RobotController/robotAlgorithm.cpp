#include "robotAlgorithm.h"
#include "dataDeclaration.h"
#include "robotConfig.h"

//将弧度单位全部转换为角度单位计算
double cosd(double angle)
{
	return cos(angle * PI / 180);
}

double sind(double angle)
{
	return sin(angle * PI / 180);
}

double tand(double angle)
{
	return tan(angle * PI / 180);
}

double atan2d(double value1, double value2)
{
	return atan2(value1, value2) * 180 / PI;
}

//绕轴旋转得到旋转矩阵
Matrix4d rot(double angle, int axis)
{
	Matrix4d rotation = Matrix4d::Identity();
	//axis==0绕x旋转，axis==1绕y旋转,axis==2绕z旋转
	if (axis == 0)
	{
		rotation(1, 1) = cosd(angle);
		rotation(1, 2) = -sind(angle);
		rotation(2, 1) = sind(angle);
		rotation(2, 2) = cosd(angle);
	}
	else if (axis == 1)
	{
		rotation(0, 0) = cosd(angle);
		rotation(0, 2) = sind(angle);
		rotation(2, 1) = -sind(angle);
		rotation(2, 2) = cosd(angle);
	}
	else if (axis == 2)
	{
		rotation(0, 0) = cosd(angle);
		rotation(0, 1) = -sind(angle);
		rotation(1, 0) = sind(angle);
		rotation(1, 1) = cosd(angle);
	}
	return rotation;
}

//沿轴平移得到平移矩阵
Matrix4d trans(double distance, int axis)
{
	Matrix4d translation = Matrix4d::Identity();
	//axis==0沿轴x平移，axis==1沿y轴平移,axis==2沿z轴平移
	if (axis == 0)
	{
		translation(0, 3) = distance;
	}
	else if (axis == 1)
	{
		translation(1, 3) = distance;
	}
	else if (axis == 2)
	{
		translation(2, 3) = distance;
	}
	return translation;
}

//由位姿坐标转换为齐次变换矩阵
Matrix4d pose2Matrix(struct CARTPOS cartPos)
{
	return trans(cartPos.x, 0) * trans(cartPos.y, 1) * trans(cartPos.z, 2) * rot(cartPos.a, 2) * rot(cartPos.b, 1) * rot(cartPos.c, 2);
}

//由齐次变换矩阵转换为位姿坐标
struct CARTPOS matrix2Pose(Matrix4d matrix)
{
	struct CARTPOS cartPos;
	cartPos.x = matrix(0, 3);
	cartPos.y = matrix(1, 3);
	cartPos.z = matrix(2, 3);
	cartPos.a = atan2d(sqrt(pow(matrix(2, 0), 2) + pow(matrix(2, 1), 2)), matrix(2, 2));
	cartPos.b = atan2d(matrix(1, 2) / sind(cartPos.a), matrix(0, 2) / sind(cartPos.a));
	cartPos.c = atan2d(matrix(2, 1) / sind(cartPos.a), -matrix(2, 0) / sind(cartPos.a));
	return cartPos;
}

//机器人正解
struct CARTPOS forwardKinematics(struct AXISPOS axisPos)
{
	Matrix4d T = Matrix4d::Identity();
	double theta[6] = { axisPos.a1, axisPos.a2, axisPos.a3, axisPos.a4, axisPos.a5, axisPos.a6 };
	for (int i = 0; i < 6; ++i)
	{
		T = T * rot(alpha[i], 0) * trans(a_[i], 0) * trans(d[i], 2) * rot((theta[i] + offset1[i]), 2);
	}
	//采用Z-Y-Z欧拉角描述坐标系的绕轴旋转
	Matrix4d baseT = rot(base.a, 2) * rot(base.b, 1) * rot(base.c, 2);
	Matrix4d toolT = rot(curTool.a, 2) * rot(curTool.b, 1) * rot(curTool.c, 2);
	T = baseT * T * toolT;
	return matrix2Pose(T);
}

MatrixXd copyMatrix(MatrixXd cMatrix, int startRow, int startColumn, int numsRow, int numsColumn)
{
	MatrixXd rMatrix(numsRow, numsColumn);
	for (int i = 0; i < numsRow; i++)
	{
		for (int j = 0; j < numsColumn; j++)
		{
			rMatrix(i, j) = cMatrix(startRow + i, startColumn + j);
		}
	}
	return rMatrix;
}

// 利用Eigen库，采用SVD分解的方法求解矩阵伪逆，默认误差er为0
MatrixXd pinv(MatrixXd & origin, const float tolerance = 0) {
	// 进行svd分解
	JacobiSVD<MatrixXd> svd_holder(origin, ComputeThinU | ComputeThinV);
	// 构建SVD分解结果
	MatrixXd U = svd_holder.matrixU();
	MatrixXd V = svd_holder.matrixV();
	MatrixXd D = svd_holder.singularValues();

	// 构建S矩阵
	MatrixXd S(V.cols(), U.cols());
	S.setZero();

	for (unsigned int i = 0; i < D.size(); ++i) {

		if (D(i, 0) > tolerance) {
			S(i, i) = 1 / D(i, 0);
		}
		else {
			S(i, i) = 0;
		}
	}

	// pinv_matrix = V * S * U^T
	return V * S * U.transpose();
}

//机器人逆解，axisPos为上一次计算得到的逆解，以便求出距离上次逆解最近的新逆解
struct AXISPOS inverseKinematics(struct CARTPOS cartPos, struct AXISPOS axisPos)
{
	struct AXISPOS desAxisPos;
	int numsIter = 10; //最大迭代次数
	//矢量积法求雅克比矩阵
	VectorXd newTheta(6);
	newTheta(0) = axisPos.a1 + offset1[0]; newTheta(1) = axisPos.a2 + offset1[1]; newTheta(2) = axisPos.a3 + offset1[2];
	newTheta(3) = axisPos.a4 + offset1[3]; newTheta(4) = axisPos.a5 + offset1[4]; newTheta(5) = axisPos.a6 + offset1[5];
	Matrix4d desT = pose2Matrix(cartPos);
	//采用牛顿-拉夫逊迭代法求逆解
	while (numsIter)
	{
		Matrix4d T01 = rot(alpha[0], 0) * trans(a_[0], 0) * trans(d[0], 2) * rot(newTheta(0), 2);
		Matrix4d T12 = rot(alpha[1], 0) * trans(a_[1], 0) * trans(d[1], 2) * rot(newTheta(1), 2);
		Matrix4d T23 = rot(alpha[2], 0) * trans(a_[2], 0) * trans(d[2], 2) * rot(newTheta(2), 2);
		Matrix4d T34 = rot(alpha[3], 0) * trans(a_[3], 0) * trans(d[3], 2) * rot(newTheta(3), 2);
		Matrix4d T45 = rot(alpha[4], 0) * trans(a_[4], 0) * trans(d[4], 2) * rot(newTheta(4), 2);
		Matrix4d T56 = rot(alpha[5], 0) * trans(a_[5], 0) * trans(d[5], 2) * rot(newTheta(5), 2);

		Matrix3d R01 = copyMatrix(T01, 0, 0, 3, 3);
		Matrix3d R12 = copyMatrix(T12, 0, 0, 3, 3);
		Matrix3d R23 = copyMatrix(T23, 0, 0, 3, 3);
		Matrix3d R34 = copyMatrix(T34, 0, 0, 3, 3);
		Matrix3d R45 = copyMatrix(T45, 0, 0, 3, 3);
		Matrix3d R56 = copyMatrix(T56, 0, 0, 3, 3);

		Matrix4d T46 = T45 * T56, T36 = T34 * T46, T26 = T23 * T36, T16 = T12 * T26;
		Matrix3d R02 = R01 * R12, R03 = R02 * R23, R04 = R03 * R34, R05 = R04 * R45, R06 = R05 * R56;

		Vector3d z, z1, z2, z3, z4, z5, z6;
		z(2) = 1;
		z1 = R01 * z;
		z2 = R02 * z;
		z3 = R03 * z;
		z4 = R04 * z;
		z5 = R05 * z;
		z6 = R06 * z;

		Vector4d t, t16, t26, t36, t46, t56, t66;
		t(3) = 1;
		t16 = T16 * t;
		t26 = T26 * t;
		t36 = T36 * t;
		t46 = T46 * t;
		t56 = T56 * t;
		t66 = t;

		Vector3d p16 = copyMatrix(t16, 0, 0, 3, 1);
		Vector3d p26 = copyMatrix(t26, 0, 0, 3, 1);
		Vector3d p36 = copyMatrix(t36, 0, 0, 3, 1);
		Vector3d p46 = copyMatrix(t46, 0, 0, 3, 1);
		Vector3d p56 = copyMatrix(t56, 0, 0, 3, 1);
		Vector3d p66 = copyMatrix(t66, 0, 0, 3, 1);

		Vector3d p16_0, p26_0, p36_0, p46_0, p56_0, p66_0;
		p16_0 = R01 * p16;
		p26_0 = R02 * p26;
		p36_0 = R03 * p36;
		p46_0 = R04 * p46;
		p56_0 = R05 * p56;
		p66_0 = R06 * p66;

		Vector3d JL1, JL2, JL3, JL4, JL5, JL6;
		//JL1[0] = z1[1] * p16_0[2] - p16_0[1] * z1[2];
		//JL1[1] = z1[2] * p16_0[0] - p16_0[2] * z1[0];
		//JL1[2] = z1[0] * p16_0[1] - p16_0[0] * z1[1];
		//JL2[0] = z2[1] * p26_0[2] - p26_0[1] * z2[2];
		//JL2[1] = z2[2] * p26_0[0] - p26_0[2] * z2[0];
		//JL2[2] = z2[0] * p26_0[1] - p26_0[0] * z2[1];
		//JL3[0] = z3[1] * p36_0[2] - p36_0[1] * z3[2];
		//JL3[1] = z3[2] * p36_0[0] - p36_0[2] * z3[0];
		//JL3[2] = z3[0] * p36_0[1] - p36_0[0] * z3[1];
		//JL4[0] = z4[1] * p46_0[2] - p46_0[1] * z4[2];
		//JL4[1] = z4[2] * p46_0[0] - p46_0[2] * z4[0];
		//JL4[2] = z4[0] * p46_0[1] - p46_0[0] * z4[1];
		//JL5[0] = z5[1] * p56_0[2] - p56_0[1] * z5[2];
		//JL5[1] = z5[2] * p56_0[0] - p56_0[2] * z5[0];
		//JL5[2] = z5[0] * p56_0[1] - p56_0[0] * z5[1];
		//JL6[0] = z6[1] * p66_0[2] - p66_0[1] * z6[2];
		//JL6[1] = z6[2] * p66_0[0] - p66_0[2] * z6[0];
		//JL6[2] = z6[0] * p66_0[1] - p66_0[0] * z6[1];

		JL1 = z1.cross(p16_0);
		JL2 = z2.cross(p26_0);
		JL3 = z3.cross(p36_0);
		JL4 = z4.cross(p46_0);
		JL5 = z5.cross(p56_0);
		JL6 = z6.cross(p66_0);

		MatrixXd fJe(6, 6); //雅克比矩阵

		for (int i = 0; i < 3; i++) {
			fJe(i, 0) = JL1(i);
			fJe(i, 1) = JL2(i);
			fJe(i, 2) = JL3(i);
			fJe(i, 3) = JL4(i);
			fJe(i, 4) = JL5(i);
			fJe(i, 5) = JL6(i);
			fJe(i + 3, 0) = z1(i);
			fJe(i + 3, 1) = z2(i);
			fJe(i + 3, 2) = z3(i);
			fJe(i + 3, 3) = z4(i);
			fJe(i + 3, 4) = z5(i);
			fJe(i + 3, 5) = z6(i);
		}

		MatrixXd fJe_ = pinv(fJe); //利用SVD分解求雅克比矩阵的伪逆

		//求微分运动向量delta
		Matrix4d curT = T01 * T12 * T23 * T34 * T45 * T56;
		Matrix4d deltaT = curT.inverse() * desT - Matrix4d::Identity();
		VectorXd delta(6);
		delta(0) = deltaT(0, 3); delta(1) = deltaT(1, 3); delta(2) = deltaT(3, 3);
		delta(3) = deltaT(2, 1); delta(4) = deltaT(0, 2); delta(5) = deltaT(1, 0);
		VectorXd desTheta = newTheta + fJe_ * delta;
		
		if ((desTheta - newTheta).norm() < 1e-8)
		{
			desAxisPos.a1 = desTheta(0) - offset1[0]; desAxisPos.a2 = desTheta(1) - offset1[1]; desAxisPos.a3 = desTheta(2) - offset1[2];
			desAxisPos.a4 = desTheta(3) - offset1[3]; desAxisPos.a5 = desTheta(4) - offset1[4]; desAxisPos.a6 = desTheta(5) - offset1[5];
			return desAxisPos;
		}
		else
		{
			newTheta = desTheta;
		}
	}
	//求逆解不成功，返回原来的轴关节空间坐标
	return axisPos;
}