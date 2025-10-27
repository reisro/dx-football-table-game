#include "YETransformComponent.h"

YETransformComponent::YETransformComponent():
	x{ 0.0f }, y{ 0.0f }, z {0.0f },
	roll{ 0.0f }, yaw{ 0.0f }, pitch { 0.0f },
	sx{ 1.0f }, sy{ 1.0f }, sz{ 1.0f }
{
	DXLog("\nCreated Transform Component...");
}

YETransformComponent::~YETransformComponent()
{
}

void YETransformComponent::start()
{
	//DXLog("\nStarted Transform Component...");
}

void YETransformComponent::shutdown()
{
	DXLog("\nShutdown Transform Component...");
}

void YETransformComponent::update(float _deltaTime)
{
	//DXLog("\nUpdating Transform Component...");
}

void YETransformComponent::setPosition(yeFloat _x, yeFloat _y, yeFloat _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void YETransformComponent::setPosition(YEVector3* position)
{
	_position.SetValue(position);

	x = position->_x;
	y = position->_y;
	z = position->_z;
}

void YETransformComponent::setRotation(yeFloat x, yeFloat y, yeFloat z)
{
	roll = x;
	yaw = y;
	pitch = z;
}

void YETransformComponent::setScale(yeFloat x, yeFloat y, yeFloat z)
{
	sx = x;
	sy = y;
	sz = z;
}

yeFloat* YETransformComponent::getPosition()
{
	return &z;
}

yeFloat* YETransformComponent::getRotation()
{
	return &roll;
}

yeFloat* YETransformComponent::getScale()
{
	return &sx;
}

void YETransformComponent::setWorldViewProj(CXMMATRIX M)
{
	WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M));
}

void YETransformComponent::SetWorld(CXMMATRIX M)
{
	World->SetMatrix(reinterpret_cast<const float*>(&M));
}

void YETransformComponent::SetWorldInverseTranspose(CXMMATRIX M)
{
	WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M));
}

void YETransformComponent::SetEyePosW(const XMVECTOR& v)
{
	EyePosW->SetFloatVector(reinterpret_cast<const float*>(&v));
}