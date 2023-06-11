#include "precomp.h"
#include "Lights/AreaLight.h"

bool AreaLight::hit(Ray* r,float& currenT,vec3& normal,vec3& IntP,vec3& Col)
{
    bool tempbool = Shape->hit(r,currenT,normal,IntP,Col);
    if (tempbool == true)
    {
        Col = Col * Brightnes;
    }
    return tempbool;
}
vec3 AreaLight::GetPoint(int& seed)
{
    vec3 C = Shape->Center;
    vec3 R = Shape->getRadius();
    vec3 P;
    
    while (true)
    {
        for (int i = 0; i < 3; i++)
        {
            if(R.vec[i] != 0)
            P.vec[i] = math::RANDF_MIN_MAX(seed, R.vec[i]*0.25f, -R.vec[i]*0.25f);

        }
        if (P.lengthSqaured() < R.x)
            return C + P;
    }
}

void AreaLight::getPos(vec3& C, float& length)
{
    Shape->getPos(C,length);
}
vec3 AreaLight::getRadius()
{
    return Shape->getRadius();
}
vec3 AreaLight::getCenter()
{
    return Shape->getCenter();
}

AreaLight::AreaLight(Shapes* shape, float Brightness)
{
    Shape = shape;
    material = Material::material::light;
    Brightnes = Brightness;
    col = shape->Color;
    FirstMatPercentage = 1;
}
