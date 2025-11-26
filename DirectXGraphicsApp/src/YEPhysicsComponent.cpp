#include "YEPhysicsComponent.h"
#include "YETransformComponent.h"
#include "YEGameObject.h"
#include "YEPhysics.h"

YEPhysics* YEPhysicsComponent::_physics_engine = nullptr;

YEPhysicsComponent::YEPhysicsComponent():
	YEBaseComponent()
{
}

YEPhysicsComponent::YEPhysicsComponent(YEGameObject* owner):
	YEBaseComponent(owner)
{
	SetGameObject(owner);
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

void YEPhysicsComponent::GetPhysicsEngine()
{
	_physics_engine = YEPhysics::GetInstance();
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
