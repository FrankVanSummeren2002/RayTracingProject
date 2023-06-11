#include"precomp.h"
#include "Ray.h"

void Ray::setOr(vec3& v)
{
	origin = v;
}

Ray::Ray(vec3 eye)
{

	origin = eye;
    for (int i = 0; i < RECURSIONCAP; i++)
    {
        RefractIndex[i] = 1000;
    }
	
}

void Ray::Init(vec3 screen)
{
	ray = screen - origin;
	ray.normalize();
}

void Ray::ClearIndex()
{
    for (int i = 0; i < RECURSIONCAP; i++)
    {
        RefractIndex[i] = 1000;
    }
    INDEXSIZE = -1;
    inside = false;
}

void Ray::DeleteLastIndex()
{
    RefractIndex[INDEXSIZE] = 1000;
    INDEXSIZE--;
}
int Ray::GetLast()
{
    if (INDEXSIZE != -1)
    {
        return RefractIndex[INDEXSIZE];
    }
    else
    {
        return -1000;
    }
}

void Ray::AddIndex(int index)
{
    for (int i = 0; i < RECURSIONCAP; i++)
    {
        if (RefractIndex[i] == 1000)
        {
            RefractIndex[i] = index;
            INDEXSIZE++;
            break;
        }
    }
   
}

vec3 Ray::getOrigin()
{
	return origin;
}

vec3 Ray::getDir()
{
	return ray;
}

void Ray::setDir(vec3& v)
{
	ray = v;
}


vec3 Ray::at(float T)
{
	return origin + ray * T;
}
