#pragma once
#include "precomp.h"
#include "Shapes/AABB.h"
class Grid;
class BVHnode
{
	Grid* grid;

	BVHnode* child[2];
	int first;
	int count;
	bool leaf;

	int sortingArray(vec3 P,vec3 N);
	bool LeftNotLeft(vec3 C,vec3 P,vec3 );
public:
	AABB bounds;
   bool BVHCollision(Ray* ray, int& index, float& t, vec3& normal, vec3& intP, vec3& Col,int refract,int SKIP = -1);
	BVHnode(Grid* g, int first, int count);
	bool shapeCollision(Ray* ray, int& index, float& t, vec3& normal, vec3& intP, vec3& Col,int refract,int SKIP = -1);
};