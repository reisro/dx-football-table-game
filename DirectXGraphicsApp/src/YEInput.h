#pragma once

#ifndef _YE_INPUT_H
#define _YE_INPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include "DXAPI.h"
#include "DXSubsystem.h"
#include "YEWinAppWindow.h"
#include <dinput.h>

class DX_API YEInput : public DXSubsystem
{
public:
	YEInput();
	virtual ~YEInput();

	static void CreateInstance();
	static YEInput* GetInstance();

	// Starts up all procedures for a specific susbsystem
	virtual void Setup() override;

	// Required operations to start for this subsystem
	virtual bool Init() override;

	// Operations needed after initialization
	virtual void PostInit() override;

	// Clean resources before shutting down
	virtual void Clean() override;

	void poll();

	bool keyDown(int keycode);

	bool mouseButtonDown(int button);

private:
	static YEInput* _instance;
	
	IDirectInput8*		 _dInput;
	IDirectInputDevice8* _dInputDeviceKeyboard;
	IDirectInputDevice8* _dInputDeviceMouse;

	char				 _mKeyboardState[256];
	DIMOUSESTATE2		 _mMouseState;
};

#endif // _YE_INPUT_H