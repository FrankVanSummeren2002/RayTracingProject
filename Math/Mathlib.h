#pragma once
#define min(a,b) a < b ? a : b;
#define max(a,b) a > b ? a : b;
#define PI 3.14159265359
#include <cmath>
class vec3;
namespace math
{
	vec3 MINvec(vec3 v, float min);
	vec3 MAXvec(vec3& v, float max);
	int clampI(int x, int a, int b);
	vec3 Vecclamp(vec3 v,float min,float max);
	float ABS(float);
	vec3 ABS(vec3);
	float clamp(float x, float a, float b);

	vec3 FacingNormal(vec3 v, vec3& n);
	vec3 refract(vec3& I, vec3 N, float ior, float Tor, bool front);
	float reflectionRate(vec3& I, vec3 N, float ior, float Tor);
	vec3 ranVecGen(int& seed,float max, float min);
	float distanceLength(vec3& v, vec3& b);
	int xorshift(int& state);
	int RANDI_MIN_MAX(int& seed, __int32 max, __int32 min);
	float RANDF_MIN_MAX(int& seed, float max, float min);
}