#include "YESpriteShader.h"
#include "YERenderer.h"

#include <Windows.h>
#include "../shaders/CompiledSpritePixelShader.hlsl.h"
#include "../shaders/CompiledSpriteVertexShader.hlsl.h"
#include "../shaders/CompiledSpriteGeometryShader.hlsl.h"

YESpriteShader::YESpriteShader(YERenderer* renderer):
	m_Renderer(renderer)
{
}

void YESpriteShader::Load()
{
	this->LoadVertexShader();
	this->LoadPixelShader();
	this->LoadGeometryShader();
	this->CreateWorldConstantBuffer();
	this->CreateAnimationConstantBuffer();
}

void YESpriteShader::Use()
{
	ID3D11DeviceContext* context = (ID3D11DeviceContext*) m_Renderer->GetDeviceContext();

	// Bind the input layout to the pipeline's Input Assembler stage
	context->IASetInputLayout(m_VertexLayout.Get());

	// Bind the vertex shader to the pipeline's Vertex Shader stage
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);

	// Bind the geometry shader to the pipeline's Geometry Shader stage
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);

	// Bind the pixel shader to the pipeline's Pixel Shader stage
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);

	// Bind the world constant buffer to the vertex shader
	const int constant_buffer_slot = 0;
	context->VSSetConstantBuffers(constant_buffer_slot, 1, m_WorldConstantBuffer.GetAddressOf());

	// Bind the world constant buffer to the geometry shader
	context->GSSetConstantBuffers(0, 1, m_WorldConstantBuffer.GetAddressOf());

	// Bind the animation constant buffer to pixel shader
	const int animation_buffer_slot = 1;
	context->PSSetConstantBuffers(animation_buffer_slot, 1, m_AnimationConstantBuffer.GetAddressOf());
}

void YESpriteShader::UpdateAnimationConstantBuffer(const AnimationBuffer& buffer)
{
}

void YESpriteShader::LoadVertexShader()
{
	ID3D11Device* device = (ID3D11Device*) m_Renderer->GetDevice();

	// Create the vertex shader
	HRESULT hr = device->CreateVertexShader(g_SpriteVertexShader, sizeof(g_SpriteVertexShader), nullptr, m_VertexShader.ReleaseAndGetAddressOf());

	// Describe the memory layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "SIZE", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT number_elements = ARRAYSIZE(layout);

	hr = device->CreateInputLayout(layout, number_elements, g_SpriteVertexShader, sizeof(g_SpriteVertexShader), m_VertexLayout.ReleaseAndGetAddressOf());
}

void YESpriteShader::LoadPixelShader()
{
	ID3D11Device* device = (ID3D11Device*) m_Renderer->GetDevice();

	device->CreatePixelShader(g_SpritePixelShader, sizeof(g_SpritePixelShader), nullptr, m_PixelShader.ReleaseAndGetAddressOf());
}

void YESpriteShader::LoadGeometryShader()
{
	ID3D11Device* device = (ID3D11Device*) m_Renderer->GetDevice();
	HRESULT hr = device->CreateGeometryShader(g_SpriteGeometryShader, sizeof(g_SpriteGeometryShader), nullptr, m_GeometryShader.ReleaseAndGetAddressOf());
}

void YESpriteShader::CreateWorldConstantBuffer()
{
	ID3D11Device* device = (ID3D11Device*) m_Renderer->GetDevice();

	// Create world constant buffer
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SpriteBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = device->CreateBuffer(&bd, nullptr, m_WorldConstantBuffer.ReleaseAndGetAddressOf());
}

void YESpriteShader::CreateAnimationConstantBuffer()
{
}

void YESpriteShader::UpdateWorldConstantBuffer(const SpriteBuffer& worldBuffer)
{
	ID3D11DeviceContext* context = (ID3D11DeviceContext*) m_Renderer->GetDeviceContext();
	context->UpdateSubresource(m_WorldConstantBuffer.Get(), 0, nullptr, &worldBuffer, 0, 0);
}
