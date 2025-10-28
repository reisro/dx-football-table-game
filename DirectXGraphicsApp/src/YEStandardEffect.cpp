#include "YEStandardEffect.h"	

YEStandardEffect::YEStandardEffect(ID3D11Device* device)
{
	// Matrix Identiy Initialization
	mWorld = XMFLOAT4X4
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, -10.0f, 1.0f
	};
	mView = XMFLOAT4X4
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	mProj = XMFLOAT4X4
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	WorldViewProj = EffectTech->GetVariableByName("gWorldViewProj")->AsMatrix();
	World = EffectTech->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose = EffectTech->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	EyePosW = EffectTech->GetVariableByName("gEyePosW")->AsVector();
}

YEStandardEffect::~YEStandardEffect()
{
}

void YEStandardEffect::Begin()
{
}

void YEStandardEffect::Destroy()
{
}
