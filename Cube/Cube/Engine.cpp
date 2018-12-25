#include "Engine.h"

Engine::Engine()
{
	hcom = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hcom == INVALID_HANDLE_VALUE){
		printf("connection fail!!!\n");
		return;
	}
	SetupComm(hcom, 1024, 1024);
	GetCommState(hcom, &dcb);
	dcb.BaudRate = 4800;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 1;
	SetCommState(hcom, &dcb);
}


Engine::~Engine()
{
}

void Engine::send_open(){
	Sleep(1000);
	char data = 'O';
	DWORD dwWrittenLen = 0;
	if (!WriteFile(hcom, &data, 8, &dwWrittenLen, NULL)){
		printf("1\n");
	}
}

void Engine::send_close(){
	Sleep(1000);
	char data = 'C';
	DWORD dwWrittenLen = 0;
	if (!WriteFile(hcom, &data, 8, &dwWrittenLen, NULL)){
		printf("1\n");
	}
}