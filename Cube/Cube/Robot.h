#pragma once
#include<winsock.h>
#include<stdio.h>
#include<math.h>
#include<windows.h>
#include<string.h>
#include<string>
#include<conio.h>//conio��Console Input/Output������̨����������ļ�д�����ж�����ͨ������̨���������������������ĺ�������Ҫ��һЩ�û�ͨ�������̲����Ķ�Ӧ����������getch()�����ȵȡ�
#include<iostream>
#include<sstream>//�ַ�������
#include <atlbase.h>
#include <stdlib.h>
#include "Engine.h"
using namespace std;


#define SERVER_ADDRESS "192.168.1.2"//��������IP��ַ
#define PORT 30003                  //�������˿ں�
#define MSGSIZE 1024                //�շ��������Ĵ�С
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
	double x, y, z, Rx, Ry, Rz, a, v;            //����������
	string instruct;                       //������ָ����Ϣ
	WORD wVersionRequested;                //typedef unsignedshort     WORD;
	WSADATA wsaData;                       //WSADATA��һ�����ݽṹ������ṹ�������洢��WSAStartup�������ú󷵻ص�Windows Sockets���ݡ�������Winsock.dllִ�е����ݡ�
	SOCKADDR_IN server;                    //�շ�������
	SOCKET sClient;                        
	void Init();                           //��ʼ��������
	string int2str(const double &int_temp);//��double����ת����string����
	void Produce();//���ɷ���ָ��
	const int STOPTIME = 3000;

//OP����
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

