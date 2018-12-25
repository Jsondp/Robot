#pragma once
#include<Windows.h>
#include<stdio.h>
class Engine
{
	HANDLE hcom;
	DCB dcb;
public:
	Engine();
	~Engine();
	void send_open();
	void send_close();
};

