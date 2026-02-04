#pragma once

#ifndef _FT_GAME_MAIN_MENU_H_
#define _FT_GAME_MAIN_MENU_H_

#include "YEGameObject.h"
#include "YESpriteComponent.h"
#include <YEInput.h>

class FTGameMainMenu : public YEGameObject
{
public:
	FTGameMainMenu(const YEGameContext& _game_context);
	virtual ~FTGameMainMenu();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

protected:
	YESpriteComponent* _sprite_component;

private:
	int image_width;
	int image_height;
	YEInput* _input;
};

#endif _FT_GAME_MAIN_MENU_H_