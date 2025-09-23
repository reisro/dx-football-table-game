#pragma once

#ifndef _YE_VECTOR3H_
#define _YE_VECTOR3H_

#include "DXAPI.h"
#include "DXTypes.h"
#include <xnamath.h>
#include <iostream>
#include <d3d11.h>
#include <d3dx11.h>

class DX_API YEVector3
{
public:

	// constructors
	YEVector3();
	YEVector3(yeFloat x, yeFloat y, yeFloat z);
	YEVector3(FXMVECTOR vector);
	YEVector3(const YEVector3& _vector);
	~YEVector3();

	XMVECTOR getVector() const { return _u; }

	// Setters
	void SetValue(YEVector3* _vector);

	// Operator overloading
	YEVector3& operator=(const YEVector3& vector) const;

	// Conversion to D3DVECTOR3
	XMVECTOR toXMVector();

	// zero vector and basis vector values
	static YEVector3* Zero() { return new YEVector3( XMVectorSet(.0f, .0f, 0.0f, .0f)); }
	static inline YEVector3 Right() { return *new YEVector3(XMVectorSet(1.0f, .0f, 0.0f, .0f)); };
	static inline YEVector3 Forward() { return *new YEVector3(XMVectorSet(.0f, .0f, 1.0f, .0f)); };

	// returns the length of the vector
	static XMVECTOR Magnitude(const YEVector3& vec);

	// returns the normalized vector
	static inline YEVector3* Normalize(YEVector3& out, YEVector3& vec);

	static inline YEVector3* Sum(const YEVector3& vec, const YEVector3& vec2)
	{
		return new YEVector3(vec._x + vec2._x, vec._y + vec2._y, vec._z + vec2._z);
	};

	static inline yeFloat Dot(const YEVector3& vec, const YEVector3& vec2);

	static inline YEVector3* Cross(const YEVector3& vec, const YEVector3& vec2, const YEVector3& vec3);

	// converts to a Matrix
	//rfMatrix& ToMatrix(const rfVector3& _vector) const;

	yeFloat _x, _y, _z;

private:
	XMVECTOR _u;
};

#endif _RFVECTOR3H_