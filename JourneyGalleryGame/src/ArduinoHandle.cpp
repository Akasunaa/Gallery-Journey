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
        std::cout << "unknown error";
    }

    //basic prop -----------
    DCB dcbSerialParam = { 0 };
    dcbSerialParam.DCBlength = sizeof(dcbSerialParam);

    if (!GetCommState(h_Serial, &dcbSerialParam)) {
        std::cout << "error get com";
    }

    dcbSerialParam.BaudRate = CBR_9600;
    dcbSerialParam.ByteSize = 8;
    dcbSerialParam.StopBits = ONESTOPBIT;
    dcbSerialParam.Parity = NOPARITY;

    if (!SetCommState(h_Serial, &dcbSerialParam)) {
        std::cout << "error basic prop";
    }

    //set the timeout ------------
    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 60;
    timeout.ReadTotalTimeoutConstant = 60;
    timeout.ReadTotalTimeoutMultiplier = 15;
    timeout.WriteTotalTimeoutConstant = 60;
    timeout.WriteTotalTimeoutMultiplier = 8;
    if (!SetCommTimeouts(h_Serial, &timeout)) {
        std::cout << "error timeout";
    }

}

void ArduinoHandle::SwitchLedRed() {
    char sBuff[2] = { 0 };
    DWORD dwWrite;
    if (!WriteFile(h_Serial, sBuff, strlen(sBuff), &dwWrite, NULL)) {
        std::cout << "error red led";

    }
    std::cout << "red";
}

void ArduinoHandle::SwitchLedBlue() {
    char sBuff[2] = {1};
    DWORD dwWrite;
    if (!WriteFile(h_Serial, sBuff, strlen(sBuff), &dwWrite, NULL)) {
        std::cout << "error blue led";
    }
    std::cout << "blue";
}

void ArduinoHandle::ReadDDR() {
    char sBuff[2]={0};
    DWORD dwRead;
    if (!ReadFile(h_Serial, sBuff, 1, &dwRead, NULL)) {
        std::cout << "error ddr";
    }
    std::cout << sBuff;
}



void ArduinoHandle::CloseCom() {
    CloseHandle(h_Serial);
}
