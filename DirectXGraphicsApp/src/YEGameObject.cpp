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
	_components.getVector()->_list.clear();
}

void YEGameObject::start()
{
	DXLog("\nStart Game Object...");

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
	DXLog("\nUpdating Game Object...");

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
	_components.getVector()->push_back(component);
}

void YEGameObject::setName(const char* _name)
{
	_game_object_name = _name;
}

YETransformComponent* YEGameObject::GetTransform()
{
    // GetElements() が一時オブジェクトを返す場合、参照を保持しないようにする
    auto elements = _components.getVector()->GetElements();

    if (elements.empty()) 
		return nullptr;

    return dynamic_cast<YETransformComponent*>(elements.front());
}