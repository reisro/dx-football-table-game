#include "YESceneObject.h"

YESceneObject::YESceneObject()
{
	_meshesToRender = std::vector<YEMesh>();
}

YESceneObject::~YESceneObject()
{
}

void YESceneObject::CreateObjectWorldList(UINT id, DirectX::CXMMATRIX M)
{
    XMStoreFloat4x4(&_meshesWorld[id], M);

	_meshesWorld.insert(std::make_pair(id, _meshesWorld[id])); // 0 1 2 3 4 field ball handler player player2
}

XMFLOAT4X4 YESceneObject::LoadWorldPosition(UINT id)
{
	return _meshesWorld[id];
}

void YESceneObject::Draw(IUnknown* context, int id)
{
	_meshesToRender[id].Draw(context);
}

void YESceneObject::Update(UINT id, DirectX::CXMMATRIX M)
{
	XMFLOAT4X4 world;

	XMStoreFloat4x4(&_meshesWorld[id], M); // 0 1 2 3 4  render world 0 1 2 3 4 check 1 

	//std::cout << "YESceneObject::Update called for ID: " << id << std::endl;
}
