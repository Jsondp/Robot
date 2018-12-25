#pragma once
#include<winsock.h>
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<string.h>
#include<string>
#include<conio.h>//conio是Console Input/Output（控制台输入输出）的简写，其中定义了通过控制台进行数据输入和数据输出的函数，主要是一些用户通过按键盘产生的对应操作，比如getch()函数等等。
#include<iostream>
#include<sstream>//字符串处理
#include <atlbase.h>
#include <stdlib.h>
#include "Engine.h"
using namespace std;


#define SERVER_ADDRESS "192.168.1.2"//服务器端IP地址
#define PORT 30003                  //服务器端口号
#define MSGSIZE 1024                //收发缓冲区的大小
#pragma comment(lib, "ws2_32.lib")  

class Robot
{
public:
	
	Robot();
	~Robot();
	void UpAnti_Clockwise();
	void UpClockwise();
	void RightAnti_Clockwise();
	void RingtClockwise();
	void LeftAnti_Clockwise();
	void LeftClockwise();
	void DownAnti_Clockwise();
	void DownClockwise();
	void FrontAnti_Clockwise();
	void FrontClockwise();
	void BackAnti_Clockwise();
	void BackClockwise();

private:
	Engine setEngine;
	double x, y, z, Rx, Ry, Rz, a, v;            //机器人坐标
	string instruct;                       //机器人指令信息
	WORD wVersionRequested;                //typedef unsignedshort     WORD;
	WSADATA wsaData;                       //WSADATA，一种数据结构。这个结构被用来存储被WSAStartup函数调用后返回的Windows Sockets数据。它包含Winsock.dll执行的数据。
	SOCKADDR_IN server;                    //收发缓冲区
	SOCKET sClient;                        
	void Init();                           //初始化机器人
	string int2str(const double &int_temp);//将double类型转换成string类型
	void Produce();//生成发送指令
	const int STOPTIME = 3000;

//OP操作
	void op();
	void op1();
	void op2();
	void op3();
	void op4();//...
	void op5();
	void op6();
	void op7();
	void op8();
	void op9();
	void op10();
	void op11();
	void op12();
	void op13();
	void op14();
	void op15();
	void op16();
	void op17();
	void op18();
	void op19();
	void op20();

	void OPP1();
	void OPP2();
};

