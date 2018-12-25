#include "stdafx.h"
#include "Ethernet.h"


CEthernet::CEthernet()
{
	m_Client = INVALID_SOCKET;

	WORD wVersionRequested;
	WSADATA wasData;//指向WinSocket信息结构的指针
	wVersionRequested = MAKEWORD(2, 2);
	int err;
	err = WSAStartup(wVersionRequested, &wasData);
	if (err != 0)
	{
		return;
	}
	if (LOBYTE(wasData.wVersion) != 2 || HIBYTE(wasData.wVersion) != 2)
	{
		WSACleanup();
		return;
	}
}


CEthernet::~CEthernet()
{
	WSACleanup();
}

bool CEthernet::Client_Connect(char* szIP, int nPort, bool bConnect)
{
	if (bConnect)
	{
		m_Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		struct sockaddr_in serv_addr;

		//以服务器地址填充结构serv_addr
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(szIP);
		serv_addr.sin_port = htons(nPort);
		int error = -1;
		int len = sizeof(int);
		timeval tm;
		fd_set set;
		unsigned long ul = 1;
		ioctlsocket(m_Client, FIONBIO, &ul); //设置为非阻塞模式
		bool ret = false;
		if (connect(m_Client, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		{
			tm.tv_sec = 1;
			tm.tv_usec = 0;
			FD_ZERO(&set);
			FD_SET(m_Client, &set);
			if (select(m_Client + 1, NULL, &set, NULL, &tm) > 0)
			{
				getsockopt(m_Client, SOL_SOCKET, SO_ERROR, (char *)&error, /*(socklen_t *)*/&len);
				if (error == 0)
					ret = true;
				else
					ret = false;
			}
			else
				ret = false;
		}
		else
			ret = true;
		ul = 0;
		ioctlsocket(m_Client, FIONBIO, &ul); //设置为阻塞模式

		return ret;
	}
	else
	{
		closesocket(m_Client);
		m_Client = INVALID_SOCKET;
	}

	return true;
}

int CEthernet::Client_Send(char* data, int nLen)
{
	return send(m_Client, data, nLen, 0);
}

int CEthernet::Client_Recv(char* data, int nLen, int nTimeout)
{
	struct timeval ti;
	ti.tv_sec = nTimeout;
	ti.tv_usec = 0;
	setsockopt(m_Client, SOL_SOCKET, SO_RCVTIMEO, (char *)&ti, sizeof(struct timeval));
	return recv(m_Client, data, nLen, 0);
}