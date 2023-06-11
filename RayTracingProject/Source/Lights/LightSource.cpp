#include"precomp.h"
#include "Lights/LightSource.h"
 vec3 LightSource::GetPoint(int& seed)
{
	return Point;
}
LightSource::LightSource(vec3 center,vec3 Color,float Brightness)
{
	Brightnes = Brightness;
	Point = center;
	col = Color;
	
}

LightSource::LightSource()
{
}
