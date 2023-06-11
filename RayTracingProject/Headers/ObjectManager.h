#pragma once
#include"precomp.h"
#include "Shapes/Shapes.h"
#include "Ray.h"
#include "Lights/LightSource.h"
#include "Shapes/plane.h"
#include "BVH/Grid.h"
#include "Lights/AreaLight.h"
class ObjectManager
{
	Shapes* BVHshape[ARRAYSIZE];
	Shapes* NonBVHShapes[ARRAYSIZE];
	sf::Image image;
	sf::Texture text;
	LightSource* light[ARRAYSIZE];
	vec3 voidcolor;
public:
	void SetVoidColor(vec3 Color);
	vec3 VoidImage(Ray* r);
	void createBVH();
	Grid grid;
	vec3 RayColor(Ray* r,int MaxRays,int& seed);
	void AddShape(Shapes* x,bool BVH);
	void AddPointLight(LightSource* x);

	void AddAreaLight(AreaLight* x, bool BVH);
	
	ObjectManager();
	vec3 lighthit(Ray* r,float& Inter,vec3& normal,int NMB,int& seed);
	vec3 RandomDir(int& seed);
	vec3 Diffuse(Ray* r, float intersectingpoint, vec3 normal, Material::material mat,int index, vec3 color,int maxRay,int& seed);
	vec3 Refract(Ray* r, vec3 IntP, vec3 normal, int index, int MaxRays,int& seed);
	
	vec3 Reflect(Ray* r, vec3 IntP, vec3 normal, int maxRays, int& seed, int index);

	vec3 GlossyReflect(Ray* r, vec3 IntP, vec3 normal, int maxRays, int& seed, int index);
};

