#include "precomp.h"
#include "Shapes/Sphere.h"



Sphere::Sphere(float Radius, vec3 center, vec3 COLOR, Material::material mat, vec3 Absorbtion, Material::material m2, float firstMatPercentage)
{
    Absorb = Absorbtion;
    FirstMatPercentage = firstMatPercentage;
    SecondMat = m2;
    Color  = COLOR;
    radius = Radius;
    Center = center;
    material = mat;
}

float Sphere::detection(Ray* r, vec3& normal) 
{
    float temp1 = 0;
    float temp2 = 0;
    vec3 c = Center - r->getOrigin();
    vec3 Dir = r->getDir();
    float t = c.dotproduct(Dir);

    if (t < 0) return -1;

    vec3 q = c - Dir * t;
    float p2 = q.dotproduct(q);

    if (p2 > radius * radius) return -1;

    temp1 = t - sqrt(radius*radius - p2);
    temp2 = t + sqrt(radius * radius - p2);
   
  
    if ((temp1 < temp2 || temp2 < 0) && temp1 >= 0)
        return temp1;
    else
        return temp2;
}

bool Sphere::hit(Ray* r, float& currentT, vec3& normal, vec3& IntP,vec3& Col)
{
    float T = detection(r, normal);
    if (T > 0.0)
    {
        if ((T < currentT || currentT == -1))
        {
            currentT = T;
            Col = Color;
      
            IntP = r->at(T);

            normal = getNormal(IntP);

            return true;
        }
    }
    return false;
}

bool Sphere::RefracHit(Ray* r, float& currentT, vec3& normal, vec3& IntP)
{
    float T = -1;
    float temp1 = 0;
    float temp2 = 0;
    vec3 c = Center - r->getOrigin();
    vec3 Dir = r->getDir();
    float t = c.dotproduct(Dir);

    vec3 q = c - Dir * t;
    float p2 = q.dotproduct(q);

    temp1 = t - sqrt(radius * radius - p2);
    temp2 = t + sqrt(radius * radius - p2);

    if ((temp1 > temp2 || temp2 < 0) && temp1 >= 0)
        T = temp1;
    else if(temp2 >= 0)
        T = temp2;

    if (T > 0.0f && T < currentT)
    {
        currentT = T;
        IntP = r->at(T);
        normal = getNormal(IntP);
        return true;
    }
    return false;

}

void Sphere::getPos(vec3& C, float& length)
{
    C = Center;
    length = radius;
}

vec3 Sphere::getNormal(vec3& v)
{
        vec3 temp = v - Center;
        temp.normalize();
        return temp;
}

vec3 Sphere::getRadius()
{
    return vec3(radius,radius,radius);
}
void Sphere::setRadius(float x)
{
    radius = x;
}