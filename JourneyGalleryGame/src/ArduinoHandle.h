#pragma once
#include "windows.h"

class ArduinoHandle
{
public:
	explicit ArduinoHandle();
	void SwitchLedRed();
	void SwitchLedBlue();
	void CloseCom();
	int ReadDDR();
	void screenMessage(const char* message);
private:
	HANDLE h_Serial;

};