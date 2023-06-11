#pragma once
#include "Shapes.h"
/*
class Triangle :
    public Shapes
{
    float x;
    float y;
    float z;
    float height;
    vec3 Normals[3];
    vec3 Points[6];
    float SizeOfSide;
    void CalcPoints();
    void calcNormals();
public:
    Triangle(float x, float y, float z,float height, vec3 C, vec3 Col, Material::material m, vec3 Absorbtion = vec3(0,0,0),
        Material::material m2 = Material::material::TheVoid, float firstMatPercentage = 1);
    bool hit(Ray* r, float& currentT, vec3& normal, vec3& IntP, vec3& Col);
    bool Intersection(Ray* r, float& currentT, vec3& normal, vec3& IntP, vec3& Col);
    int planeinter(Ray* r, vec3 P,vec3 N);
};

*/