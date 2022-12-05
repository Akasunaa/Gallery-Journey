#pragma once
#include "windows.h"

class ArduinoHandle
{
public:
	explicit ArduinoHandle();
	void SwitchLedRed();
	void SwitchLedBlue();
	void CloseCom();
	void ReadDDR();
private:
	HANDLE h_Serial;

};