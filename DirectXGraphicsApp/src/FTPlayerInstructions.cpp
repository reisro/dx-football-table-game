#include "FTPlayerInstructions.h"

FTPlayerInstructions::FTPlayerInstructions(const YEGameContext& _game_context):
	YEGameObject("Football Player Instructions", _game_context),
	_sprite_component(new YESpriteComponent),
	_uiText("\t\t\t\t\t\t\t\t\tAD move player W shoot"),
	_uiText2("\t\t\t\t\tLEFT RIGHT move keeper UP shoot\n\t\t\t\t\t\t\t\t Press P to start match")
{
}

FTPlayerInstructions::~FTPlayerInstructions()
{
}

void FTPlayerInstructions::start()
{
	_sprite_component->LoadTexture("C:\\Game Assets\\TEXTURES\\ftgame_none.png", image_width, image_height);

	_input = YEInput::GetInstance();
}

void FTPlayerInstructions::shutdown()
{
}

void FTPlayerInstructions::update(float _deltaTime)
{
	if (_input->keyDown(DIK_P))
	{
		OnPKeyPressed();

		CloseInstructions();
	}
}

void FTPlayerInstructions::SetGameMenuText()
{
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.spriteID = 1;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg = _uiText;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg2 = _uiText2;
}

void FTPlayerInstructions::CloseInstructions()
{
	YERenderer* renderer = YERenderer::GetInstance();

	renderer->GetSceneObject()->_sceneUI.showUI = false;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg = "";
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg2 = "";
}
