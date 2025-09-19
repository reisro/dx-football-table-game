#include "YEGameObject.h"
#include "YEBaseComponent.h"
#include "YETransformComponent.h"

YEGameObject::YEGameObject():
	_game_object_name{ "Game Object" },
	_id{ 0 }
{
	// Every game object has a transform component by default
	addComponent(new YETransformComponent());
}

YEGameObject::YEGameObject(const char* _game_name):
	_game_object_name{ _game_name }, _id{ 0 }
{
	// Every game object has a transform component by default
	addComponent(new YETransformComponent());
}

YEGameObject::~YEGameObject()
{
	_components.clear();
}

void YEGameObject::start()
{
	DXLog("\nStart Game Object...");

	if (!_components.empty())
	{
		for (auto cp : _components)
		{
			cp->start();
		}
	}
}

void YEGameObject::shutdown()
{
	if (!_components.empty())
	{
		for (auto cp : _components)
		{
			cp->shutdown();
		}
	}
}	

void YEGameObject::update(float _deltaTime)
{
	DXLog("\nUpdating Game Object...");

	if (!_components.empty())
	{
		for (auto cp : _components)
		{
			cp->update(_deltaTime);
		}
	}
}

void YEGameObject::addComponent(YEBaseComponent* component)
{
	_components.push_back(component);
}

void YEGameObject::setName(const char* _name)
{
	_game_object_name = _name;
}