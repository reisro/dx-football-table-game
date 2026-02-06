#pragma once

#ifndef _FT_PLAYER_INSTRUCTIONS_H_
#define _FT_PLAYER_INSTRUCTIONS_H_

#include "YEGameObject.h"
#include "YESpriteComponent.h"
#include <YEInput.h>
#include <functional>

class FTPlayerInstructions : public YEGameObject
{
public:
	FTPlayerInstructions(const YEGameContext& _game_context);
	virtual ~FTPlayerInstructions();

	void start() override;
	void shutdown() override;
	void update(float _deltaTime) override;

	void SetGameMenuText();
	void CloseInstructions();

	std::function<void(void)> OnPKeyPressed;

private:
	int image_width;
	int image_height;
	YESpriteComponent* _sprite_component;

	const char* _uiText;
	const char* _uiText2;

	YEInput* _input;
};

#endif _FT_PLAYER_INSTRUCTIONS_H_