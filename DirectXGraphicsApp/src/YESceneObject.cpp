#include "YESceneObject.h"

YESceneObject::YESceneObject()
{
}

YESceneObject::~YESceneObject()
{
}

void YESceneObject::Draw(IUnknown* context, int id)
{
	_meshesToRender[id].Draw(context);
}

void YESceneObject::Update(UINT id, DirectX::CXMMATRIX M)
{
	XMFLOAT4X4 world;

	if (id != _internalid)
	{
		_internalid++;

		XMStoreFloat4x4(&_meshesToRender[_internalid]._mWorld, M);
	}
	else
		XMStoreFloat4x4(&_meshesToRender[id]._mWorld, M);
}
