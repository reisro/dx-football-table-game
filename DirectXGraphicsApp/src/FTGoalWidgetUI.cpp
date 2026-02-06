#include "FTGoalWidgetUI.h"
#include "YERenderer.h"

FTGoalWidgetUI::FTGoalWidgetUI(const YEGameContext& _game_context):
	image_width(1024),
	image_height(768),
	_sprite_component(new YESpriteComponent),
	_timer(new YETimer())
{
	addComponent(_sprite_component);
}

FTGoalWidgetUI::~FTGoalWidgetUI()
{
}

void FTGoalWidgetUI::start()
{
	_sprite_component->LoadTexture("C:\\Game Assets\\TEXTURES\\ftgame_goal_ui.png", image_width, image_height);
}

void FTGoalWidgetUI::shutdown()
{
}

void FTGoalWidgetUI::update(float _deltaTime)
{
	if (_timer->Countdown(2) && _onShow)
	{
		YERenderer::GetInstance()->GetSceneObject()->_sceneUI.showUI = false;

		OnWidgetUIHide();

		_onShow = false;
	}
}

void FTGoalWidgetUI::SetGameMenuText()
{
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg = "";
}

void FTGoalWidgetUI::Show()
{
	SetGameMenuText();

	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.spriteID = 2;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.showUI = true;

	_onShow = true;
}