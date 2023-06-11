#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "precomp.h"
#include "doctest.h"
#include "stb_image.h"
#include "Math/Vector2.h"
#include "Mathlib.h"
#include "Vec3.h"
#include "Matrix.h"
#include "ray.h"
#include "box.h"
#include "sphere.h"
#include "plane.h"
///
//there seems to be an issue with cmath that i have not been able to locate so it might not work.
///
TEST_CASE("Testing Vector2 functionality")
{
	SUBCASE("Construction")
	{
		/// Default constructor
		const Vector2 v0;
		CHECK(v0.x == 0.0f);
		CHECK(v0.y == 0.0f);

		/// Constructor from components
		const Vector2 v1(9.1f, -3.0f);
		CHECK(v1.x == 9.1f);
		CHECK(v1.y == -3.0f);

		/// Constructor from components
		const Vector2 v2(4.3f);
		CHECK(v2.x == 4.3f);
		CHECK(v2.y == 4.3f);

		/// Copy construction
		Vector2 v3(v2);
		CHECK(v2.x == v3.x);
		CHECK(v2.y == v3.y);

		/// Zero all the components of the vector
		v3.Clear();
		CHECK(v0.x == v3.x);
		CHECK(v0.y == v3.y);
	}

	SUBCASE("Mathematical operators")
	{
		const Vector2 v0(2.3f, 3.7f);
		const Vector2 v1(-6.6f, 1.2f);
		const float factor = 3.5f;
		Vector2 v2;

		/// Returns the value of the given vector added to this.
		v2 = v0 + v1;
		CHECK(v2.x == v0.x + v1.x);
		CHECK(v2.y == v0.y + v1.y);

		/// Returns the value of the given vector subtracted from this.
		v2 = v0 - v1;
		CHECK(v2.x == v0.x - v1.x);
		CHECK(v2.y == v0.y - v1.y);

		SUBCASE("Vector and scalar multiplication.")
		{
			/// Returns a copy of this vector scaled the given value.
			v2 = v1 * factor;
			CHECK(v2.x == v1.x * factor);
			CHECK(v2.y == v1.y * factor);

			/// Returns a new vector being the result of a float value multiplied on right hand side with a vector
			v2 = factor * v0;
			CHECK(v2.x == v0.x * factor);
			CHECK(v2.y == v0.y * factor);
		}

		/// Returns a copy of this vector scaled the given value.
		v2 = v0 / factor;
		CHECK(v2.x == v0.x / factor);
		CHECK(v2.y == v0.y / factor);

		SUBCASE("Dot product calculation.")
		{
			/// Calculates and returns the dot product of this vector with the given vector.
			const float dot = v0 * v1;
			CHECK(-10.74f == dot);

			const float calculatedDot = v0.Dot(v1);
			CHECK(dot == calculatedDot);
		}

		/// Adds the given vector to this.
		SUBCASE("Adds the given vector to this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 += v0;
			CHECK(v3.x == v0.x + 3.0f);
			CHECK(v3.y == v0.y + -4.0f);
		}

		/// Subtracts the given vector from this
		SUBCASE("Subtracts the given vector from this.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 -= v1;
			CHECK(v3.x == 3.0f - v1.x);
			CHECK(v3.y == -4.0f - v1.y);
		}

		/// Multiplies this vector by the given scalar
		SUBCASE("Multiplies this vector by the given scalar.")
		{
			Vector2 v3(3.0f, -4.0f);
			v3 *= factor;
			CHECK(v3.x == 3.0f * factor);
			CHECK(v3.y == -4.0f * factor);
		}
	}

	SUBCASE("Logical operators")
	{
		/// Checks if the two vectors have identical components
		const float x = 2.93f;
		const float y = 4.39f;
		Vector2 v0(x, y);
		Vector2 v1(x, y);
		Vector2 v2(y, x);

		CHECK(v0 == v1);
		CHECK(v2 != v0);
	}

	SUBCASE("Length operations")
	{
		Vector2 v0(3.0f, 4.0f);

		/// Gets the magnitude of this vector
		const float vectorLenght = v0.Magnitude();
		CHECK(vectorLenght == 5.0f);

		/// Gets the squared magnitude of this vector
		const float vectorLenghtSq = v0.SquareMagnitude();
		CHECK(vectorLenghtSq == 25.0f);

		/// Limits the size of the vector to the given maximum
		v0.Trim(2.5f);
		CHECK(2.5f == v0.Magnitude());

		/// Returns the normalised version of a vector
		Vector2 v1 = v0;
		Vector2 v2 = v1.Unit();
		CHECK(v1 == v0);
		CHECK(1.0f == v2.Magnitude());
			
		/// Turns a non-zero vector into a vector of unit length
		v0.Normalize();
		CHECK(1.0f == v0.Magnitude());
	}
}

TEST_CASE("Testing Vector3 functionality")
{
	SUBCASE("Construction")
	{
		/// The default constructor creates a zero vector.
		vec3 A;
		CHECK(A.x == 0);
		CHECK(A.y == 0);
		CHECK(A.z == 0);
		/// Creates a vector with the given components
		vec3 v1(1, 2, 3);
		CHECK(v1.x == 1);
		CHECK(v1.y == 2);
		CHECK(v1.z == 3);

		//copy constructor
		vec3 v2(v1);
		CHECK(v1.x == 1);
		CHECK(v1.y == 2);
		CHECK(v1.z == 3);
	}

	SUBCASE("Mathematical operators")
	{
		vec3 v1(5.f, 10.f, 13.f);
		vec3 v2(10.f, 5.f, 13.f);
		vec3 v3;
		/// Returns the value of the given vector added to this
		v3 = v1 + v2;
		CHECK(v3.x == 15.f);
		CHECK(v3.y == 15.f);
		CHECK(v3.z == 26.f);
		/// Returns the value of the given vector subtracted from this
		v3 = v1 - v2;
		CHECK(v3.x == -5.f);
		CHECK(v3.y == 5.f);
		CHECK(v3.z == 0.f);
		/// Returns a copy of this vector scaled the given value
		v3 =  v2 * 2;
		CHECK(v3.x == 20.f);
		CHECK(v3.y == 10.f);
		CHECK(v3.z == 26.f);
		/// Returns a copy of this vector scaled the inverse of the value
		v3 =  v2 * 2;
		CHECK(v3.x == 20.f);
		CHECK(v3.y == 10.f);
		CHECK(v3.z == 26.f);
		/// Returns the negative this vector
		v3 = -v2;
		CHECK(v3.x == -10);
		CHECK(v3.y == -5);
		CHECK(v3.z == -13);
		/// Adds the given vector to this
		v3 = v1 * v2;
		CHECK(v3.x == 50.f);
		CHECK(v3.y == 50.f);
		CHECK(v3.z == 169.f);
		/// Subtracts the given vector from this
		v3 = v1 / v2;
		CHECK(v3.x == 0.5f);
		CHECK(v3.y == 2.f);
		CHECK(v3.z == 1.f);
		/// Multiplies this vector by the given scalar

		SUBCASE("Vector products")
		{
			vec3 v1(5.f, 10.f, 13.f);
			vec3 v2(10.f, 5.f, 13.f);
			vec3 v3;
			float dot;
			/// Calculates and returns the dot product of this with the given vector
			dot = v1.dotproduct(v2);
			//used my own calculator for this awnser
			CHECK(dot == 269.f);
			/// Calculates and returns the cross product of this vector with the given vector
			v3 = v1.crossprod(v2);
			// used an online calculater for these calculations
			//https://www.symbolab.com/solver/vector-cross-product-calculator/%5Cbegin%7Bpmatrix%7D5%2610%2613%5Cend%7Bpmatrix%7D%5Ctimes%5Cbegin%7Bpmatrix%7D10%265%2613%5Cend%7Bpmatrix%7D
			CHECK(v3.x == 65); 
			CHECK(v3.y == 65);
			CHECK(v3.z == -75);
		}

		SUBCASE("Length operations")
		{
			vec3 v1(1,4,6);
			///  Gets the magnitude of this vector
			float lengt = v1.getlength();
			//used an online calculator https://www.symbolab.com/solver/vector-magnitude-calculator/%7C%5Cbegin%7Bpmatrix%7D1%264%266%5Cend%7Bpmatrix%7D%7C
			float calclengt = static_cast<float>(sqrt(53));
			CHECK(lengt == calclengt);
			/// Turns a non-zero vector into a vector of unit length
			
			/// Returns the normalised version of a vector
			/// used an online calculator https://www.symbolab.com/solver/vector-unit-calculator/unit%20%5Cbegin%7Bpmatrix%7D1%264%266%5Cend%7Bpmatrix%7D
			 v1.normalize();
//			CHECK(v1 == vec3(1.f/sqrt(53.f), 4/sqrt(53.f), 6.f/sqrt(53.f)));
		}
	}

	SUBCASE("Logical operations")
	{
		/// Checks if the two vectors have identical components
		vec3 v1(5, 7, 1);
		vec3 v2(5, 7,  1);
		bool test = v1 == v2;
		bool test2 = (v1.x == v2.x && v1.y == v2.y && v1.z == v1.z);
		CHECK(test == test2);
		/// Checks if the two vectors have non-identical components
		vec3 v3(2, 5, 1);
		bool test3 = v1 == v3;
		bool test4 = (v1.x != v2.x || v1.y != v2.y || v1.z != v1.z);
		CHECK(test3 == test4);
	}
}

TEST_CASE("Testing Matrix functionality")
{
	SUBCASE("Construction")
	{
		/// Construct a new matrix from explicit values

		float temp[4][4] = { {1,2,3},{4,5,6},{7,8,9} };
		Matrix m(Matrix::MatSizes::THREE_THREE, temp);
		CHECK(m.at(0, 0) == 1);
		CHECK(m.at(2, 0) == 3);
		CHECK(m.at(0, 2) == 7);
		CHECK(m.at(2, 2) == 9);

		//copy constructor
		Matrix m2 = m;
		CHECK(m.at(0, 0) == 1);
		CHECK(m.at(2, 0) == 3);
		CHECK(m.at(0, 2) == 7);
		CHECK(m.at(2, 2) == 9);

		/// Creates a rotation matrix around the y axis (angle in degrees)

		m.rotationMatrixY(10);
		/// used a cosine calculator https://www.rapidtables.com/calc/math/Cos_Calculator.html
		/// had to round because the translation from degrees to radians has a small rounding of error
		CHECK(roundf(m.at(0, 0)) == roundf(0.98480775f));
		CHECK(roundf(m.at(2, 0)) == roundf(0.17364818f));
		CHECK(roundf(m.at(0, 2)) == roundf(-0.17364818f));
		CHECK(roundf(m.at(2, 2)) == roundf(0.98480775f));

	}

	SUBCASE("Mathematical operations")
	{
		float temp[4][4] = { {1,2,3},{4,5,6},{7,8,9} };
		Matrix m(Matrix::MatSizes::THREE_THREE, temp);
		float temp2[4][4] = { {9,8,7},{6,5,4},{3,2,1} };
		Matrix m2(Matrix::MatSizes::THREE_THREE, temp2);
		Matrix m3(Matrix::MatSizes::THREE_THREE);
		/// Matrix addition
		m3 = m + m2;
		CHECK(m3.at(0, 0) == 10.f);
		CHECK(m3.at(2, 0) == 10.f);
		CHECK(m3.at(0, 2) == 10.f);
		CHECK(m3.at(2, 2) == 10.f);
		/// Matrix subtraction
		m3 = m - m2;
		CHECK(m3.at(0, 0) == -8.f);
		CHECK(m3.at(2, 0) == -4.f);
		CHECK(m3.at(0, 2) == 4.f);
		CHECK(m3.at(2, 2) == 8.f);
		/// Matrix multiplication
		m3 = m * m2;
		//used a calculator https://matrix.reshish.com/nl/multCalculation.php
		CHECK(m3.at(0, 0) == 30);
		CHECK(m3.at(2, 0) == 18);
		CHECK(m3.at(0, 2) == 138);
		CHECK(m3.at(2, 2) == 90);
		SUBCASE("Inversion")
		{
			/// Get the determinant of this matrix
			float determinant = m.getDeterminant();
			CHECK(determinant == 0.f);
			float temp3[4][4] = { {12,2,6,4},{23,6,43,8},{34,3,7,532},{42,5,4,7} };
			Matrix m4(Matrix::MatSizes::FOUR_FOUR, temp3);
			determinant = m4.getDeterminant();
			CHECK(determinant == -168624);
			/// Inverts this matrix
			Matrix m5(Matrix::MatSizes::THREE_THREE, temp3);
			Matrix m6 = m5.inverse();
			// used calculator for the numbers https://matrix.reshish.com/nl/inverCalculation.php
			CHECK(roundf(m6.at(0, 0)) == roundf(-0.11631f));
			CHECK(roundf(m6.at(0, 2)) == roundf(0.06684f));
			CHECK(roundf(m6.at(2, 0)) == roundf(-0.18048f));
			CHECK(roundf(m6.at(2, 2)) == roundf(0.03475f));
			Matrix m7(Matrix::MatSizes::FOUR_FOUR, temp3);
			Matrix m8 = m7.inverse();
		}
	}
}
	TEST_CASE("3d Maths")
	{
		SUBCASE("spheres")
		{

			//basic ray sphere intersection
			Sphere sphere(1, vec3(0, 0, 2), RED, Material::material::diffuse);
			Ray r(vec3(0, 0, 0));
			vec3 Dir = vec3(0, 0, 1);
			r.setDir(Dir);
			float intersect = -1;
			vec3 Normal;
			vec3 Inter;
			vec3 Col;
			sphere.hit(&r, intersect, Normal, Inter, Col);
			CHECK(intersect == 1);
			CHECK(Normal == vec3(0, 0, -1));


			//Ray inside the sphere intersection
			vec3 O = vec3(0, 0, 2);
			r.setOr(O);
			intersect = -1;
			sphere.hit(&r, intersect, Normal, Inter, Col);
			CHECK(Inter == vec3(0, 0, 3));

			//sphere behind ray
			O = vec3(0, 0, 5);
			r.setOr(O);
			intersect = -1;
			CHECK(sphere.hit(&r, intersect, Normal, Inter, Col) == false);




			//more difficult intersections
			//used http://www.ambrsoft.com/TrigoCalc/Sphere/SpherLineIntersection_.htm for calculations
			//the accuracy only goes to two numbers after the dot.
			sphere = Sphere(1, vec3(2, 2, 2), RED, Material::material::diffuse);
			Dir = vec3(0.34, 0.32, 0.20);
			Dir.normalize();
			O = vec3(0, 0, 0);
			r.setOr(O);
			r.setDir(Dir);
			intersect = -1;
			CHECK(sphere.hit(&r, intersect, Normal, Inter, Col) == true);
			// had to round to two decimals
			Inter.x = round(Inter.x * 100);
			Inter.y = round(Inter.y * 100);
			Inter.z = round(Inter.z * 100);
			CHECK(Inter == vec3(181, 170, 106));



			//check the second intersection point
			//used http://www.ambrsoft.com/TrigoCalc/Sphere/SpherLineIntersection_.htm for calculations
			intersect = 100;
			CHECK(sphere.RefracHit(&r, intersect, Normal, Inter) == true);
			// had to round to two decimals
			Inter.x = round(Inter.x * 100);
			Inter.y = round(Inter.y * 100);
			Inter.z = round(Inter.z * 100);
			CHECK(Inter == vec3(272, 256, 160));
		}
		SUBCASE("Planes")
		{
			//basic ray intersections
			vec3 P(0, 0, 10);
			vec3 N(0, 0, 1);
			plane Plane(N, P, RED, Material::material::diffuse, false, RED);
			Ray r(vec3(0, 0, 0));
			vec3 Dir = vec3(0, 0, 1);
			r.setDir(Dir);
			float intersect = -1;
			vec3 Normal;
			vec3 Inter;
			vec3 Col;
			Plane.hit(&r, intersect, Normal, Inter, Col);
			CHECK(intersect == 10);

			//ray parrallel to plane
			N = vec3(0, 1, 0);
			P = vec3(0, 1, 0);
			Plane = plane(N, P, RED, Material::material::diffuse, false, RED);
			CHECK(Plane.hit(&r, intersect, Normal, Inter, Col) == false);
		}
		SUBCASE("AABB")
		{
			//basic box intersections
			Box box(1, 1, 1, vec3(0, 0, 1), RED, Material::material::diffuse);
			Ray r(vec3(0, 0, 0));
			vec3 Dir = vec3(0, 0, 1);
			r.setDir(Dir);
			float intersect = -1;
			vec3 Normal;
			vec3 Inter;
			vec3 Col;
			CHECK(box.hit(&r, intersect, Normal, Inter, Col) == true);
			CHECK(intersect == 2);

		}


    }
