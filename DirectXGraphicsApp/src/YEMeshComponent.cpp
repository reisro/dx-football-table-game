#include "YEMeshComponent.h"
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
	YELog("\nStarting Mesh Component...");
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

	SendToSceneObject();
}

void YEMeshComponent::SendToSceneObject()
{
	YERenderer* renderer = YERenderer::GetInstance();

	std::vector<YEMesh> loadedMeshes = ModelMesh->getLoadedMeshes();

	auto obj = GetGameObjectOwner();

	// Check if there are multiple meshes loaded
	if (loadedMeshes.size() > 1)
	{	
		obj->hasMultipleMeshes = true;
		obj->_numberMeshes = loadedMeshes.size();
	}

	if (!loadedMeshes.empty())
	{
		std::vector<YEMesh>::iterator it = loadedMeshes.begin();

		while (it != loadedMeshes.end())
		{
			it->_idMWorld = obj->_id;
			renderer->GetSceneObject()->_meshesToRender.push_back(*it);
			++it;
		}
	}

	delete ModelMesh;
	ModelMesh = nullptr;
}

void YEMeshComponent::SetFilenamePath(const wchar_t* pFileName)
{
	_meshFilename = pFileName;
}

const wchar_t* YEMeshComponent::GetFilenamePath()
{
	return _meshFilename;
}

YEGameObject* YEMeshComponent::GetGameObjectOwner()
{
	return _gameObject;
}
