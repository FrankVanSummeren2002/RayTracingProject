#include"precomp.h"
#include "Shapes/Shapes.h"

bool Shapes::hit(Ray* r, float& currentT, vec3& normal, vec3& IntP,vec3& Col) { return false; }

bool Shapes::RefracHit(Ray* r, float& currentT, vec3& normal, vec3& IntP)
{
    return false;
}
void Shapes::getPos(vec3& C, float& length)
{
}
vec3 Shapes::getCenter()
{
    return Center;
}
vec3 Shapes::getRadius()
{

    return Radius;
}
void Shapes::setRadius(float x)
{
}
;










