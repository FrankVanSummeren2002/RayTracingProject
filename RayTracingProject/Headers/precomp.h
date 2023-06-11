#pragma once

#define SCRWIDTH 512.f
#define SCRHEIGHT 512.f

#define PI 3.14159265359
struct Material
{
	enum class material  {TheVoid, reflective, diffuse, water = 13,glass = 15,light,GlossyReflection};
};
#define RECURSIONCAP  10
#define HALFSHADOW vec3(0.5f,0.5f,0.5f)
#define RED vec3(1,0.1f,0.1f)
#define BLUE vec3(0.1f,0.1f,1.f)
#define GREEN vec3(0.1f,1,0.1f)
#define WHITE vec3(1.f,1.f,1.f)
#define BLACK vec3(0.01f,0.01f,0.01f)
#define ARRAYSIZE 100
#include "SFML/Graphics.hpp"
#include "Mathlib.h"
#include "vec3.h"
#include "Matrix.h"

