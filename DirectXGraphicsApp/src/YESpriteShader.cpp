#include "YESpriteShader.h"
#include "YERenderer.h"

#include <Windows.h>
#include "../shaders/CompiledSpritePixelShader.hlsl.h"
#include "../shaders/CompiledSpriteVertexShader.hlsl.h"
#include "../shaders/CompiledSpriteGeometryShader.hlsl.h"

YESpriteShader::YESpriteShader(YERenderer* renderer)
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

void YESpriteShader::UpdateWorldConstantBuffer(const WorldBuffer& worldBuffer)
{
}

void YESpriteShader::UpdateAnimationConstantBuffer(const AnimationBuffer& buffer)
{
}

void YESpriteShader::LoadVertexShader()
{
}

void YESpriteShader::LoadPixelShader()
{
}

void YESpriteShader::LoadGeometryShader()
{
}

void YESpriteShader::CreateWorldConstantBuffer()
{
}

void YESpriteShader::CreateAnimationConstantBuffer()
{
}
