#include"precomp.h"
#include "BVH/Grid.h"

void Grid::createBHV(Shapes* shape[100])
{
	int i = 0;
	while (shape[i] != nullptr)
	{
		index[i] = i;
		i++;
	}
	for (int j = 0; j < i; j++)
	{
		shapes[j] = shape[j];
	}
	delete root;
	root = new BVHnode(this,0,i-1);
}

bool Grid::BVH(Ray* ray, int& Index, float& t, vec3& normal, vec3& intP, vec3& Col,int refract,int SKIP)
{
	//if there are no shapes in the BVH return
	if (shapes[0] == nullptr)
	{
		return false;
	}

	if (root->bounds.intersection(ray, t) == true)
	{
		t = -1;
		return root->BVHCollision(ray, Index, t, normal, intP, Col,refract,SKIP);
	}
	return false;
}

