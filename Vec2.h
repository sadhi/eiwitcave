#ifndef VEC2_H
#define VEC2_H

#include "math.h"

class Vec2
{
public:
	Vec2(): X( 0 ), Y( 0 ) {};
	Vec2( float a_Value ): X( a_Value ), Y( a_Value ) {};
	Vec2( float a_X, float a_Y ): X( a_X ), Y( a_Y ) {};

	inline	float	GetLength()			{ return	( X*X + Y*Y ); }
	inline	float	GetNormalLength()	{ return	( sqrtf( X*X + Y*Y ) ); }
	inline	void	Normalize()			{ float		Length = GetNormalLength(); X /= Length; Y /= Length; }

	float X, Y;
}; // Vec2 Class

#endif