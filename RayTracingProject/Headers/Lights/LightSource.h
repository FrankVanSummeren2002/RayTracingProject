#pragma once
#include "precomp.h"
class LightSource
{
	vec3 Point;
public:
	float MaxDistance = 500;
	float Brightnes = 0;
	
	vec3 col;
	virtual vec3 GetPoint(int& seed);
	LightSource(vec3 center,vec3 Color,float Brightness);
	LightSource();
};

