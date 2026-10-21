#include "YESpriteComponent.h"
#include "YERenderer.h"

YESpriteComponent::YESpriteComponent():
	_sprite(new YESprite(YERenderer::GetInstance()))
{
}

YESpriteComponent::YESpriteComponent(YEGameObject* owner):
	_sprite(new YESprite(YERenderer::GetInstance()))
{
}

YESpriteComponent::YESpriteComponent(const YEGameContext& game_context):
	_sprite(new YESprite(YERenderer::GetInstance()))
{
}

YESpriteComponent::~YESpriteComponent()
{
}

void YESpriteComponent::start()
{
}

void YESpriteComponent::shutdown()
{
}

void YESpriteComponent::update(float _deltaTime)
{
}

void YESpriteComponent::LoadTexture(const char* pFileName, int width, int height)
{
	const char* _executablePath = YEFileSystem::FindExecutablePath(pFileName);

	if (_sprite->LoadTextureFromFile(_executablePath, &_sprite->_texture, &width, &height))
		YELog("YESpriteComponent: Successfull loaded texture.");

	YERenderer* renderer = YERenderer::GetInstance();

	renderer->GetSceneObject()->_spritesToRender.push_back(*_sprite);
}

void YESpriteComponent::RemoveTexture()
{
	YERenderer* renderer = YERenderer::GetInstance();

	renderer->GetSceneObject()->_sceneUI.showUI = false;
}
