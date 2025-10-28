#pragma once

#ifndef _YESTANDARD_EFFECTS_H
#define _YESTANDARD_EFFECTS_H

#include <string>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include "d3dx11effect.h"

using namespace DirectX;
using namespace DirectX::PackedVector;

class YEStandardEffect
{
	public:
		YEStandardEffect(ID3D11Device* device);
		~YEStandardEffect();

	static void Begin();
	static void Destroy();

	void SetWorldViewProj(DirectX::CXMMATRIX M) { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(DirectX::CXMMATRIX M) { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(DirectX::CXMMATRIX M) { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const DirectX::XMFLOAT3& v) { EyePosW->SetRawValue(&v, 0, sizeof(DirectX::XMFLOAT3)); }

	private:
		ID3D11Device* _fx;
		XMFLOAT4X4 mWorld;
		XMFLOAT4X4 mView;
		XMFLOAT4X4 mProj;

		ID3DX11EffectMatrixVariable* WorldViewProj;
		ID3DX11EffectMatrixVariable* World;
		ID3DX11EffectMatrixVariable* WorldInvTranspose;
		ID3DX11EffectVectorVariable* EyePosW;

		ID3DX11Effect* EffectTech;

		std::string effect_file_name = "FX/StandardEffect.fx";
};

#endif _YESTANDARD_EFFECTS_H