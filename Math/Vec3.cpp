#include "Vec3.h"
#include "mathlib.h"

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
	return (x < v.x&& y < v.y&& z < v.z);
}

bool vec3::operator>(vec3& v)
{
	return (x > v.x && y > v.y && z > v.z);
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

	float division = 1.f / length;
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