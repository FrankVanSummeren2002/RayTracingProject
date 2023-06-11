#include "Mathlib.h"
#include "vec3.h" 

float math::ABS(float x)
{
	if ( x < 0)
	{
		return -x;
    }
	return x;
}
vec3 math::ABS(vec3 x)
{
	for (int i = 0; i < 3; i++)
	{
		if (x.vec[i] < 0)
		{
			x.vec[i] =  -x.vec[i];
		}
	}
	return x;
}
vec3 math::MINvec(vec3 v, float min)
{
	vec3 Anwser;
	for (int i = 0; i < 3; i++)
	{
		if (v.vec[i] < min)
			Anwser.vec[i] = min;
		
		else
			Anwser.vec[i] = v.vec[i];
	}
	return Anwser;
}
vec3 math::MAXvec(vec3& v, float max)
{
	vec3 Anwser;
	for (int i = 0; i < 3; i++)
	{
		if (v.vec[i] > max)
			Anwser.vec[i] = max;

		else
			Anwser.vec[i] = v.vec[i];
	}
	return Anwser;
}
int math::clampI(int X, int A, int B)
{
	int temp = max(X, A);
	temp = min(temp, B);
		return temp;
}

vec3 math::Vecclamp(vec3 v, float Min, float Max)
{
	for (int i = 0; i < 3; i++)
	{
		float temp = max(v.vec[i], Min);
		v.vec[i] = min(temp, Max);
	}
	return v;
}





float math::clamp(float X, float A, float B)
{
	float temp = max(X, A);
	temp = min(temp, B);
		return temp;
}





vec3 math::FacingNormal(vec3 v, vec3& n)
{
	float dot = v.dotproduct(n);
	if (dot > 1 || dot <= 0)
	{
		n = -n;
	}
	return n;
}
//based on https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
vec3 math::refract(vec3& Dir, vec3 N, float ior, float Tor, bool front)
{
	float temp = N.dotproduct(Dir);
	float cos = clamp(temp,-1,1);
	vec3 n = N;
	if (cos < 0)
	cos = -cos;

	else
	{
		float temp = ior;
		ior = Tor;
		Tor = ior;
		n = -N;
	}
	float division = ior / Tor;
	temp = 1 - division * division * (1 - cos * cos);
	return (Dir * division + n * (division * cos - sqrtf(math::ABS(temp))));
	
}

//based on shlicks approximation https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics/refraction	
float math::reflectionRate(vec3& I, vec3 N, float ior, float Tor)
{
	float cosine = -I.dotproduct(N);
	if (cosine < 0)
		cosine = -cosine;
	
	float temp = (1 - ior) / (1 + ior);
	temp = temp	 * temp;
	temp = temp + (1 - temp) * pow((1 - cosine), 5);
	math::clamp(temp, 0, 1);
	return temp;
}
vec3 math::ranVecGen(int& seed, float max, float min)
{
	vec3 p;
		p.x = RANDF_MIN_MAX(seed,max,min);
		p.y = RANDF_MIN_MAX(seed, max, min);
		p.z = RANDF_MIN_MAX(seed, max, min);

	return p;
}


float math::distanceLength(vec3& v, vec3& b)
{
	return sqrt((b.x - v.x) * (b.x - v.x) + (b.y - v.y) * (b.y - v.y) + (b.z - v.z) * (b.z - v.z));
}

int math::xorshift(int& state)
{
	int temp = state;
	temp ^= temp << 17;
	temp ^= temp >> 12;
	temp ^= temp << 15;
	state = temp;
	return temp;
}

int math::RANDI_MIN_MAX(int& seed, __int32 max, __int32 min) {
	if (abs(min) > abs(max))
	{
		int swap = min;
		min = max;
		max = swap;
	}
	int value = max - min;
	if (max > 0)
	{
		value++;
		__int32 MAX = (-value) % value;

				__int32 r = xorshift(seed);
				if (r >= MAX)
					return (r % value) + min;
				else
					return(-r % value) + max;
	}
	else
	{
		value--;
		__int32 MAX = (-value) % value;
			__int32 r = xorshift(seed);
			while (true)
			{
				if (r >= MAX)
					return -(r % value) + min;
				else
					return(r % value) + max;
			}
			
	}
}

float math::RANDF_MIN_MAX(int& seed, float max, float min) {
	if (abs(min) > abs(max))
	{
		float swap = min;
		min = max;
		max = swap;
	}
	int value = static_cast<int>((max - min) * 10000000);
	if (max > 0)
	{
		value++;
		__int32 MAX = (-value) % value;
		int i = 0;
		
		while (true)
		{
			__int32 r = xorshift(seed);
			if (r >= MAX)
			{
				return ((r % value) * 0.0000001f + min);
			}
			else
				return(-r % value) * 0.0000001f + max;

			
		}
	}
	else
	{
		value--;
		__int32 MAX = (-value) % value;
	
		while (true)
		{
			__int32 r = xorshift(seed);
			if (r >= MAX)
				return (-(r % value) * 0.0000001f + min);
			else
				return(-r % value) * 0.0000001f + max;
		}
			
		
			
	}
}