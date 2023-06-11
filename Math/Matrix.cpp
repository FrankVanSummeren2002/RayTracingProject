#include "Matrix.h"
#include "mathlib.h"

void Matrix::IdentityMatrix()
{

}

Matrix::Matrix(MatSizes size)
{
	Size = size;
}

Matrix::Matrix(MatSizes size, float mat[][4])
{
	Size = size;
	for (int i = 0; i < static_cast<int>(size); i++)
	{
		for (int j = 0; j < static_cast<int>(size); j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
}
float Matrix::at(int x, int y)
{
	return matrix[y][x];
}
void Matrix::rotationMatrixY(int degrees)
{
	float Rad = static_cast<float>(degrees * PI / 180.f);
	float Cos = cos(Rad);
	float Sin = sin(Rad);
	float mt[4][4] = { {Cos,0,Sin},{0,1,0},{-Sin,0,Cos} };
	for (int i = 0; i < static_cast<int>(Size); i++)
	{
		for (int j = 0; j < static_cast<int>(Size); j++)
		{
			matrix[i][j] = mt[i][j];
		}
	}
}
void Matrix::rotationMatrixX(int degrees)
{
	float Rad = static_cast<float>(degrees * PI / 180.f);
	float Cos = cos(Rad);
	float Sin = sin(Rad);
	float mt[4][4] = { {1,0,0},{0,Cos,Sin},{0,Sin,Cos}};
	for (int i = 0; i < static_cast<int>(Size); i++)
	{
		for (int j = 0; j < static_cast<int>(Size); j++)
		{
			matrix[i][j] = mt[i][j];
		}
	}
}
void Matrix::rotationMatrixZ(int degrees)
{
	float Rad = static_cast<float>(degrees * PI / 180.f);
	float Cos = cos(Rad);
	float Sin = sin(Rad);
	float mt[4][4] = { {Cos,-Sin,0},{Sin,Cos,0},{0,0,1} };
	for (int i = 0; i < static_cast<int>(Size); i++)
	{
		for (int j = 0; j < static_cast<int>(Size); j++)
		{
			matrix[i][j] = mt[i][j];
		}
	}
}
float Matrix::getDeterminant()
{
	if (static_cast<int>(Size) == 3)
	{
		return Determinant3X3(matrix);
	}
	else
	{
		float D = 0;
		float tempMat[4][4];
		int Xiter = 0;
		int sign = 1;
		for (int i = 0; i < 4; i++)
		{
			int Yiter = 0;
			for (int y = 1; y < static_cast<int>(Size); y++)
			{


				for (int x = 0; x < static_cast<int>(Size); x++)
				{
					if (x == i)
					{
						continue;
					}

					tempMat[Yiter][Xiter] = matrix[y][x];
					Xiter++;
				}
				Xiter = 0;
				Yiter++;
			}
			D += sign * matrix[0][i] * Determinant3X3(tempMat);
			sign *= -1;
		}

		return D;
	}



}
float Matrix::getDeterminant2X2(float Mat[2][2])
{
	return (Mat[0][0] * Mat[1][1] - Mat[0][1] * Mat[1][0]);
}

float Matrix::Determinant3X3(float Mat[4][4])
{
	float D = Mat[0][0] * (Mat[1][1] * Mat[2][2] - Mat[1][2] * Mat[2][1])
		+ Mat[0][1] * (Mat[1][2] * Mat[2][0] - Mat[1][0] * Mat[2][2])
		+ Mat[0][2] * (Mat[1][0] * Mat[2][1] - Mat[1][1] * Mat[2][0]);
	return D;
}
void Matrix::rotateAxis(vec3& v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	v.x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z;
	v.y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z;
	v.z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z;

}
void Matrix::rotationMatrix(vec3& v,float degrees)
{
	//based on the rodrigues formula
	float Rad = static_cast<float>(degrees * PI / 180.f);
	float I[3][3] = { {1,0,0},{0,1,0},{0,0,1} };
	float Cos = cos(Rad);
	float Sin = sin(Rad);
	float m[4][4] = { {0,-v.z,v.y},{v.z,0,-v.x},{-v.y,v.x,0}};
	Matrix w(MatSizes::THREE_THREE, m);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrix[i][j] = I[i][j] + (w.matrix[i][j] * Sin) + (w.matrix[i][j] * w.matrix[i][j]) * ((1-Cos) * (Rad * 0.5f));
		}
	}
	
}
const Matrix Matrix::operator+(const Matrix& v) const
{
	float temp[4][4];
	for (int i = 0; i < static_cast<int>(Size); i++)
	{
		for (int j = 0; j < static_cast<int>(Size); j++)
		{
			temp[i][j] = matrix[i][j] + v.matrix[i][j];
		}
	}
	return Matrix(Size, temp);
}

const Matrix Matrix::operator-(const Matrix& v) const
{
	float temp[4][4];
	for (int i = 0; i < static_cast<int>(Size); i++)
	{
		for (int j = 0; j < static_cast<int>(Size); j++)
		{
			temp[i][j] = matrix[i][j] - v.matrix[i][j];
		}
	}
	return Matrix(Size, temp);
}

const Matrix Matrix::operator*(const Matrix& v) const
{
	float temp[4][4] = { {0,0,0,0}, {0,0,0,0},{0,0,0,0}, {0,0,0,0} };
	for (int i = 0; i < static_cast<int>(Size); i++)
	{
		for (int j = 0; j < static_cast<int>(Size); j++)
		{
			for (int k = 0; k < static_cast<int>(Size); k++)
			{

				temp[i][j] += matrix[i][k] * v.matrix[k][j];

			}
		}
	}

	return Matrix(Size, temp);
}
Matrix Matrix::inverse()
{
	float division = 1.f/getDeterminant();
	float tempMatrix[4][4];
	int Xiter = 0;
	int Yiter = 0;
	int sign = 1;
	if (static_cast<int>(Size) == 3)
	{
		for (int i = 0; i < static_cast<int>(Size); i++)
		{
			for (int j = 0; j < static_cast<int>(Size); j++)
			{
				float mat2x2[2][2];
				Yiter = 0;
				for (int k = 0; k < static_cast<int>(Size); k++)
				{
					if (k == i)
					{
						continue;
					}
					
					for (int l = 0; l < static_cast<int>(Size); l++)
					{
						if (l == j)
						{
							continue;
						}
						
						mat2x2[Yiter][Xiter] = matrix[k][l];
						Xiter++;
					}
					Yiter++;
					Xiter = 0;
				}
				
				tempMatrix[j][i] =sign * division * getDeterminant2X2(mat2x2);
				sign *= -1;
			}
		}
	}
	else
	{
		for (int i = 0; i < static_cast<int>(Size); i++)
		{
			
			for (int j = 0; j < static_cast<int>(Size); j++)
			{
				float mat3x3[4][4];
				Yiter = 0;
				for (int k = 0; k < static_cast<int>(Size); k++)
				{
					if (k == i)
					{
						continue;
					}

					for (int l = 0; l < static_cast<int>(Size); l++)
					{
						if (l == j)
						{
							continue;
						}

						mat3x3[Yiter][Xiter] = matrix[k][l];
						Xiter++;
					}
					Yiter++;
					Xiter = 0;
				}

				tempMatrix[j][i] = sign * division * Determinant3X3(mat3x3);
				sign *= -1;
			}
			sign *= -1;
		}
	}
	return Matrix(Size,tempMatrix);

}

 Matrix Matrix::operator/(const Matrix& v)
{
	Matrix temp = inverse();
	return temp * v;
}
