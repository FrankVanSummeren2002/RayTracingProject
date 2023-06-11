#pragma once
#include "precomp.h"
#ifndef RAY
#define RAY


class Ray
{
	vec3 origin;
	vec3 ray;
	int INDEXSIZE = -1;
	
public:
	bool inside = false;
	int RefractIndex[RECURSIONCAP];
	void DeleteLastIndex();
	int GetLast();
	void AddIndex(int index);
	void ClearIndex();
	vec3 getOrigin();
	vec3 getDir();
	void setDir(vec3& v);
	void setOr(vec3& v);
	Ray(vec3 eye);
	
	void Init(vec3 screen);



	vec3 at(float T);

};
#endif
