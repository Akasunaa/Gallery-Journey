#pragma once
#include "windows.h"

class ArduinoHandle
{
public:
	explicit ArduinoHandle();
	void SwitchLed();
	void CloseCom();

private:
	HANDLE h_Serial;

};