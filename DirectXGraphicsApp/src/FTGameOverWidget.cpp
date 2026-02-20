#include "FTGameOverWidget.h"
#include "YERenderer.h"

FTGameOverWidget::FTGameOverWidget(const YEGameContext& _game_context):
	YEGameObject("Football Game Over Widget", _game_context),
	_sprite_component(new YESpriteComponent),
	_onShow(false),
	_yeInput(YEInput::GetInstance()),
	_uiText(""),
	_uiText2("")
{
	addComponent(_sprite_component);
}

FTGameOverWidget::~FTGameOverWidget()
{
}

void FTGameOverWidget::start()
{
	_sprite_component->LoadTexture("C:\\DirectX\\graphicsapplication\\DirectXGraphicsApp\\bin\\x64\\Debug\\Game Assets\\ftgame_none.png", image_width, image_height);
}

void FTGameOverWidget::shutdown()
{
}

void FTGameOverWidget::update(float _deltaTime)
{
	YEGameObject::update(_deltaTime);

	if (_onShow)
	{
		if (_yeInput->keyDown(DIK_SPACE))
			OnSpaceKeyPressed();
	}
}

void FTGameOverWidget::SetGameMenuText(const char* msg)
{
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.showUI = true;

	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.spriteID = 2;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg = msg;
	YERenderer::GetInstance()->GetSceneObject()->_sceneUI.textMsg2 = "Press SPACE to play again";

	OnWidgetShows();
}