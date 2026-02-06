#pragma once
#pragma warning(disable : 4838) 

#ifndef _YE_GAME_OBJECT_H_
#define _YE_GAME_OBJECT_H_

#include "DXAPI.h"
#include "YEVectorWrapper.h"
#include "YETransformComponent.h"

struct YEGameContext;
class YEBaseComponent;

class DX_API YEGameObject
{
public:

	YEGameObject();
	YEGameObject(const char* object_name, const YEGameContext& _game_context, bool isEmpty=false);
	YEGameObject(const char* _game_name);

	virtual ~YEGameObject();

	virtual void start();

	virtual void shutdown();

	virtual void update(float _deltaTime);

	virtual void addComponent(YEBaseComponent* component);

	virtual void setName(const char* _name);

	void SetPosition(YEVector3* pos);

	YEGameContext GetGameContext();

	YEVector3* GetPosition() const;

	int GetNumberOfMeshes() const { return _numberMeshes; }

	int GetNumberOfChildren() const { return _numberChildren; }

	YETransformComponent* _transform;

	YEGameObject* _parent;

	UINT _id;
	UINT _physicsid;

	int _numberMeshes;
	int _numberChildren;

	bool hasChildren;
	bool hasParent;
	bool hasMultipleMeshes;
	bool hasRigidBody;

protected:
	const char* _game_object_name;

	YEVectorWrapper<YEBaseComponent*> _components;
	YEVectorWrapper<YEGameObject*>	  _children;
	
private:
	YEVector3* position;
};

#endif _YE_GAME_OBJECT_H_