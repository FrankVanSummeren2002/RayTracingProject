#pragma once
#include "precomp.h"
#include "Shapes.h"
class AABB
{

	//constructor creates the boundingbox
	vec3 Center;
	vec3 Axis[3] = { vec3(1, 0, 0),vec3(0, 1, 0),vec3(0, 0, 1) };
	
public:
	vec3 radius;
	bool intersection(Ray* r, float& CurrentT);
	vec3 Min;
	vec3 Max;
	AABB();
	AABB(Shapes** shapes,int first,int count,int* index);
};