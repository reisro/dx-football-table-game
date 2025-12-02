#include "YEInput.h"

YEInput* YEInput::_instance = nullptr;

YEInput::YEInput()
{
	_instance = this;
}

YEInput::~YEInput()
{
	_instance = nullptr;
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