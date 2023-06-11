#include "precomp.h"
#include "Shapes/Triangle.h"
/*
void Triangle::CalcPoints()
{
	Points[0] = Center;
	Points[0].y -= height;
	Points[1] = Center;
	Points[1].y += height;

	Points[2] = Points[1];
	Points[2].x += x;
	Points[2].z += z;

	int sign = 1;
	int sign2 = 1;
	for (int i = 2; i < 6; i++)
	{
		Points[i] = Points[1];
		Points[i].x += x * sign;
		Points[i].z += z * sign2;
		
		//the if statement will make it so that the end result will be +--+
		if (i % 2 == 0)
			sign2 *= -1;

		sign *= -1;
	}
}

void Triangle::calcNormals()
{
	if (Points[0].y > Points[1].y)
		Normals[0] = vec3(0, -1, 0);
	else
		Normals[1] = vec3(0, 1, 0);


	vec3 U = Points[2] - Points[0];
	vec3 V = Points[4] - Points[0];
	Normals[1] = V.crossprod(U);
	Normals[2] = -Normals[1];

	vec3 V = Points[3] - Points[0];
	Normals[3] = V.crossprod(U);
	Normals[4] = -Normals[1];
}


Triangle::Triangle(float X, float Y, float Z, float Height, vec3 C, vec3 Col, Material::material m, vec3 Absorbtion, Material::material m2, float firstMatPercentage)
{
	x = X;
	y = Y;
	z = Z;
	height = Height;

	Center = C;
	Color = Col;
	material = m;
	SecondMat = m2;
	CalcPoints();
	calcNormals();
}

bool Triangle::hit(Ray* r, float& currentT, vec3& normal, vec3& IntP, vec3& Col)
{
	if (Intersection(r, currentT, normal, IntP, Col) == true)
	{

	}
	
}

bool Triangle::Intersection(Ray* r, float& currentT, vec3& normal, vec3& IntP, vec3& Col)
{
	//check the quad
	/*float FinalT;
	float tempt = planeinter(r, Points[1], Normals[0]);
	vec3 Inter = r->at(tempt);
	
	if (math::ABS(Inter.x - Points[1].x) < x && (Inter.z - Points[1].z) < z)
    {
		FinalT = tempt;
	}
	
	float tempt = planeinter(r, Points[1], Normals[0]);
	vec3 Inter = r->at(tempt);
	vec3 tempvec;
	float lengthLR;
	float lengthLT;
	float lengthIT;
	float lengthIR;
	float lengthIL;
	float Area1, Area2, Area3, Area4;
	//checking the edges
		tempt = planeinter(r, (Points[2] + Points[4])*0.5, Normals[1]);
		Inter = r->at(tempt);

		tempvec = (Points[2] - Points[4]);
		lengthLR = tempvec.getlength();
		tempvec =Points[0] - Points[2];
		lengthLT = tempvec.getlength();
		tempvec = (Points[2] - Points[4]);


		tempvec = (Inter - Points[2]);
		lengthIL = tempvec.getlength();
		tempvec = (Inter - Points[4]);
		lengthIR = tempvec.getlength();
		tempvec = (Inter - Points[0]);
		lengthIT = tempvec.getlength();

		float Heron = (lengthLR * 2 + lengthLT) * 0.5;
		Area1 = sqrt((Heron * (Heron - lengthLR)) * 2 + Heron * lengthLT);

		float Heron = (lengthLR * 2 + lengthLT) * 0.5;
		Area1 = sqrt((Heron * (Heron - lengthLR)) * 2 + Heron * lengthLT);
	    

}

int Triangle::planeinter(Ray* r, vec3 P, vec3 N)
{
	vec3 Dir = r->getDir();
	vec3 Origin = r->getOrigin();
	float angle = Dir.dotproduct(N);
	vec3 PO = P - Origin;
	return N.dotproduct(PO) / angle;
}

*/