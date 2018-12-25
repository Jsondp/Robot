#pragma once
class CEthernet
{
public:
	CEthernet();
	~CEthernet();

	bool Client_Connect(char* szIP, int nPort, bool bConnect);//连接断开服务器
	int Client_Send(char* data, int nLen);//想服务器发送数据
	int Client_Recv(char* data, int nLen, int nTimeout);//接收从服务器发来的数据
private:
	SOCKET m_Client;
};

