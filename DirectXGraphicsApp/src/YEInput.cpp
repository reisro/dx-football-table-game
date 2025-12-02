#include "YEInput.h"
#include "DXConfig.h"

YEInput* YEInput::_instance = nullptr;

YEInput::YEInput()
{
	_instance = this;
}

YEInput::~YEInput()
{
	_instance = nullptr;
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
	return false;
}

void YEInput::PostInit()
{
}

void YEInput::Clean()
{
}

bool YEInput::keyDown(int keycode)
{
	return (_mKeyboardState[keycode] & 0x80) != 0;
}