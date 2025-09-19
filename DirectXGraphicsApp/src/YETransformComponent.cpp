#include "YETransformComponent.h"

YETransformComponent::YETransformComponent():
	position{ 0.0f, 0.0f, 0.0f },
	rotation{ 0.0f, 0.0f, 0.0f },
	scale{ 1.0f, 1.0f, 1.0f }
{
	DXLog("\nCreated Transform Component...");
}

YETransformComponent::~YETransformComponent()
{
}

void YETransformComponent::start()
{
	DXLog("\nStarted Transform Component...");
}

void YETransformComponent::shutdown()
{
	DXLog("\nShutdown Transform Component...");
}

void YETransformComponent::update(float _deltaTime)
{
	DXLog("\nUpdating Transform Component...");
}

void YETransformComponent::setPosition(yeFloat x, yeFloat y, yeFloat z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void YETransformComponent::setRotation(yeFloat x, yeFloat y, yeFloat z)
{
	rotation[0] = x;
	rotation[1] = y;
	rotation[2] = z;
}

void YETransformComponent::setScale(yeFloat x, yeFloat y, yeFloat z)
{
	scale[0] = x;
	scale[1] = y;
	scale[2] = z;
}

yeFloat* YETransformComponent::getPosition()
{
	return position;
}

yeFloat* YETransformComponent::getRotation()
{
	return rotation;
}

yeFloat* YETransformComponent::getScale()
{
	return scale;
}