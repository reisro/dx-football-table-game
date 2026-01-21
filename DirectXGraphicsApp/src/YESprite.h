#pragma once

#ifndef YE_SPRITE_H
#define YE_SPRITE_H

#include "DXAPI.h"
#include "WICTextureLoader.h"
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>
#include <filesystem>

using Microsoft::WRL::ComPtr;

class YERenderer;

struct SpriteVertex
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	float width = 0.0f;
	float height = 0.0f;
};

class YESprite
{
public:
	YESprite(YERenderer* renderer);
	virtual ~YESprite();

	void Create();
	void Render();

private:

	YERenderer* _mRenderer = nullptr;

	// Vertex buffer
	ComPtr<ID3D11Buffer> m_VertexBuffer = nullptr;
	void CreateVertexBuffer();

	// Vertices
	std::vector<SpriteVertex> m_Vertices;

	// Texture buffer
	void LoadTexture();
	ComPtr<ID3D11ShaderResourceView> m_DiffuseTexture = nullptr;
};

#endif
