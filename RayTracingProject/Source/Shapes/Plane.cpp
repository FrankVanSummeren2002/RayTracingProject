#include "precomp.h"
#include "Shapes/Plane.h"

void plane::setUV(vec3 P2,vec3 P3)
{
    U = P2 - Center;
    V = P3 - Center;
}
void plane::setNormal(vec3 P2,vec3 P3)
{
    setUV(P2,P3);
    Normal = U.crossprod(V);
    Normal.normalize();

}
plane::plane(vec3 A, vec3 B, vec3 C, vec3 Col, Material::material mat, bool Text,vec3 col2, vec3 Absorbtion,
    Material::material m2,float firstMatPercentage, float length, float height, float width)
{
    Absorb = Absorbtion;
    FirstMatPercentage = firstMatPercentage;
    SecondMat = m2;
    material = mat;
    Center = A;
    setNormal(B,C);

    Color = Col;
    Col2 = col2;
    Grid = Text;
    Radius.x = length;
    Radius.y = height;
    Radius.z = width;
}
plane::plane(vec3& N, vec3& P, vec3 Col,  Material::material mat, bool Text,vec3 color2, vec3 Absorbtion,
    Material::material m2, float firstMatPercentage,float length, float height, float width)
{
    Absorb = Absorbtion;
    FirstMatPercentage = firstMatPercentage;
    SecondMat = m2;
    material = mat;
    Normal = N;
    Center = P;
    Color = Col;
    Grid = Text;
    Col2 = color2;
    Radius.x = length;
    Radius.y = height;
    Radius.z = width;
}

plane::plane() { Grid = false; }
bool plane::hit(Ray* r, float& currentT, vec3& normal, vec3& IntP,vec3& Col)
{
    Texture text;
    float i = 0;
    vec3 origin = r->getOrigin();
    vec3 dir = r->getDir();
    vec3 TempNormal;
    if (intersectPlane(origin, dir, i,TempNormal) == false)
    {
        return false;
    }
    if (i > 0.0)
    {
        if ((i < currentT || currentT == -1))
        {
            IntP = r->at(i);
            //possible for quads
            for (int j = 0; j < 3; j++)
            {
                //smaller or equal to 0 means that the quad does not have a limit 
                if (Radius.vec[j] > 0)
                {
                    if (math::ABS(IntP.vec[j] - Center.vec[j]) > Radius.vec[j])
                    {
                        return false;
                    }
                }

              
            }

            currentT = i;
            
            
            normal = TempNormal;
            if (Grid == true)
            {
                if (text.grid(IntP.x, IntP.z) == true)
                {
                    Col = Col2;
                }
                else
                {
                    Col = Color;
                }
            }
            else
            {
                Col = Color;
            }
            return true;
        }
    }
    return false;
}

bool plane::intersectPlane(vec3& Origin, vec3& Dir, float& t,vec3& normal)
{
   
    float angle = Dir.dotproduct(Normal);
    vec3 PO = Center - Origin;
    t = Normal.dotproduct(PO) / angle;
    if (angle > 0.0001)
    {
        normal = -Normal;
    }
    else
    {
        normal = Normal;
    }
    return true;
}
bool plane::RefracHit(Ray* r, float& currentT, vec3& normal, vec3& IntP)
{
    //planes don't really refract because they are to thin
    return false;
}
