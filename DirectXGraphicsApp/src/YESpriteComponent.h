#pragma once
#pragma warning(disable : 4838) 

#ifndef _YE_SPRITE_COMPONENT_H_
#define _YE_SPRITE_COMPONENT_H_

#include "YEBaseComponent.h"
#include "YEGameContext.h"
#include "YESprite.h"

class YEPhysics;

class DX_API YESpriteComponent : public YEBaseComponent
{
public:
	YESpriteComponent();
	YESpriteComponent(YEGameObject* owner);
	YESpriteComponent(const YEGameContext& game_context);
	virtual ~YESpriteComponent();

	virtual void start() override;
	virtual void shutdown() override;
	virtual void update(float _deltaTime) override;

	void LoadTexture(const char* pFileName, int width, int height);

private:
	YESprite* _sprite;
};

#endif