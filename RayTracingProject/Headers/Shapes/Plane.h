#pragma once
#include "Shapes.h"
class plane : public Shapes
{
    float d = 0;

    vec3 U, V;
    vec3 Col2;
    void setUV(vec3 P2, vec3 P3);
    void setNormal(vec3 P2, vec3 P3);
    bool Grid;
public:
    bool intersectPlane(vec3& l0, vec3& l, float& t,vec3& N);
    bool hit(Ray* r, float& currentT, vec3& normal, vec3& IntP,vec3& Col);

    plane();
    plane(vec3 A, vec3 B, vec3 C, vec3 Col, Material::material mat, bool Text, vec3 Color2,vec3 Aborbsion = vec3(0, 0, 0),Material::material m2 = Material::material::TheVoid,
        float FristMatPercentage = 1, float length = 0, float height = 0, float width = 0);
    plane(vec3& N, vec3& P, vec3 Col, Material::material mat, bool Text,vec3 Color2, vec3 Aborbsion = vec3(0, 0, 0), Material::material m2 = Material::material::TheVoid,
        float FristMatPercentage = 1,float length = 0,float height = 0,float width = 0);
    bool RefracHit(Ray* r, float& currentT, vec3& normal, vec3& IntP);
    vec3 Normal;
};
