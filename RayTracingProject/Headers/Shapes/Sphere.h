#pragma once
#include "Shapes.h"
class Sphere : public Shapes
{
    float radius = 0;
    
public:
    Sphere(float Radius, vec3 center, vec3 COLOR, Material::material mat, vec3 Absorbtion = vec3(0, 0, 0)
        , Material::material m2 = Material::material::TheVoid,float FristMatPercentage = 1);
    float detection(Ray* r, vec3& normal);
    bool hit(Ray* r, float& currentT, vec3& normal, vec3& IntP,vec3& Col);
    bool RefracHit(Ray* r, float& currentT, vec3& normal, vec3& IntP);
    void getPos(vec3& C, float& length);
    vec3 getNormal(vec3& v);
    vec3 getRadius();

    void setRadius(float x);


};

