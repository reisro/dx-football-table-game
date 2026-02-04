#include "FTGoalWidgetUI.h"
#include "YERenderer.h"

FTGoalWidgetUI::FTGoalWidgetUI(const YEGameContext& _game_context):
image_width(1024),
image_height(768),
_sprite_component(new YESpriteComponent)
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
}

void FTGoalWidgetUI::SetGameMenuText()
{
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg = "";
}

void FTGoalWidgetUI::Show()
{
	SetGameMenuText();

	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.spriteID++;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.showUI = true;
}