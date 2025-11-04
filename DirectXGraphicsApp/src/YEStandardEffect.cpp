#include "YEStandardEffect.h"	
#include <D3DX11.h>
#include "DXAPI.h"

YEStandardEffect::YEStandardEffect(ID3D11Device* device)
{
	// Matrix Identiy Initialization
	mWorld = XMFLOAT4X4
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 14.0f, 1.0f
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

	CreateEffectFromMemory(device, L"C:\DirectX\graphicsapplication\\DirectXGraphicsApp\\shaders\\WorldTransformation.fxo");

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

void YEStandardEffect::CreateEffectFromMemory(ID3D11Device* device, const std::wstring& filename)
{
	/*std::ifstream fin(filename, std::ios::binary);
	
	if (!fin)
	{
		MessageBoxA(0, "Could not open the FX file.", 0, 0);
		return;
	}

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();*/

	DWORD shaderFlags = 0;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	HRESULT hr = D3DX11CompileFromFile(L"C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\shaders\\WorldTransformation.fx", 0, 0, 0, "fx_5_0", shaderFlags,
		0, 0, &compiledShader, &compilationMsgs, 0);

	//// compilationMsgs can store errors or warnings.
	if (compilationMsgs != 0)
	{
		MessageBoxA(0, (char*)compilationMsgs->GetBufferPointer(), 0, 0);
		ReleaseCOM(compilationMsgs);
	}

	//// Even if there are no compilationMsgs, check to make sure there were no other errors.
	if (FAILED(hr))
	{
		DXLog("Shader Compilation errors.");
	}

	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, device, &EffectTech);
}