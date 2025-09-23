#include "YEVector3.h"

YEVector3::YEVector3() :_x(yeFloat(.0f)), _y(yeFloat(.0f)), _z(yeFloat(.0f)),
_u(XMLoadFloat3(new XMFLOAT3(_x, _y, _z)))
{
}

YEVector3::YEVector3(yeFloat x, yeFloat y, yeFloat z):
	_x(x), _y(y), _z(z)
{
}

YEVector3::YEVector3(FXMVECTOR vector):
	_u(vector), _x(yeFloat(XMVectorGetX(vector))), _y(yeFloat(XMVectorGetY(vector))), _z(yeFloat(XMVectorGetZ(vector)))
{
}

YEVector3::YEVector3(const YEVector3& _vector):
	_x(_vector._x), _y(_vector._y), _z(_vector._z),
	_u(XMLoadFloat3(new XMFLOAT3(_x, _y, _z)))
{
}

YEVector3::~YEVector3()
{
}

void YEVector3::SetValue(YEVector3* _vector)
{
	_x = _vector->_x;
	_y = _vector->_y;
	_z = _vector->_z;
	_u = XMLoadFloat3(new XMFLOAT3(_vector->_x, _vector->_y, _vector->_z));
}

YEVector3& YEVector3::operator=(const YEVector3& vector) const
{
	return *new YEVector3(vector);
}

XMVECTOR YEVector3::toXMVector()
{
	return _u;
}

XMVECTOR YEVector3::Magnitude(const YEVector3& vec)
{
	return XMVectorSqrt(vec._u);
}

inline YEVector3* YEVector3::Normalize(YEVector3& out, YEVector3& vec)
{
	return nullptr;
}

inline yeFloat YEVector3::Dot(const YEVector3& vec, const YEVector3& vec2)
{
	return yeFloat();
}

inline YEVector3* YEVector3::Cross(const YEVector3& vec, const YEVector3& vec2, const YEVector3& vec3)
{
	return nullptr;
}
