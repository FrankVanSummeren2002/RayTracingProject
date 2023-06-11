#include"precomp.h"
#include "Shapes/AABB.h"

bool AABB::intersection(Ray* r, float& currentT)
{
    vec3 normal;
    float tMax = 100000;
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
        //ray is parrallel to axis
        if (math::ABS(temp2) < 0.001)
        {
            if (-temp - radius.vec[i] < 0 && -temp + radius.vec[i] < 0)
                return false;
        }

        t0 = (temp + radius.vec[i]) / temp2;
        t1 = (temp - radius.vec[i]) / temp2;
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
 
    if (Tmin > 0)
        currentT = Tmin;
    else
        currentT = tMax;

    return true;
}

AABB::AABB()
{
}

AABB::AABB(Shapes** shapes,int first,int count,int* index)
{
    //for x,y,z
    int size = first + count;
    if (size + 1 < ARRAYSIZE)
    {
        size++;
    }
    for (int i = 0; i < 3; i++)
    {
        Max.vec[i] = shapes[index[first]]->getCenter().vec[i] + shapes[index[first]]->getRadius().vec[i];
        Min.vec[i] = shapes[index[first]]->getCenter().vec[i] - shapes[index[first]]->getRadius().vec[i];
        for (int j = first; j < size; j++)
        {

            if(Max.vec[i] < (shapes[index[j]]->getCenter().vec[i]+shapes[index[j]]->getRadius().vec[i]))
            Max.vec[i] = shapes[index[j]]->getCenter().vec[i]+shapes[index[j]]->getRadius().vec[i];

            if(Min.vec[i] > (shapes[index[j]]->getCenter().vec[i]-shapes[index[j]]->getRadius().vec[i]) )
            Min.vec[i] = shapes[index[j]]->getCenter().vec[i]-shapes[index[j]]->getRadius().vec[i];
        }
    }
    Center = (Min  + Max)* 0.5;
    
    radius = math::ABS(Center - Min);
    //radius  Center;
}
