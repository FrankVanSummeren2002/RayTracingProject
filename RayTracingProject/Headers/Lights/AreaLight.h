#pragma once
#include "precomp.h"
#include "lightsource.h"
#include "Shapes/Shapes.h"
class AreaLight :
    public LightSource, public Shapes
{
    Shapes* Shape;
public:
    AreaLight(Shapes* shape, float Brightnes);
    bool hit(Ray* r, float& currenT, vec3& normal, vec3& IntP, vec3& Col);
    vec3 GetPoint(int& seed);
    void getPos(vec3& C, float& length);
    vec3 getRadius();
    vec3 getCenter();
};

