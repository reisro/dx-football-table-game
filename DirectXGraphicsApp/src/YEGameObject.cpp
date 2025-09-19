#include "YEGameObject.h"

YEGameObject::YEGameObject():
	_game_object_name{ "Game Object" },
	_id{ 0 }
{
}

YEGameObject::YEGameObject(const char* _game_name):
	_game_object_name{ _game_name }, _id{ 0 }
{
}

YEGameObject::~YEGameObject()
{
}

void YEGameObject::start()
{
	DXLog("\nStart Game Object...");
}

void YEGameObject::shutdown()
{
	return;
}	

void YEGameObject::update(float _deltaTime)
{
	DXLog("\nUpdating Game Object...");
}

void YEGameObject::addComponent()
{
	return;
}

void YEGameObject::setName(const char* _name)
{
	_game_object_name = _name;
}