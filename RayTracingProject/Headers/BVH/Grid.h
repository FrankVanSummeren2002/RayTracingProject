#pragma once
#include "precomp.h"
#include "Shapes/Shapes.h"
#include "BVHnode.h"
class Grid
{
	BVHnode* root;

public:
	void createBHV(Shapes* shape[100]);
	bool BVH(Ray* ray, int& index, float& t, vec3& normal, vec3& intP, vec3& Col,int refract,int SKIP = -1);
	int index[100];
	Shapes* shapes[100];
};


