#pragma once

#ifndef YE_SPRITE_H
#define YE_SPRITE_H

#include "DXAPI.h"
#include "../3rdparty/texture/WICTextureLoader.h"
#include "stb_image.h"
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

class DX_API YESprite
{
public:
	YESprite(YERenderer* renderer);
	virtual ~YESprite();

	void Create();
	void Render();

	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

	ID3D11ShaderResourceView* _texture = NULL;

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
