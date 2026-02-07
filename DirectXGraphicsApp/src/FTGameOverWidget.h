#pragma once

#ifndef _FT_GAME_OVER_WIDGET_H_
#define _FT_GAME_OVER_WIDGET_H_

#include "YEGameObject.h"
#include "YESpriteComponent.h"
#include "YEInput.h"
#include <functional>

class FTGameOverWidget : public YEGameObject
{
public:
	FTGameOverWidget(const YEGameContext& _game_context);
	virtual ~FTGameOverWidget();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	void SetGameMenuText(const char* msg);
	void Show();

	std::function<void(void)> OnWidgetShows;
	std::function<void(void)> OnSpaceKeyPressed;

protected:
	YESpriteComponent* _sprite_component;

private:
	int image_width;
	int image_height;
	bool _onShow;

	const char* _uiText;
	const char* _uiText2;

	YEInput* _yeInput;

};

#endif _FT_GAME_OVER_WIDGET_H_