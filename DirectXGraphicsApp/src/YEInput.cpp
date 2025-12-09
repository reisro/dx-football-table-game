#include "YEInput.h"
#include "DXConfig.h"

YEInput* YEInput::_instance = nullptr;

YEInput::YEInput()
{
	
}

YEInput::~YEInput()
{
	_instance = nullptr;

	_DXGE_SAFE_RELEASE(_dInput);
	_DXGE_SAFE_RELEASE(_dInputDeviceKeyboard);

	_dInputDeviceKeyboard->Unacquire();
	_dInputDeviceMouse->Unacquire();

	_DXGE_SAFE_RELEASE(_dInputDeviceMouse);
}

void YEInput::CreateInstance()
{
	if (YEngineConfig::YEConfig::instance.inputAPI == YEngineConfig::InputAPI::DirectInput)
	{
		_instance = new YEInput();
	}
}

YEInput* YEInput::GetInstance()
{
	return _instance;
}

void YEInput::Setup()
{
}

bool YEInput::Init()
{
	ZeroMemory(_mKeyboardState, sizeof(_mKeyboardState));
	ZeroMemory(&_mMouseState, sizeof(_mMouseState));

	YEWinAppWindow* outputWindow = dynamic_cast<YEWinAppWindow*>(YEWindow::GetInstance());

	HR(DirectInput8Create(outputWindow->GetHInstance(), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&_dInput, 0));

	// Keyboard device initalization
	HR(_dInput->CreateDevice(GUID_SysKeyboard, &_dInputDeviceKeyboard, 0));
	HR(_dInputDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard));
	HR(_dInputDeviceKeyboard->SetCooperativeLevel(outputWindow->GetWindowsHandle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
	HR(_dInputDeviceKeyboard->Acquire());

	// Mouse device initalization
	HR(_dInput->CreateDevice(GUID_SysMouse, &_dInputDeviceMouse, 0));
	HR(_dInputDeviceMouse->SetDataFormat(&c_dfDIMouse2));
	HR(_dInputDeviceMouse->SetCooperativeLevel(outputWindow->GetWindowsHandle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
	HR(_dInputDeviceMouse->Acquire());

	return true;
}

void YEInput::PostInit()
{
}

void YEInput::Clean()
{
}

void YEInput::poll()
{
	HRESULT hr = _dInputDeviceKeyboard->GetDeviceState(sizeof(_mKeyboardState), (void **)&_mKeyboardState);
	
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			// if lost set to zero
			ZeroMemory(_mKeyboardState, sizeof(_mKeyboardState));

			_dInputDeviceKeyboard->Acquire();
		}
	}

	hr = _dInputDeviceMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (LPVOID)&_mKeyboardState);

	if (FAILED(hr))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			// if lost set to zero
			ZeroMemory(&_mMouseState, sizeof(_mMouseState));
			_dInputDeviceMouse->Acquire();
		}
	}
}

bool YEInput::keyDown(int keycode)
{
	return (_mKeyboardState[keycode] & 0x80) != 0;
}

bool YEInput::mouseButtonDown(int button)
{
	return (_mMouseState.rgbButtons[button] & 0x80) != 0;
}