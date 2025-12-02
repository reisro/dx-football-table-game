#pragma once

#ifndef _YE_INPUT_H
#define _YE_INPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include "DXAPI.h"
#include "DXSubsystem.h"
#include <dinput.h>

class DX_API YEInput : public DXSubsystem
{
public:
	YEInput();
	virtual ~YEInput();

	// Starts up all procedures for a specific susbsystem
	virtual void Setup() override;

	// Required operations to start for this subsystem
	virtual bool Init() override;

	// Operations needed after initialization
	virtual void PostInit() override;

	// Clean resources before shutting down
	virtual void Clean() override;

	bool keyDown(int keycode);

private:
	static YEInput* _instance;
	
	char		    _mKeyboardState[256];
	IDirectInput8*  _dInput;
};

#endif // _YE_INPUT_H