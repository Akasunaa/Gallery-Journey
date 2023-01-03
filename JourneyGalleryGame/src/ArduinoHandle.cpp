#include "ArduinoHandle.h"
#include <iostream>
#include <string>

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
    DWORD dwWrite;
    const char* message = "red";
    if (!WriteFile(h_Serial, message, strlen(message), &dwWrite, NULL)) {
        std::cout << "error red led";
    }
    std::cout << "red";
}

void ArduinoHandle::SwitchLedBlue() {
    DWORD dwWrite;
    const char* message = "blue";
    if (!WriteFile(h_Serial, message, strlen(message), &dwWrite, NULL)) {
        std::cout << "error blue led";
    }
    std::cout << "blue";
}

void ArduinoHandle::screenMessage(const char* message)
{
    DWORD dwWrite;
    if (!WriteFile(h_Serial, message, strlen(message), &dwWrite, NULL)) {
        std::cout << "error message";
    }
    std::cout << "screen message";
}


int ArduinoHandle::ReadDDR() {
    char sBuff[2]={0};
    DWORD dwRead;
    if (!ReadFile(h_Serial, sBuff, 1, &dwRead, NULL)) {
        std::cout << "error ddr";
    }
    std::cout << sBuff;
    if (strlen(sBuff) > 0) { 
        switch (sBuff[0]) {
        case '1':
            return 0;
            break;
        case '4':
            return 1;
            break;
        case '7':
            return 2;
            break;
        case '*':
            return 3;
            break; 
        case '2':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '8':
            return 6;
            break;
        case '0':
            return 7;
            break;
        case '3':
            return 8;
            break;
        case '6':
            return 9;
            break;
        case '9':
            return 10;
            break;
        case '#':
            return 11;
            break;
        case 'A':
            return 12;
            break;
        case 'B':
            return 13;
            break;
        case 'C':
            return 14;
            break;
        case 'D':
            return 15;
            break;
        }
    }
    return -1;
}




void ArduinoHandle::CloseCom() {
    CloseHandle(h_Serial);
}
