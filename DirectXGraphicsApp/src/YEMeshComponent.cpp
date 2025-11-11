#include "YEMeshComponent.h"
#include "YERenderer.h"
#include "YEMesh.h"
#include "YEGameObject.h"

YEMeshComponent::YEMeshComponent()
{
}

YEMeshComponent::YEMeshComponent(YEGameObject* owner, const wchar_t* pFileName): 
	YEBaseComponent(owner), _meshFilename(pFileName), ModelMesh(new YEMeshLoader())
{
}

YEMeshComponent::~YEMeshComponent()
{
}

void YEMeshComponent::start()
{
	DXLog("\nStarting Mesh Component...");
}

void YEMeshComponent::shutdown()
{
}

void YEMeshComponent::update(float _deltaTime)
{
}

void YEMeshComponent::LoadModel(const wchar_t* pFileName)
{
	YERenderer* renderer = YERenderer::GetInstance();

	ModelMesh->Load(renderer->GetDevice(), renderer->GetDeviceContext(), pFileName);

	renderer->GetSceneObject()->_meshesToRender = ModelMesh->getLoadedMeshes();

	renderer->GetSceneObject()->_meshesToRender[0]._mWorld = _gameObject->_transform->getWorldMatrix();
}

const wchar_t* YEMeshComponent::GetFilenamePath()
{
	return _meshFilename;
}
