#ifndef MATH
#define MATH
#include <SFML/Graphics.hpp>
#define min(a,b) a < b ? b : a;
#define max(a,b) a > b ? b : a;

class vec3;
namespace math
{
	 int clampI(int x, int a, int b);
	 float InvSqrt(float x);
	 float clamp(float x, float a, float b);
	 float calcInterPoint(float& b, float& a, float& d);
	 vec3 getNormal(vec3& v, vec3& center);
	 vec3 FacingNormal(vec3 v, vec3& n);
	 vec3 refract(vec3& I, vec3 N, float ior, float Tor);
	 vec3 ranVecGen(int min, int max);
	 float ranFloat();
	 float distanceLength(vec3& v, vec3& b);
}

class vec3
{
public:
	union
	{
		float vec[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};

	vec3();

	vec3(float X, float Y, float Z);

	vec3 reflect(vec3& v, vec3& n);

	float dotproduct(vec3& v);


	vec3 crossprod(vec3& v);

	float lengthSqaured();

	float getlength();

	void normalize();


	void operator+=(const vec3& b);
	void operator-=(const vec3& b);
	void operator*=(const vec3& b);
	void operator/=(const vec3& b);
	bool operator<(float b);
	bool operator>(float b);
	bool operator<(vec3& v);
	bool operator>(vec3& v);
	bool operator!=(const vec3& v) const;
	bool operator==(const vec3& v)const;
	const vec3 operator-()const;
	const vec3 operator+(const vec3& v)const;
	const vec3 operator-(const vec3& v)const;
	const vec3 operator*(const vec3& v)const;
	const vec3 operator/(const vec3& v)const;
	template <class T>
	const vec3 operator/(T v) const
	{
		float division = 1 / v;
		return vec3(x * division, y * division, z * division);
	}

	template <class T>
	const vec3 operator*(T v) const
	{
		return vec3(v * x, v * y, v * z);
	}
	template <class T>
	void operator*=(T b)
	{
		x *= b;
		y *= b;
		z *= b;
	}
	template <class T>
	void operator/=(T b)
	{
		auto division = 1 / b;
		x *= division;
		y *= division;
		z *= division;
	}

};



class Matrix
{
	float x = 0;
	float y = 0;
	float z = 0;
	int size = 0;
	float matrix[4][4]{ 0 };
	void IdentityMatrix();
public:
	
	Matrix(int Size);
	Matrix(int size, float mat[][4]);
	float at(int x, int y);
	void rotationMatrix(int degrees);

	void rotateYaxis(vec3& v);
};

#endif