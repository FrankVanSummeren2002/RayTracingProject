#include"precomp.h"
#include "Math.h"
int math::clampI(int X, int A, int B)
{
	int temp = min(X, A);
	temp = max(temp, B)
		return temp;
}

float math::InvSqrt(float x) {
	float xhalf = 0.5f * x;
	int i = *(int*)&x;            // store floating-point bits in integer
	i = 0x5f3759df - (i >> 1);    // initial guess for Newton's method
	x = *(float*)&i;              // convert new bits into float
	x = x * (1.5f - xhalf * x * x);     // One round of Newton's method
	return x;
}

float math::clamp(float X,float A,float B)
{
	float temp = min(X, A);
	temp = max(temp, B)
		return temp;
}

float math::calcInterPoint(float& b, float& a, float& d)
{
	float division = 1 / (2 * a);
	float dsqrt = sqrt(d);
	float temp1 = (-b + dsqrt) * division;
	float temp2 = (-b - dsqrt) * division;
	if (temp1 < temp2)
	{
		return temp1;
	}
	else
	{
		return temp2;
	}
}

vec3 math::getNormal(vec3& v, vec3& center)
{
	vec3 temp = v - center;
	temp.normalize();
	return temp;
}

vec3 math::FacingNormal(vec3 v, vec3& n)
{
	float temp = v.dotproduct(n);
	if (temp > 1)
	{
		n = -n;
	}
	return n;
}
vec3 math::refract(vec3& I, vec3 N, float ior, float Tor)
{
	float cosi = math::clamp(N.dotproduct(I), -1.f, 1.f);
	if (cosi < 0) cosi = -cosi;
	float etai = Tor;
	float etat = ior;

	float eta = etai / etat;
	float sin = 1 - eta * eta * (1 - cosi * cosi);
	vec3 temp = I * eta + N * (eta * cosi - sqrt(sin));
	return temp;
}
vec3 math::ranVecGen(int min, int max)
{
	vec3 p;
		while(p.getlength()*p.getlength() < 1)
		{
			p.x = static_cast <float> (rand()) / RAND_MAX + rand() % 2 - 1;
			p.y = static_cast <float> (rand()) / RAND_MAX + rand() % 2 - 1;
			p.z = static_cast <float> (rand()) / RAND_MAX + rand() % 2 - 1;
		}
		return p;
}

float math::ranFloat()
{
	float t = rand() / (RAND_MAX + 1.f);
 	return t;
}

float math::distanceLength(vec3& v, vec3& b)
{
	return sqrt((b.x - v.x) * (b.x - v.x) + (b.y - v.y) * (b.y - v.y) + (b.z - v.z) * (b.z - v.z));
}

bool vec3::operator==(const vec3& v) const
{
	if (v.x == x && v.y == y && v.z == z)
		return true;
	else
		return false;
}

void vec3::operator+=(const vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void vec3::operator-=(const vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void vec3::operator*=(const vec3& b)
{
	x *= b.x;
	y *= b.y;
	z *= b.z;
}

void vec3::operator/=(const vec3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
}

bool vec3::operator<(float b)
{

	return (x + y + z) < b;
}

bool vec3::operator>(float b)
{
	return (x + y + z) > b;
}

bool vec3::operator<(vec3& v)
{
	return (x <v.x && y<v.y && z < v.z);
}

bool vec3::operator>(vec3& v)
{
	return (x > v.x&& y > v.y&& z > v.z);
}

bool vec3::operator!=(const vec3& v) const
{
	if (v.x != x && v.y != y && v.z != z)
		return true;
	else
		return false;
}


vec3::vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

vec3::vec3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

vec3 vec3::reflect(vec3& v, vec3& n) {

	return v - n * v.dotproduct(n) * 2;
}

float vec3::dotproduct(vec3& v)
{
	return x * v.x + y * v.y + z * v.z;
}


vec3 vec3::crossprod(vec3& v)
{
	return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

float vec3::lengthSqaured()
{
	return x * x + y * y + z * z;
}
float vec3::getlength()
{
	float awnser = sqrt(x * x + y * y + z * z);

	return awnser;
}

void vec3::normalize()
{
	float length = getlength();

		float division = 1/length;
		x *= division;
		y *= division;
		z *= division;
	
}


const vec3 vec3::operator-() const
{
	return vec3(-x, -y, -z);
}

const vec3 vec3::operator+(const vec3& v) const
{
	return vec3(x + v.x, y + v.y, z + v.z);
}

const vec3 vec3::operator-(const vec3& v) const
{
	return vec3(x - v.x, y - v.y, z - v.z);
}

const vec3 vec3::operator*(const vec3& v) const
{
	return vec3(v.x * x, v.y * y, v.z * z);
}

const vec3 vec3::operator/(const vec3& b) const
{
	return vec3(x / b.x, y / b.y, z / b.z);
}






void Matrix::IdentityMatrix()
{

}

Matrix::Matrix(int Size)
{
	size = Size;
}

Matrix::Matrix(int Size, float mat[][4])
{
	size = Size;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
}
float Matrix::at(int x, int y)
{
	return matrix[y][x];
}
void Matrix::rotationMatrix(int degrees)
{
	float Rad = static_cast<float>(degrees * PI / 180.f);
	float Cos = cos(Rad);
	float Sin = sin(Rad);
	float mt[4][4] = { {Cos,0,Sin},{0,1,0},{-Sin,0,Cos} };
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = mt[i][j];
		}
	}
}
void Matrix::rotateYaxis(vec3& v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	v.x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z;
	v.y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z;
	v.z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z;

}

