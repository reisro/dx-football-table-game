#include "YEMeshComponent.h"
#include "YERenderer.h"

YEMeshComponent::YEMeshComponent()
{
}

YEMeshComponent::YEMeshComponent(const wchar_t* pFileName)
{
	//LoadModel(pFileName);
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

	return ModelMesh->Load(reinterpret_cast<ID3D11Device*>(renderer->GetDevice()), renderer->GetDeviceContext(), pFileName);
}