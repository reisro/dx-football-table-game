#include "YEGameObject.h"
#include "YEGameObject.h"
#include "YEBaseComponent.h"
#include "YETransformComponent.h"
#include "YEGameContext.h"

YEGameObject::YEGameObject():
	_game_object_name{ "Game Object" },
	_id{ 0 }
{
	// Every game object has a transform component by default
	_transform = new YETransformComponent();
	_transform->_gameObject = this;
}

YEGameObject::YEGameObject(const YEGameContext& _game_context):
_game_object_name{ "Game Object" },
_id{ _game_context.sceneObject->_meshid++ }
{
	// Every game object has a transform component by default
	_transform = new YETransformComponent();
	_transform->Attach(_game_context.sceneObject);
	_transform->_gameObject = this;
}

YEGameObject::YEGameObject(const char* _game_name):
	_game_object_name{ _game_name }, _id{ 0 }
{
	// Every game object has a transform component by default
	addComponent(new YETransformComponent());
}

YEGameObject::~YEGameObject()
{
	_components.getVector()->_list.clear();
}

void YEGameObject::start()
{
	//DXLog("\nStart Game Object...");

	if (!_components.getVector()->_list.empty())
	{
		for (auto cp : _components.getVector()->_list)
		{
			cp->start();
		}
	}
}

void YEGameObject::shutdown()
{
	if (!_components.getVector()->_list.empty())
	{
		for (auto cp : _components.getVector()->_list)
		{
			cp->shutdown();
		}
	}
}	

void YEGameObject::update(float _deltaTime)
{
	YELog("\nUpdating Game Object...");

	if (!_components.getVector()->_list.empty())
	{
		for (auto cp : _components.getVector()->_list)
		{
			cp->update(_deltaTime);
		}
	}
}

void YEGameObject::addComponent(YEBaseComponent* component)
{
	component->_gameObject = this;

	_components.getVector()->push_back(component);
}

void YEGameObject::setName(const char* _name)
{
	_game_object_name = _name;
}

void YEGameObject::SetPosition(YEVector3* pos)
{
	_transform->setPosition(pos);
}

YEVector3* YEGameObject::GetPosition() const
{
	return _transform->getPosition();
}
