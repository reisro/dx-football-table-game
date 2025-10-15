#include "YEMeshComponent.h"	
#include "YERenderer.h"

YEMeshComponent::YEMeshComponent()
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

bool YEMeshComponent::LoadModel(std::string path)
{
	YERenderer* renderer = YERenderer::GetInstance();

	return ModelMesh->Load(reinterpret_cast<ID3D11Device*>(renderer->GetDevice()), renderer->GetDeviceContext(), path);
}