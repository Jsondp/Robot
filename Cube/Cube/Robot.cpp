#include "Robot.h"

Robot::Robot()
{
	Init();
}


Robot::~Robot()
{
	closesocket(sClient);//结束与机器人的连接
	WSACleanup();  //解除Socket库的加载并且释放一定的资源
}

void Robot::Init(){
	setEngine.send_open();
	//Sleep(2000);
	//初始化窗口套接字图书馆  初始化Winsock DLL
	WSAStartup(0x0202, &wsaData);
	//创建客户端套接字
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//AF_INET指明使用TCP/IP协议；
	//SOCK_STREAM，IPPROTO_TCP具体指明使用的TCP协议
	//指明远程服务器的地址信息（端口号、IP地址等）
	memset(&server, 0, sizeof(SOCKADDR_IN));//先将保存地址的server设置为0
	server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式
	server.sin_port = htons(PORT); //指明服务器的端口号
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);//指明服务器IP地址
	int error = -1;
	int len = sizeof(int);
	timeval tm;
	fd_set set;
	unsigned long ul = 1;
	ioctlsocket(sClient, FIONBIO, &ul);
	if (connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN)) == -1){//与机器人建立连接
		printf("connect failed:%d\n", errno);
	}
	else{
		printf("connect success\n");
	}
	ul = 0;
	ioctlsocket(sClient, FIONBIO, &ul);
	op();
	//setEngine.send_open();
	setEngine.send_close();
}

string Robot::int2str(const double &int_temp){
	string string_temp;
	stringstream stream;
	stream << int_temp;
	string_temp = stream.str();
	return string_temp;
}

void Robot::Produce(){
	instruct.clear();
	instruct = "movej(p[";
	instruct += int2str(x / 1000);
	instruct += ",";
	instruct += int2str(y / 1000);
	instruct += ",";
	instruct += int2str(z / 1000);
	instruct += ",";
	instruct += int2str(Rx / 180 *3.1415);
	//instruct += int2str(Rx);
	instruct += ",";
	instruct += int2str(Ry / 180 * 3.1415);
	//instruct += int2str(Ry);
	instruct += ",";
	instruct += int2str(Rz / 180 * 3.1415);
	//instruct += int2str(Rz);
	instruct += "],a=";
	instruct += int2str(a);
	instruct += ",v=";
	instruct += int2str(v);
	instruct += ")\n";
}

void Robot::op(){//复位
	x = -10.361;
	y = -380.910;
	z = 330.216;
	Rx = 171.430;
	Ry = -8.646;
	Rz = 8.113;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op1(){//向下
	x = 2.448;
	y = -395.051;
	z = 165.900;
	Rx = 177.391;
	Ry = -6.823;
	Rz = 2.264;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op2(){//逆旋转
	x = 2.438;
	y = -395.040;
	z = 176.888;
	Rx = 122.306;
	Ry = -126.681;
	Rz = -0.990;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op3(){//顺旋转
	x = 2.446;
	y = -395.067;
	z = 176.935;
	Rx = 129.165;
	Ry = 124.336;
	Rz = 4.365;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op9(){
	x = -134.102;
	y = -356.652;
	z = 330.261;
	Rx = 167.417;
	Ry = -34.773;
	Rz = 6.109;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op10(){
	x = -135.252;
	y = -356.993;
	z = 161.546;
	Rx = -173.854;
	Ry = 36.568;
	Rz = -2.465;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op11(){
	x = -231.594;
	y = -308.311;
	z = 54.802;
	Rx = -54.004;
	Ry = 90.032;
	Rz = -84.743;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op12(){
	x = -252.331;
	y = -317.544;
	z = 112.944;
	Rx = -58.133;
	Ry = 93.340;
	Rz = -76.756;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op13(){
	x = -10.366;
	y = -380.924;
	z = 330.220;
	Rx = 117.747;
	Ry = -132.847;
	Rz = 14.936;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op14(){
	x = 0.582;
	y = -407.960;
	z = 154.505;
	Rx = -118.426;
	Ry = 133.189;
	Rz = -6.127;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op15(){
	x = -24.396;
	y = -379.828;
	z = 426.284;
	Rx = -10.688;
	Ry = -9.411;
	Rz = 179.371;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op16(){
	x = -82.454;
	y = -354.416;
	z = 218.106;
	Rx = 11.239;
	Ry = 119.571;
	Rz = -133.721;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op17(){
	x = -110.546;
	y = -250.912;
	z = 53.608;
	Rx = -20.294;
	Ry = -116.672;
	Rz = 120.829;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op18(){
	x = -97.233;
	y = -237.593;
	z = 173.791;
	Rx = -8.498;
	Ry = -133.105;
	Rz = 118.677;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op19(){
	x = -133.167;
	y = -240.572;
	z = 53.612;
	Rx = -36.562;
	Ry = -105.609;
	Rz = 110.501;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::op20(){
	x = -3.051;
	y = -392.193;
	z = 152.287;
	Rx = -171.466;
	Ry = 9.433;
	Rz = -4.174;
	a = 0.5;
	v = 0.5;
	Produce();
	send(sClient, instruct.c_str(), strlen(instruct.c_str()), 0);
	Sleep(STOPTIME);
}

void Robot::OPP1(){
	setEngine.send_open();
	op();
	op1();
	setEngine.send_close();
	Sleep(STOPTIME);
	op();
	op9();
	op10();
	setEngine.send_open();
	op9();
	op11();
	setEngine.send_close();
	Sleep(STOPTIME);
	op12();
	op9();
	op13();
	op14();
	setEngine.send_open();
	op();
}

void Robot::OPP2(){
	setEngine.send_open();
	op();
	op1();
	setEngine.send_close();
	Sleep(STOPTIME);
	op();
	op9();
	op10();
	setEngine.send_open();
	op9();
	op();
	op15();
	op16();
	op18();
	op17();
	setEngine.send_close();
	Sleep(STOPTIME);
	op19();
	op18();
	setEngine.send_close();
	Sleep(STOPTIME);
	op16();
	op();
	Sleep(STOPTIME);
	op20();
	setEngine.send_open();
	Sleep(STOPTIME);
	op();
}

//顶层逆旋转
void Robot::UpAnti_Clockwise(){
	op();
	op1();
	setEngine.send_close();
	Sleep(STOPTIME);
	op2();
	setEngine.send_open();
	Sleep(STOPTIME);
	op();
}

void Robot::UpClockwise(){
	op();
	op1();
	setEngine.send_close();
	Sleep(STOPTIME);
	op3();
	setEngine.send_open();
	Sleep(STOPTIME);
	op();
}

void Robot::RightAnti_Clockwise(){
	OPP1();
	UpAnti_Clockwise();
	OPP1();
	OPP1();
	OPP1();
}

void Robot::RingtClockwise(){
	OPP1();
	UpClockwise();
	OPP1();
	OPP1();
	OPP1();
}

void Robot::LeftAnti_Clockwise(){
	OPP1();
	OPP1();
	OPP1();
	UpAnti_Clockwise();
	OPP1();
}

void Robot::LeftClockwise(){
	OPP1();
	OPP1();
	OPP1();
	UpClockwise();
	OPP1();
}

void Robot::DownAnti_Clockwise(){
	OPP1();
	OPP1();
	UpClockwise();
	OPP1();
	OPP1();
}

void Robot::DownClockwise(){
	OPP1();
	OPP1();
	UpAnti_Clockwise();
	OPP1();
	OPP1();
}

void Robot::FrontAnti_Clockwise(){
	OPP2();
	UpClockwise();
	OPP2();
	OPP2();
	OPP2();
}

void Robot::FrontClockwise(){
	OPP2();
	UpAnti_Clockwise();
	OPP2();
	OPP2();
	OPP2();
}

void Robot::BackAnti_Clockwise(){
	OPP2();
	OPP2();
	OPP2();
	UpClockwise();
	OPP2();
}

void Robot::BackClockwise(){
	OPP2();
	OPP2();
	OPP2();
	UpAnti_Clockwise();
	OPP2();
}