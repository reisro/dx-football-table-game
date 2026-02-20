#include "FTGameMainMenu.h"

FTGameMainMenu::FTGameMainMenu(const YEGameContext& _game_context):
	image_width(1024),
	image_height(768),
	_sprite_component(new YESpriteComponent),
	_uiText("\n\t\t\t\t\t\t\t\t\t\tPress SPACE to begin")
{
	addComponent(_sprite_component);
}

FTGameMainMenu::~FTGameMainMenu()
{
}

void FTGameMainMenu::start()
{
	_sprite_component->LoadTexture("C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\bin\\x64\\Debug\\Game Assets\\ftgame_logo.png", image_width, image_height);

	SetGameMenuText();	

	_input = YEInput::GetInstance();
}

void FTGameMainMenu::shutdown()
{
}

void FTGameMainMenu::update(float _deltaTime)
{
	if (_input->keyDown(DIK_SPACE))
		OnMainMenuKeyPressed();
}

void FTGameMainMenu::SetGameMenuText()
{
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg = _uiText;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg2 = "";
}
