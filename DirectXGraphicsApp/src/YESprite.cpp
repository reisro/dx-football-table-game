#include "YESprite.h"
#include "YERenderer.h"

YESprite::YESprite(YERenderer* renderer)
{
	_mRenderer = renderer;
}

YESprite::~YESprite()
{
}

void YESprite::Create()
{
	CreateVertexBuffer();
	LoadTexture();
}

void YESprite::Render()
{
    ID3D11DeviceContext* context = (ID3D11DeviceContext*)_mRenderer->GetDeviceContext();

    // We need the stride and offset for the vertex
    UINT vertex_stride = sizeof(SpriteVertex);
    UINT vertex_offset = 0;

    // Bind the vertex buffer to the Input Assembler
    context->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &vertex_stride, &vertex_offset);

    // Bind the geometry topology to the Input Assembler
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

    // Bind texture to the pixel shader
    context->PSSetShaderResources(0, 1, m_DiffuseTexture.GetAddressOf());

    // Render geometry
    context->Draw(static_cast<UINT>(m_Vertices.size()), 0);
}

void YESprite::CreateVertexBuffer()
{
	ID3D11Device* device = (ID3D11Device*)_mRenderer->GetDevice();

	m_Vertices.push_back({ 0.0f, 1.0f, 0.0f, 1.0f, 1.0f });

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SpriteVertex) * static_cast<UINT>(m_Vertices.size());
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = m_Vertices.data();

	HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexData, m_VertexBuffer.ReleaseAndGetAddressOf());
}

void YESprite::LoadTexture()
{
	std::wstring path = L"C:\\DirectX\\RoveCoder-DirectX11-Samples-master\\RoveCoder-DirectX11-Samples-master\\Resources\\Textures\\doughnut_sprite_sheet.png";

    // Check if file exists
    if (!std::filesystem::exists(path))
    {
        std::wstring error = L"Could not load file: " + path;
        MessageBox(NULL, error.c_str(), L"Error", MB_OK);
        return;
    }

    ID3D11Device* device = (ID3D11Device*)_mRenderer->GetDevice();
    ID3D11DeviceContext* context = (ID3D11DeviceContext*) _mRenderer->GetDeviceContext();

    // Load sprite sheet
    ComPtr<ID3D11Resource> spriteSheetResource;
    ComPtr<ID3D11ShaderResourceView> tempSRV;
    HRESULT HR = CreateWICTextureFromFile(device, context, path.c_str(), spriteSheetResource.ReleaseAndGetAddressOf(), tempSRV.ReleaseAndGetAddressOf());

    // Get texture description
    D3D11_TEXTURE2D_DESC sheetDesc = {};
    ComPtr<ID3D11Texture2D> spriteSheetTex;
    spriteSheetResource.As(&spriteSheetTex);
    spriteSheetTex->GetDesc(&sheetDesc);

    // Define sprite sheet parameters (Adjust these based on your sprite sheet layout)
    const int frameWidth = 512;
    const int frameHeight = 512;
    const int columns = sheetDesc.Width / frameWidth;
    const int rows = sheetDesc.Height / frameHeight;
    const int frameCount = columns * rows;

    // Create Texture2DArray for extracted frames
    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = frameWidth;
    texDesc.Height = frameHeight;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = frameCount;
    texDesc.Format = sheetDesc.Format;
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;

    ComPtr<ID3D11Texture2D> textureArray;
   HR = (device->CreateTexture2D(&texDesc, nullptr, textureArray.ReleaseAndGetAddressOf()));

    // Copy frames from sprite sheet into Texture2DArray
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            int index = row * columns + col;

            D3D11_BOX srcBox = {};
            srcBox.left = col * frameWidth;
            srcBox.top = row * frameHeight;
            srcBox.right = srcBox.left + frameWidth;
            srcBox.bottom = srcBox.top + frameHeight;
            srcBox.front = 0;
            srcBox.back = 1;

            context->CopySubresourceRegion(textureArray.Get(), index, 0, 0, 0, spriteSheetTex.Get(), 0, &srcBox);
        }
    }

    // Create Shader Resource View for Texture2DArray
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = texDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
    srvDesc.Texture2DArray.MostDetailedMip = 0;
    srvDesc.Texture2DArray.MipLevels = 1;
    srvDesc.Texture2DArray.FirstArraySlice = 0;
    srvDesc.Texture2DArray.ArraySize = frameCount;

    HR = device->CreateShaderResourceView(textureArray.Get(), &srvDesc, m_DiffuseTexture.ReleaseAndGetAddressOf());
}
