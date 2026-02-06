#pragma once

#ifndef _FT_GAME_GOAL_H_
#define _FT_GAME_GOAL_H_

#include "YEGameObject.h"
#include "YESpriteComponent.h"
#include "YETimer.h"
#include <functional>

class FTGoalWidgetUI : public YEGameObject
{
public:
	FTGoalWidgetUI(const YEGameContext& _game_context);
	virtual ~FTGoalWidgetUI();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	void SetGameMenuText();
	void Show();

	std::function<void(void)> OnWidgetUIHide;

protected:
	YESpriteComponent* _sprite_component;

private:
	int image_width;
	int image_height;
	bool _onShow;

	YETimer* _timer;
};

#endif _FT_GAME_GOAL_H_