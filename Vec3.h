#ifndef VEC3_H
#define VEC3_H

#define _USE_MATH_DEFINES
#include "math.h"

class Vec3
{
public:
	Vec3(): X( 0 ), Y( 0 ), Z( 0 ) {};
	Vec3( float a_Value ): X( a_Value ), Y( a_Value ), Z( a_Value ) {};
	Vec3( float a_X, float a_Y, float a_Z ): X( a_X ), Y( a_Y ), Z( a_Z ) {};

	inline	float	GetLength()			{ return	( X*X + Y*Y + Z*Z); }
	inline	float	GetNormalLength()	{ return	( sqrtf( X*X + Y*Y + Z*Z) ); }
	inline	void	Normalize()			{ float		Length = GetNormalLength(); X /= Length; Y /= Length; Z /= Length; }

	Vec3	GetNormalize()
	{
		float Length = GetNormalLength(); 
		return Vec3(X / Length, Y / Length, Z / Length); 
	}

	inline	float	Dot(Vec3* vecB)		{ return	(X * vecB->X) + (Y * vecB->Y) + (Z * vecB->Z); }

	float	Angle(Vec3* vecB)
	{
		Vec3 vecANorm = GetNormalize();
		Vec3 vecBNorm = vecB->GetNormalize();
		return	 acos((vecANorm.X * vecBNorm.X) + (vecANorm.Y * vecBNorm.Y) + (vecANorm.Z * vecBNorm.Z));
	}

	/*float	Angle(Vec3* vecB)
	{
		float lVecA = GetLength();
		float lVecB = vecB->GetLength();
		return	 acos(((X * vecB->X) + (Y * vecB->Y) + (Z * vecB->Z))/(lVecA*lVecB));
	}*/

	Vec3	GetCross(Vec3* vecB)
	{
		Vec3 vecANorm = GetNormalize();
		Vec3 vecBNorm = vecB->GetNormalize();

		return	  Vec3((Y * vecB->Z - vecB->Y * Z), 
			(Z * vecB->X - vecB->Z * X),
			(X * vecB->Y - vecB->X * Y));

		/*return	  Vec3((vecANorm.Y * vecBNorm.Z - vecBNorm.Y * vecANorm.Z), 
			(vecANorm.Z * vecBNorm.X - vecBNorm.Z * vecANorm.X),
			(vecANorm.X * vecBNorm.Y - vecBNorm.X * vecANorm.Y));*/
	}

	inline Vec3 Substract(Vec3* vec)	{ return	Vec3(X - vec->X, Y - vec->Y, Z - vec->Z); }

	float X, Y, Z;

}; // Vec3 Class

#endif