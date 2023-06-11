#pragma once
#include "precomp.h"
#include "Ray.h"
#include "textures.h"
class Shapes
{
	
public:
    Material::material material = Material::material::TheVoid;
    Material::material SecondMat = Material::material::TheVoid;
    float FirstMatPercentage = 1;
    vec3 Radius;
    vec3 Color;
    vec3 Center{ 0,0,0 };
    vec3 Absorb;

    virtual bool hit(Ray* r, float& currentT,vec3& normal,vec3& IntP,vec3& Col);
    virtual bool RefracHit(Ray* r, float& currentT, vec3& normal, vec3& IntP);
    virtual void getPos(vec3& C, float& length);
    virtual vec3 getCenter();
    virtual vec3 getRadius();
    virtual void setRadius(float x);
};






