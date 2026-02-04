#pragma once

#ifndef _FT_GAME_GOAL_H_
#define _FT_GAME_GOAL_H_

#include "YEGameObject.h"
#include "YESpriteComponent.h"

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

protected:
	YESpriteComponent* _sprite_component;

private:
	int image_width;
	int image_height;
};

#endif _FT_GAME_GOAL_H_