#pragma once
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
		} ;
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
		float division = static_cast<float>(1.f / v);
		return vec3(x * division,y * division, z * division);
	}

	template <class T>
	const vec3 operator*(T v) const
	{
		return vec3(static_cast<float>(v * x),static_cast<float>( v * y),static_cast<float> (v * z));
	}

	template <class T>
	void operator*=(T b)
	{
		x *= static_cast<float> (b);
		y *= static_cast<float> (b);
		z *= static_cast<float> (b);
	}
	template <class T>
	void operator/=(T b)
	{
		float division = 1.f / static_cast<float>(b);
		x *= division;
		y *= division;
		z *= division;
	}

};

