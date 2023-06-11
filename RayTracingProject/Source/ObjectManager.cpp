#include"precomp.h"
#include "ObjectManager.h"
#include "mutex"
#include "BVH/Grid.h"
#include "Shapes/Sphere.h"

#include"thread"
ObjectManager::ObjectManager()
{
	voidcolor = vec3(0, 0, 0);
	grid = Grid();
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		BVHshape[i] = nullptr;
		light[i] = nullptr;
		NonBVHShapes[i] = nullptr;
	}
	image.loadFromFile("assets/background.jpg");
	text.loadFromFile("assets/background.jpg");
}

void ObjectManager::SetVoidColor(vec3 Col)
{
	voidcolor = Col;
}
vec3 ObjectManager::VoidImage(Ray* r)
{
	return voidcolor;
	vec3 Inter = r->at(760);
	Inter = math::ABS(Inter);
	int y = image.getSize().y - math::ABS(Inter.y);
	int x = Inter.x;
	float test = atan2(Inter.x, Inter.z) / (2.f * PI) + 0.5f;
	int u = test * image.getSize().x;
	int v =image.getSize().y - ( Inter.y * 0.5f + 0.5f);
	
	if (x > image.getSize().x|| y > image.getSize().y)
	{
		return BLACK;
	}

	sf::Color col = image.getPixel(u, v);
	vec3 temp(col.r / 255.f, col.g / 255.f, col.b / 255.f);
	return temp;
}
void ObjectManager::createBVH()
{
	if(BVHshape[0] != nullptr)
	grid.createBHV(BVHshape);
}

vec3 ObjectManager::RayColor(Ray* r, int maxRays, int& seed)
{
	maxRays--;
	vec3 Origin = r->getOrigin();
	vec3 Dir = r->getDir();
	vec3 normal;
	float intersectingpoint = -1;
	vec3 color = BLACK;
	vec3 C1, C2;
	float percentage = 1;
	vec3 IntP;
	Material::material mat = Material::material::TheVoid;
	Material::material m2 = Material::material::TheVoid;
	int index = -1;

	if (grid.BVH(r, index, intersectingpoint, normal, IntP, color,r->GetLast()) == true)
	{
		mat = BVHshape[index]->material;
		m2 = BVHshape[index]->SecondMat;
		percentage = BVHshape[index]->FirstMatPercentage;
	
	}

	int RefracIndex = -r->GetLast() - 1;
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		if (NonBVHShapes[i] != nullptr)
		{
			if (RefracIndex != i)
			{
				if (NonBVHShapes[i]->hit(r, intersectingpoint, normal, IntP, color) == true)
				{
					index = -i - 1;
					mat = NonBVHShapes[i]->material;
					m2 = NonBVHShapes[i]->SecondMat;
					percentage = NonBVHShapes[i]->FirstMatPercentage;
				}
			}
			else
			{
				if (NonBVHShapes[i]->RefracHit(r, intersectingpoint, normal, IntP) == true)
				{
				  index = -i - 1;
				  mat = NonBVHShapes[i]->material;
				  m2 = NonBVHShapes[i]->SecondMat;
				  percentage = NonBVHShapes[i]->FirstMatPercentage;
				}
			}

		}
		else
			break;

	}
		
		switch (mat)
		{
		case Material::material::TheVoid:
		{
			return VoidImage(r);
			break;
		}
		case Material::material::reflective:
		{
			C1 = Reflect(r, IntP, normal, maxRays, seed, index);
			break;
		}
		case Material::material::diffuse:
		{
			
			C1 = Diffuse(r, intersectingpoint, normal, mat, index, color, maxRays, seed);
			break;
		}
		case Material::material::light:
		{
			C1 = color;
			break;
		}
		case Material::material::GlossyReflection:
		{
			C1 = GlossyReflect(r, IntP, normal, maxRays, seed, index);
			break;
		}
		default:
		{
			C1 = Refract(r, IntP, normal, index, maxRays, seed);
			break;
		}
		}

		switch (m2)
		{
		case Material::material::TheVoid:
		{
			break;
		}
		case Material::material::reflective:
		{
			r->setDir(Dir);
			r->setOr(Origin);
			C2 = Reflect(r, IntP, normal, maxRays, seed, index);
			break;
		}
		case Material::material::diffuse:
		{
			r->setDir(Dir);
			r->setOr(Origin);
			C2 = Diffuse(r, intersectingpoint, normal, m2, index, color, maxRays, seed);
			break;
		}
		case Material::material::light:
		{
			r->setDir(Dir);
			r->setOr(Origin);
			C2 = color;
			break;
		}
		case Material::material::GlossyReflection:
		{
			r->setDir(Dir);
			r->setOr(Origin);
			C2 = GlossyReflect(r, IntP, normal, maxRays, seed, index);
			break;
		}
		default:
		{
			r->setDir(Dir);
			r->setOr(Origin);
			C2 = Refract(r, IntP, normal, index, maxRays, seed);
			break;
		}
		}

		return (C1 * percentage) + (C2 * (1.f - percentage));
}



void ObjectManager::AddShape(Shapes* x, bool BVH)
{
	if (BVH == true)
	{
		for (int i = 0; i < ARRAYSIZE; i++)
		{
			if (BVHshape[i] == nullptr)
			{
				BVHshape[i] = x;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < ARRAYSIZE; i++)
		{
			if (NonBVHShapes[i] == nullptr)
			{
				NonBVHShapes[i] = x;
				break;
			}
		}
	}
}

void ObjectManager::AddPointLight(LightSource* x)
{
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		if (light[i] == nullptr)
		{
			light[i] = x;
			return;
		}
	}
}
void ObjectManager::AddAreaLight(AreaLight* x, bool BVH)
{
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		if (light[i] == nullptr)
		{
			light[i] = x;
			break;
		}
	}

	if (BVH == true)
	{
		for (int i = 0; i < ARRAYSIZE; i++)
		{
			if (BVHshape[i] == nullptr)
			{
				BVHshape[i] = x;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < ARRAYSIZE; i++)
		{
			if (NonBVHShapes[i] == nullptr)
			{
				NonBVHShapes[i] = x;
				break;
			}
		}
	}
}


vec3 ObjectManager::lighthit(Ray* r,float &Inter,vec3& normal,int NMB,int& seed)
{
	vec3 Color;
	vec3 IntP = r->at(Inter);

	vec3 NOrigin = IntP + normal * 0.001f;
	r->setOr(NOrigin);
	bool hit = false;
	vec3 avgColor;
	float Dis;
	vec3 newDir;
	vec3 B;
	vec3 t;
	vec3 OBJInt = IntP;
	float angle;
	int ShapeIndex;
	//every lightsource
	for (int i = 0; i < ARRAYSIZE; i++)
	{
		//check the every light
		if (light[i] != nullptr)
		{	
			hit = false;

			vec3 P = light[i]->GetPoint(seed);
			//setting the direction to the light
			newDir = P - OBJInt;
			Dis = newDir.getlength();
			newDir.normalize();
			r->setDir(newDir);
			
			//calculating the distance from the lightsource to the 
			vec3 DisT = (P - NOrigin);
			float MaxT = DisT.x / newDir.x;

			angle = normal.dotproduct(newDir);
			//if the angle is lower than zero then there is a self intersection which means i dont have to shoot the ray
			if (angle > 0)
			{
				//setting intersection point to -1 means no intersections yet.
				Inter = -1;

				for (int j = 0; j < ARRAYSIZE; j++)
				{
					if (NonBVHShapes[j] != nullptr)
					{
							//check if the there is an intersection with the shape and if it is before or after it hit the lightsource
							if (NonBVHShapes[j]->hit(r, Inter, t, IntP, Color) == true && Inter < MaxT)
							{
								//if it intersects with an Area light it should ignore it
								if (NonBVHShapes[j]->material != Material::material::light)
								{
									//this is to check to see if an object is inside a refractive object if so then ignore
									if (NonBVHShapes[j]->material == Material::material::glass || NonBVHShapes[j]->material == Material::material::water)
									{
										vec3 Distance = NonBVHShapes[j]->Center - NOrigin;
										vec3 Rad = NonBVHShapes[j]->getRadius();
										for (int k = 0; k < 3; k++)
										{
											if (math::ABS(Distance.vec[k]) > math::ABS(Rad.vec[k]))
											{
												hit = true;
												break;
											}
										}
									}
									else
									{
									 hit = true;
									}
									
								}
								break;
							}
					}
					else break;
				}
			

				if (grid.BVH(r, ShapeIndex, Inter, t, IntP, Color,-100,NMB) == true)
				{
					if (BVHshape[ShapeIndex]->material != Material::material::light)
					{
						if (BVHshape[ShapeIndex]->material == Material::material::glass || BVHshape[ShapeIndex]->material == Material::material::water)
						{
							vec3 Distance = BVHshape[ShapeIndex]->Center - NOrigin;
							vec3 Rad = BVHshape[ShapeIndex]->getRadius();
							for (int k = 0; k < 3; k++)
							{
								if (math::ABS(Distance.vec[k]) > math::ABS(Rad.vec[k]))
								{
									hit = true;
									break;
								}
							}
						}
						else
							hit = true;
						

					}
				}
			}
			else hit = true;
			
			if (hit == false)
			{
				avgColor += light[i]->col * (light[i]->Brightnes * (1.f / (Dis)) * angle);	
			}
		}
		else break;
	}
		return avgColor;
}

	vec3 ObjectManager::RandomDir(int& seed)
	{
		while (true)
		{
			vec3 newDir = math::ranVecGen(seed,1,-1);
			if (newDir.lengthSqaured() < 1)
			{
				return newDir;
			}
		}
	}


	vec3 ObjectManager::Diffuse(Ray* r,float intersectingpoint,vec3 normal,Material::material mat,int index,vec3 color,int maxRays,int& seed)
	{
		
		vec3 NewOrigin = r->at(intersectingpoint) + normal * 0.001;
		
		vec3 directColor = (color * lighthit(r, intersectingpoint, normal, index,seed));
		vec3 indirectColor;
		vec3 NewDir;
		r->setDir(NewDir);
		//allow it to recurse only twice more so it won't take to long
		if (maxRays +2 >= RECURSIONCAP)
		{
				r->setOr(NewOrigin);
				NewDir = (NewOrigin + normal + RandomDir(seed)) - NewOrigin;
				NewDir.normalize();
				r->setDir(NewDir);
				
				indirectColor = RayColor(r, maxRays,seed);

		   	    indirectColor = math::Vecclamp(indirectColor, 0, 1);
		}
		else
		{
			r->setOr(NewOrigin);
			return directColor;
		}
		r->setOr(NewOrigin);
		return (directColor*0.875 + indirectColor * 0.125);
	}

	vec3 ObjectManager::Refract(Ray* r, vec3 IntP, vec3 normal, int index, int maxRays, int& seed)
	{
		float Ior;
		if (index < 0)
			Ior = static_cast<float>(NonBVHShapes[-index - 1]->material) * 0.1f;
		else
			Ior = static_cast<float>(BVHshape[index]->material) * 0.1f;

		
		if (maxRays <= 0)
		{
			return BLACK;
		}
		//if the last ray index is the same as the shape that means that it is already inside
		if (r->GetLast() != index)
		{
			vec3 OldDir = r->getDir();
			
			vec3 NOrigin = IntP + normal * -0.002f;
    		r->setOr(NOrigin);
			//do only the first refraction with a reflection because of speed
			//and because of the posablity to have a refraction inside another 
			//refractive object so the reflection will just keep bouncing inside the two objects 
			if (maxRays + 1 >= RECURSIONCAP)
			{
				float reflectionRate = math::reflectionRate(OldDir, normal, 1, Ior);
				vec3 Reflection = Reflect(r, IntP, normal, maxRays, seed, index);
				Reflection = math::Vecclamp(Reflection, 0, 1);
				r->AddIndex(index);
				vec3 dir;
				if (r->inside == false)
				{
					dir = math::refract(OldDir, normal, 1, Ior, false);
					r->inside = true;
				}
				else
				{
					dir = math::refract(OldDir, normal, Ior, 1, false);
					r->inside = false;
				}

				r->setOr(NOrigin);
				r->setDir(dir);
				vec3 refract = RayColor(r, maxRays, seed);

				//beers law
                vec3 Abs;
				vec3 Veclength = r->getOrigin() - NOrigin;
				float lenght = Veclength.getlength();
				if (index < 0)
				{
					Abs.x = expf(-NonBVHShapes[-index - 1]->Absorb.x * lenght);
					Abs.y = expf(-NonBVHShapes[-index - 1]->Absorb.y * lenght);
					Abs.z = expf(-NonBVHShapes[-index - 1]->Absorb.z * lenght);
				}
				else
				{
					Abs.x = expf(-BVHshape[index]->Absorb.x * lenght);
					Abs.y = expf(-BVHshape[index]->Absorb.y * lenght);
					Abs.z = expf(-BVHshape[index]->Absorb.z * lenght);
				}
				return (Reflection * reflectionRate) + (refract * (1 - reflectionRate))* Abs;
			}
			else
			{
				r->AddIndex(index);
				vec3 dir;
				if (r->inside == false)
				{
					dir = math::refract(OldDir, normal, 1, Ior, false);
					r->inside = true;
				}
				else
				{
					dir = math::refract(OldDir, normal, Ior, 1, false);
					r->inside = false;
				}

				r->setOr(NOrigin);
				r->setDir(dir);

				vec3 refract = (RayColor(r, maxRays, seed));
				//beers law
				vec3 Abs;
				vec3 Veclength = r->getOrigin() - NOrigin;
				float lenght = Veclength.getlength();
				if (lenght < 1)
				{
					lenght = 1;
				}
				if (index < 0)
				{
					Abs.x = expf(-NonBVHShapes[-index - 1]->Absorb.x * lenght);
					Abs.y = expf(-NonBVHShapes[-index - 1]->Absorb.y * lenght);
					Abs.z = expf(-NonBVHShapes[-index - 1]->Absorb.z * lenght);
				}
				else
				{
					Abs.x = expf(-BVHshape[index]->Absorb.x * lenght);
					Abs.y = expf(-BVHshape[index]->Absorb.y * lenght);
					Abs.z = expf(-BVHshape[index]->Absorb.z * lenght);
				}
				return refract * Abs;
			}
		}
		else
		{
			r->DeleteLastIndex();
			

			vec3 NOrigin = IntP + normal * 0.005f;
			r->setOr(NOrigin);

			vec3 dir = r->getDir();
			if (r->inside == true)
			{
				dir = math::refract(dir, normal, 1, Ior, false);
				r->inside = false;
			}
			else
			{
				dir = math::refract(dir, normal, Ior, 1, false);
				r->inside = true;
			}
			
			r->setDir(dir);

		

			vec3 refraction = RayColor(r, maxRays, seed);
			refraction = math::Vecclamp(refraction, 0, 2);
		
			return refraction;
		}
	}

	vec3 ObjectManager::Reflect(Ray* r, vec3 IntP,vec3 normal,int maxRays,int& seed,int index)
	{
		vec3 OldDir = r->getDir();

		vec3 NOrigin = IntP + normal * 0.03f;

		r->setOr(NOrigin);
	
		vec3 newDir = OldDir.reflect(OldDir, normal);
		vec3 absorb;
		if (index < 0)
			absorb = NonBVHShapes[-index-1]->Absorb;
		else
			absorb = BVHshape[index]->Absorb;

		
	    r->setDir(newDir);
		if (maxRays > 0)
		{
			//Absorbtion is what the shape absorbs so i have to inverse it to get the color that we actually see
    		return  (vec3(1,1,1) - absorb) * (RayColor(r, maxRays, seed));		
		}
		else
		{
			return BLACK;
		}
	}
	vec3 ObjectManager::GlossyReflect(Ray* r, vec3 IntP, vec3 normal, int maxRays, int& seed,int index)
	{
		if (maxRays > 0)
		{
			vec3 NOrigin = IntP + normal * 0.03f;
			r->setOr(NOrigin);

			vec3 OldDir = r->getDir();
            vec3 newDir = OldDir.reflect(OldDir, normal) + (((NOrigin + normal + RandomDir(seed)) - NOrigin)) * 0.4;
			newDir.normalize();
			r->setDir(newDir);

			vec3 absorb;
			if (index < 0)
				absorb = NonBVHShapes[-index - 1]->Absorb;
			else
				absorb = BVHshape[index]->Absorb;
			//Absorbtion is what the shape absorbs so i have to inverse it to get the color that we actually see
			return (vec3(1,1,1) - absorb) * (RayColor(r, maxRays, seed));
		}
		else
		{
			return BLACK;
		}
	}
