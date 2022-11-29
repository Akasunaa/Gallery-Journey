#include "ArduinoHandle.h"
#include <iostream>

ArduinoHandle::ArduinoHandle(){
    //Port d'entree ------------
    char  ComPortName[] = "\\\\.\\COM12";
    h_Serial = CreateFile(ComPortName, GENERIC_READ | GENERIC_WRITE, // Read/Write Access
        0,                            // No Sharing, ports cant be shared
        NULL,                         // No Security
        OPEN_EXISTING,                // Open existing port only
        0,                            // Non Overlapped I/O
        NULL);
    if (h_Serial == INVALID_HANDLE_VALUE) {
        std::cout << "no handle?";
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            std::cout << "serial port not found.";
        }
        //any other error. Handle error here.
    }

    //basic prop -----------
    DCB dcbSerialParam = { 0 };
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(h_Serial, &dcbSerialParam)) {
        //handle error here
    }

    dcbSerialParam.BaudRate = CBR_9600;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity = NOPARITY;

    if (!SetCommState(h_Serial, &dcbSerialParam)) {
        //handle error here
    }


    //set the timeout ------------
    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 60;
    timeout.ReadTotalTimeoutConstant = 60;
    timeout.ReadTotalTimeoutMultiplier = 15;
    timeout.WriteTotalTimeoutConstant = 60;
    timeout.WriteTotalTimeoutMultiplier = 8;
    if (!SetCommTimeouts(h_Serial, &timeout)) {
        //handle error here
    }

}

void ArduinoHandle::SwitchLed() {
    char sBuff[2] = { 0 };
    DWORD dwRead = 5;
    if (!WriteFile(h_Serial, sBuff, 1, &dwRead, NULL)) {
        std::cout << "not fun";
    }
}

void ArduinoHandle::CloseCom() {
    CloseHandle(h_Serial);
}
