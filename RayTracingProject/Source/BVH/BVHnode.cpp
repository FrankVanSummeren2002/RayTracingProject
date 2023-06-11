#include "precomp.h"
#include "BVH/BVHnode.h"
#include "BVH/Grid.h"
#include "Ray.h"

BVHnode::BVHnode(Grid* g,int f,int c)
{
	count = c;
	//making sure the count doesnt go over the bounds 
	if (count >= ARRAYSIZE)
	{
		count = 99;
	}
	first = f;
	grid = g;
	//creating the AABB
	bounds = AABB(grid->shapes, first, count, grid->index);

	int edge = 0;
	float SizeDif = -1;
	float SizeXCount = (count+1) * bounds.radius.vec[0] * bounds.radius.vec[1] * bounds.radius.vec[2];
	float LeftSize;
	float RightSize;
	if (count == 0)
	{
		leaf = true;
	}
	else
	{
		//checks the efficienty of a splitplane on the center of an object for all three sides 
		vec3 Point;
		vec3 Normal;
		for (int i = 0; i <= count; i++)
		{
			vec3 P = grid->shapes[grid->index[i]]->Center;
			for (int j = 0; j < 3; j++)
			{
				vec3 N;
				N.vec[j] = 1;
				edge = sortingArray(P, N);
				AABB left(grid->shapes, first, edge - 1, grid->index);
				LeftSize = (edge) * left.radius.vec[0] * left.radius.vec[1] * left.radius.vec[2];
				AABB right(grid->shapes, first + edge, count - edge, grid->index);
				RightSize = (count - edge+1) * right.radius.vec[0] * right.radius.vec[1] * right.radius.vec[2];
				float temp = SizeXCount - (LeftSize + RightSize);
				if (temp > SizeDif)
				{
					SizeDif = temp;
					Point = P;
					Normal = N;
				}
			}
		}
		//if there is an possible split that has effect then use the best possible point and normal else become a leaf
		if (SizeDif > 0)
		{
			edge = sortingArray(Point, Normal);
		}
		else
		{
			leaf = true;
		}
	}

	if (leaf == false)
	{
			child[0] = new BVHnode(g, first, edge-1);
			child[1] = new BVHnode(g, first + edge,count- edge);
	}
	else
	{
		child[0] = nullptr;
		child[1] = nullptr;
	}
}

bool BVHnode::shapeCollision(Ray* ray, int& index,float& t,vec3& normal,vec3& intP,vec3& Col, int Refract,int SKIP)
{
	int Index;
	bool hit = false;
	for (int i = first; i <= first + count; i++)
	{
		Index = grid->index[i];
		//this is mainly used for lighting so you can skip intersection with itself
		if (Index == SKIP)
		{
			continue;
		}
		//Refract is the last refraction index from the ray class
		if (Refract == Index)
		{
			if (grid->shapes[grid->index[i]]->RefracHit(ray, t, normal, intP) == true)
			{
				hit = true;
				index = Index;
			}
		}
		else
		{
			if (grid->shapes[grid->index[i]]->hit(ray, t, normal, intP, Col) == true)
			{
				hit = true;
				index = Index;
			}
		}
		
	}
	return hit;
}

bool BVHnode::BVHCollision(Ray* ray, int& index, float& t, vec3& normal, vec3& intP, vec3& Col,int refract,int SKIP)
{
	bool hit1 = false;
	bool hit2 = false;
	float t1 = -1;
	float t2 = -1;

	if (leaf == true)
	{
		//function to check collision between shapes
		return shapeCollision(ray, index,t,normal,intP,Col,refract,SKIP);
	}
		hit1 = child[0]->bounds.intersection(ray,t1);
		hit2 = child[1]->bounds.intersection(ray,t2);

	// hit 1 and 2 false == no hits
	if (hit1 == false && hit2 == false)
		return false;
	
	// one of them hit check collision with that
	if (hit1 == false && hit2 == true)
	return child[1]->BVHCollision(ray, index, t, normal, intP, Col,refract,SKIP);

	if (hit1 == true && hit2 == false)
	return child[0]->BVHCollision(ray, index, t, normal, intP, Col,refract,SKIP);

	// two of them hit check both and  keep the lowest intersection value
	if (hit1 == true && hit2 == true)
	{
			hit1 = child[0]->BVHCollision(ray, index, t, normal, intP, Col,refract, SKIP);
			hit2 = child[1]->BVHCollision(ray, index, t, normal, intP, Col,refract, SKIP);
			if (hit1 == true || hit2 == true)
				return true;
	}
	return false;
}

int BVHnode::sortingArray(vec3 P, vec3 N)
{
	int LeftAmount = 0;
	int RightAmount = 0;
	int buffer = 0;
	int buffer2 = 0;
	int emptyLocation = 0;
	bool Left = false;
	bool bufferFull = false;
	while (LeftAmount+RightAmount < count+bufferFull)
	{
		//if the buffer is full we have to clean it out before we can go to the next shape
		if (bufferFull == true)
		{
			Left = LeftNotLeft(grid->shapes[buffer]->Center, P, N);
			//if the buffer is on the left we can just place in the empty location
			if (Left == true)
			{
				grid->index[emptyLocation] = buffer;
				LeftAmount++;
				bufferFull = false;
			}
			//if it is not left we have to place the index in the back of the array
			//and we then place the value that is in the back in the buffer
			else
			{
				buffer2 = buffer;
				buffer = grid->index[first + count - RightAmount];
				grid->index[first + count - RightAmount] = buffer2;
				RightAmount++;
			}
		}
		//if the buffer is empty we check the next one.
		else
		{
			Left = LeftNotLeft(grid->shapes[grid->index[first + LeftAmount]]->Center, P, N);
			//if it is not on the left place it in the back and place the one thats in the back into the buffer
			//and remember the now empty location
			if (Left == false)
			{
				emptyLocation = first + LeftAmount;
				buffer = grid->index[first + count - RightAmount];
				
				grid->index[first + count - RightAmount] = grid->index[first + LeftAmount];
				RightAmount++;
				bufferFull = true;
			}
			//is already in right position so leave it
			else
			{
				LeftAmount++;
			}
		}
	}
	return LeftAmount;
}

bool BVHnode::LeftNotLeft(vec3 C, vec3 P, vec3 N)
{
	//check the angle from the point to the plane center to see if the angle
	vec3 Temp = P - C;
	float denom = Temp.dotproduct(N);
	if (denom > 0)
	{
		return true;
	}
	return false;
}


