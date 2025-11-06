#include "YEMeshComponent.h"
#include "YERenderer.h"

YEMeshComponent::YEMeshComponent()
{
}

YEMeshComponent::YEMeshComponent(const wchar_t* pFileName): YEBaseComponent(),
ModelMesh(new YEMeshLoader())	
{
	LoadModel(pFileName);
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

bool YEMeshComponent::LoadModel(const wchar_t* pFileName)
{
	YERenderer* renderer = YERenderer::GetInstance();

	renderer->LoadMesh(pFileName);

	return true;
}