#pragma once
#include "precomp.h"
#include "Shapes.h"
class Box : public Shapes
{
   vec3 Axis[3];

    vec3 Colxyz[3];

    vec3 radius;
    bool rotated = false;
public:
    Box(float x, float y, float z, vec3 Cent, vec3 Cx, Material::material m, vec3 Absorbtion = vec3(0, 0, 0),
        int degreesX = 0,int degreesY = 0,int degreesZ = 0, bool MultiCol = false, vec3 Cy = WHITE, vec3 Cz = WHITE,
        Material::material m2 = Material::material::TheVoid,float FristMatPercentage = 1);
  
    bool hit(Ray* r, float& currentT, vec3& normal, vec3& IntP,vec3& Col);
    bool RefracHit(Ray* r, float& currentT, vec3& normal, vec3& intP);
    float SideInter(vec3& l0, vec3& l, vec3& normal, vec3& P);
    vec3 getRadius();
};