#pragma once
class CEthernet
{
public:
	CEthernet();
	~CEthernet();

	bool Client_Connect(char* szIP, int nPort, bool bConnect);//���ӶϿ�������
	int Client_Send(char* data, int nLen);//���������������
	int Client_Recv(char* data, int nLen, int nTimeout);//���մӷ���������������
private:
	SOCKET m_Client;
};

