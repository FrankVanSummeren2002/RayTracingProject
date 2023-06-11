#pragma once
#include "vec3.h"
class Matrix
{
	
	float x = 0;
	float y = 0;
	float z = 0;
	
	float matrix[4][4]{ 0 };
	void IdentityMatrix();
	float Determinant3X3(float Mat[4][4]);
public:
	enum class MatSizes
	{ THREE_THREE = 3, FOUR_FOUR = 4 };
	MatSizes Size;
	Matrix(MatSizes size);
	Matrix(MatSizes size, float mat[][4]);
	float at(int x, int y);
	void rotationMatrixX(int degrees);
	void rotationMatrixY(int degrees);
	void rotationMatrixZ(int degrees);
	float getDeterminant();
	float getDeterminant2X2(float  mat[2][2]);
	void rotateAxis(vec3& v);
	void rotationMatrix(vec3& v, float degrees);


	const Matrix operator+(const Matrix& v)const;
	const Matrix operator-(const Matrix& v)const;
	const Matrix operator*(const Matrix& v)const;
	Matrix inverse();
	Matrix operator/(const Matrix& v);


};

