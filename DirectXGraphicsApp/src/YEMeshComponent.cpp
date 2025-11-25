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

	if (loadedMeshes.size() > 1)
	{
		GetGameObjectOwner()->_numberChildren = static_cast<int>(loadedMeshes.size());
		GetGameObjectOwner()->hasChildren = true;
	}

	if (!loadedMeshes.empty())
	{
		std::vector<YEMesh>::iterator it = loadedMeshes.begin();

		while (it != loadedMeshes.end())
		{
			renderer->GetSceneObject()->_meshesToRender.push_back(*it);
			++it;
		}
	}

	delete ModelMesh;
	ModelMesh = nullptr;
}

const wchar_t* YEMeshComponent::GetFilenamePath()
{
	return _meshFilename;
}

YEGameObject* YEMeshComponent::GetGameObjectOwner()
{
	return _gameObject;
}
