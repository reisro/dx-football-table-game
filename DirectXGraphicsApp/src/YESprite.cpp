#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include "YESprite.h"
#include "YERenderer.h"
#include "imgui.h"

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
	std::wstring path = L"C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\Game Assets\\game_logo.png";

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

bool YESprite::LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    ID3D11Device* device = (ID3D11Device*)_mRenderer->GetDevice();

    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    device->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    device->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

bool YESprite::LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    FILE* f = fopen(file_name, "rb");
    if (f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
        return false;
    fseek(f, 0, SEEK_SET);
    void* file_data = IM_ALLOC(file_size);
    fread(file_data, 1, file_size, f);
    fclose(f);
    bool ret = LoadTextureFromMemory(file_data, file_size, out_srv, out_width, out_height);
    IM_FREE(file_data);
    return ret;
}
