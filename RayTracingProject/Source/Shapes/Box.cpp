#include"precomp.h"
#include "Shapes/Box.h"

Box::Box(float width, float height, float depth, vec3 Cent, vec3 Cx, Material::material m, vec3 Absorbtion, int degreesX, int degreesY, int degreesZ, bool MultiCol,
    vec3 Cy,vec3 Cz, Material::material m2, float firstMatPercentage)
{
    Absorb = math::Vecclamp(Absorbtion,0,1);
    FirstMatPercentage = firstMatPercentage;
    SecondMat = m2;
    material = m;
    if (MultiCol == false)
    {
        Colxyz[0] = Cx;
        Colxyz[1] = Cx;
        Colxyz[2] = Cx;
    }
    else
    {
        Colxyz[0] = Cx;
        Colxyz[1] = Cy;
        Colxyz[2] = Cz;
    }  
    Center = Cent;
    Matrix matrix = Matrix(Matrix::MatSizes::THREE_THREE);
    vec3 XN = vec3(1, 0, 0);
    vec3 YN = vec3(0, 1, 0);
    vec3 ZN = vec3(0, 0, 1);
    if (degreesX != 0)
    {
        matrix.rotationMatrixX(degreesX);
        matrix.rotateAxis(ZN);
        matrix.rotateAxis(YN);
        YN.z = -YN.z;
        matrix.rotateAxis(XN);
        rotated = true;
    }
    if (degreesY != 0)
    {
        matrix.rotationMatrixY(degreesY);
        matrix.rotateAxis(ZN);
        matrix.rotateAxis(YN);
        matrix.rotateAxis(XN);
        rotated = true;
    }
    if (degreesZ != 0)
    {
        matrix.rotationMatrixZ(degreesZ);
        matrix.rotateAxis(ZN);
        matrix.rotateAxis(YN);
        matrix.rotateAxis(XN);
        rotated = true;
    }
   
    
    radius = vec3(width,height,depth);
    Axis[0] = XN;
    Axis[1] = YN;
    Axis[2] = ZN;
    //the BVH needs to get to the width height and depth of the box to create the AABB but because i rotate it i need change the Radius
    //because the OBB might stick out of the AABB
    if (rotated == true)
    {
        vec3 Min, Max;
        for (int i = 0; i < 3; i++)
        {
            vec3 length = (Axis[i] * radius.vec[i]);
            Min.vec[i] =  length.getlength();
            Max.vec[i] =  - length.getlength();
        }
        Radius = math::ABS(Min) + math::ABS(Max);
    }
    else
        Radius = radius;
}
bool Box::hit(Ray* r, float& currentT, vec3& normal, vec3& intP,vec3& color)
{
    vec3 Col;
    if (rotated == false)
    {
        float tMax = 100000;
        float Tmin = -10000000;
        float t0;
        float t1;
        int index = 0;
        vec3 O = r->getOrigin();
        vec3 Dir = r->getDir();
        vec3 CO = Center - O;
        for (int i = 0; i < 3; i++)
        {
            float division = 1 / Dir.vec[i];

            t0 = (Center.vec[i] + radius.vec[i] - O.vec[i]) * division;
            t1 = (Center.vec[i] - radius.vec[i] - O.vec[i]) * division;

            if (t0 < 0 && t1 < 0)
                return false;
            if (t0 > t1)
            {
                float swap = t1;
                t1 = t0;
                t0 = swap;
            }
            if (t0 > Tmin)
            {
                index = i;
                Tmin = t0;
            }
            if (t1 < tMax)
            {
                tMax = t1;
            }

        }

        if (tMax < Tmin)
            return false;

        float t;
        if (Tmin > 0)
            t = Tmin;
        else
            t = tMax;
        if (t < currentT || currentT == -1)
        {
            currentT = t;
        }
        else
        {
            return false;
        }
        vec3  temp = r->at(currentT);
        vec3 Point;
        float sign = 1;
        color = Colxyz[index];
        for (int j = 0; j < 2; j++)
        {
            for (int i = 0; i < 3; i++)
            {
                Point = Center + Axis[i] * radius.vec[i] * sign;
                vec3 Line = (temp - Point);
                float Onplane = Line.dotproduct(Axis[i]);
                if (Onplane  < 0.0001 && Onplane > -0.0001)
                {
                    normal = Axis[i] * sign;
                }
            }
            sign *= -1;
        }
        normal;

        intP = r->at(currentT) + normal * 0.001;
        return true;
        //making sure min is closest to the ray*/

    }
    ///
    ///
    /// 
    /// 
    /// 
    //the rotated box part
    ///
    ///
    ///
    ///
    /// 
    else 
{
        float tMax = 100000000;
        float Tmin = -10000000;
        float t0;
        float t1;
        int index = 0;
        vec3 O = r->getOrigin();
        vec3 Dir = r->getDir();
        vec3 CO = Center - O;
        for (int i = 0; i < 3; i++)
        {
            float angle = Axis[i].dotproduct(CO);
            float temp2 = Dir.dotproduct(Axis[i]);
            float division = 1 / temp2;
            //ray is parrallel to axis and is outside of the box
            if (math::ABS(temp2) < 0.001)
            {
                if (-angle - radius.vec[i] < 0 && -angle + radius.vec[i] < 0)
                    return false;
            }

            t0 = (angle + radius.vec[i]) * division; 
            t1 = (angle - radius.vec[i]) * division;

            if (t0 < 0 && t1 < 0)
                return false;
            if (t0 > t1)
            {
                float swap = t1;    
                t1 = t0;
                t0 = swap;
            }
            if (t0 > Tmin)
            {
                index = i;
                Tmin = t0;
            }
            if (t1 < tMax)
                tMax = t1;
         
        }

        if (tMax < Tmin)
            return false;

       

        float t;
        if (Tmin > 0)
            t = Tmin;
        else
            t = tMax;

        if (t < currentT || currentT == -1)
            currentT = t;
        else
            return false;
 
        color = Colxyz[index];
        vec3  hitpoint = r->at(currentT);
        vec3 Point;
        float sign = 1;
        //do it once with possitive axis and once with negative axis
        for (int j = 0; j < 2; j++)
        {
            //check for each axis to see which one is closest to the point
            for (int i = 0; i < 3; i++)
            {
                Point = Center + Axis[i] * radius.vec[i] * sign;
                vec3 Line = (hitpoint - Point);
                float Onplane = Line.dotproduct(Axis[i]);
                if (Onplane  < 0.0001 && Onplane > -0.0001)
                {
                    normal = Axis[i] * sign;
                }
            }
            sign *= -1;
        }
        normal;

        intP = r->at(currentT) + normal * 0.001;
        return true;
    }
}

bool Box::RefracHit(Ray* r, float& currentT, vec3& normal, vec3& intP)
{
    float tMax = 100000000;
    float Tmin = -10000000;
    float t0;
    float t1;
    int index;
    vec3 O = r->getOrigin();
    vec3 Dir = r->getDir();
    vec3 CO = Center - O;
    for (int i = 0; i < 3; i++)
    {
        float temp = Axis[i].dotproduct(CO);
        float temp2 = Dir.dotproduct(Axis[i]);
        float division = 1 / temp2;
        //ray is parrallel to axis
        if (math::ABS(temp2) < 0.001)
        {
            if (-temp - radius.vec[i] < 0 && -temp + radius.vec[i] < 0)
                return false;
        }

        t0 = (temp + radius.vec[i]) * division;
        t1 = (temp - radius.vec[i]) * division;
        if (t0 > t1)
        {
            float swap = t1;
            t1 = t0;
            t0 = swap;
        }
        if (t0 > Tmin)
        {
            index = i;
            Tmin = t0;
        }
        if (t1 < tMax)
        {
            tMax = t1;
        }
    }

    if (tMax < Tmin)
        return false;


    if (Tmin > 0)
        currentT = Tmin;
    else
        currentT = tMax;

    vec3  hitpoint = r->at(currentT);
    vec3 Point;
    float sign = 1;

    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            Point = Center + Axis[i] * radius.vec[i] * sign;
            vec3 Line = (hitpoint - Point);
            float Onplane = Line.dotproduct(Axis[i]);
            if (Onplane  < 0.0001 && Onplane > -0.0001)
            {
                normal = Axis[i] * sign;
            }
        }
        sign *= -1;
    }
    normal;

    intP = r->at(currentT) + normal * 0.001;
    return true;

 
}

float Box::SideInter(vec3& l0, vec3& l, vec3& normal, vec3& P)
{
    float angle = -l.dotproduct(normal);

    vec3 Line = l0 - P;
    return normal.dotproduct(Line) / angle;
}

vec3 Box::getRadius()
{
    return Radius;
}
