#include "YEPhysicsComponent.h"
#include "YEPhysics.h"

YEPhysicsComponent::YEPhysicsComponent():
	YEBaseComponent()
{

}

YEPhysicsComponent::YEPhysicsComponent(YEGameObject* owner):
	YEBaseComponent(owner)
{
}

YEPhysicsComponent::~YEPhysicsComponent()
{

}

void YEPhysicsComponent::start()
{
}

void YEPhysicsComponent::shutdown()
{
}

void YEPhysicsComponent::update(float _deltaTime)
{
}

YEPhysics* YEPhysicsComponent::GetPhysicsEngine()
{
	return YEPhysics::GetInstance();
}

void YEPhysicsComponent::Attach(IYETransformComponentListener* observer)
{
}

void YEPhysicsComponent::Detach(IYETransformComponentListener* observer)
{
}

void YEPhysicsComponent::Notify()
{

}
