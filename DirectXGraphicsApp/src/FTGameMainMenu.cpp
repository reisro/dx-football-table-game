#include "FTGameMainMenu.h"

FTGameMainMenu::FTGameMainMenu(const YEGameContext& _game_context):
	image_width(1024),
	image_height(768),
	_sprite_component(new YESpriteComponent)
{
	addComponent(_sprite_component);
}

FTGameMainMenu::~FTGameMainMenu()
{
}

void FTGameMainMenu::start()
{
	_sprite_component->LoadTexture("C:\\Game Assets\\TEXTURES\\ftgame_logo.png", image_width, image_height);

	SetGameMenuText();	

	_input = YEInput::GetInstance();
}

void FTGameMainMenu::shutdown()
{
}

void FTGameMainMenu::update(float _deltaTime)
{
	if (_input->keyDown(DIK_SPACE))
		_sprite_component->RemoveTexture();
}

void FTGameMainMenu::SetGameMenuText()
{
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg = "Press SPACE to play";
}
