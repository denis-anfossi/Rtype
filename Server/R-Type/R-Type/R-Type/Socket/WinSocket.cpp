#include "WinSocket.hpp"

#ifdef __linux__
#else

WinSocket::WinSocket()
{ }

WinSocket::~WinSocket()
{ }

bool     WinSocket::CreateSocket(int domain, int type, int protocol)
{
  WSADATA wsaData = {0};
  int iResult = 0;
  
  socket_ = INVALID_SOCKET;
  iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != 0)
 	return false;
  socket_ = WSASocket(domain, type, protocol, NULL, 0, WSA_FLAG_OVERLAPPED);
  if (socket_ == INVALID_SOCKET) 
	return false;
  return true;
}

bool     WinSocket::BindSocket(int family, int port)
{
  struct sockaddr_in sockaddress;
  int    len;
   sockaddress.sin_family = family;
   sockaddress.sin_port = htons(port);
   sockaddress.sin_addr.s_addr = htonl(INADDR_ANY);
   len = sizeof(sockaddress);
   if (bind(socket_, (struct sockaddr*)&sockaddress, len) < 0)
	 return false;
   return true;
}

receive     WinSocket::RecvData(int len, int flags)
{
	receive   rcv;
	if (len > 0)
	{
//		std::cout << len << std::endl;
		char   *buffer = new char[len + 1];
		struct sockaddr_in addr_;
		int    sizeaddr = sizeof(addr_);

		int check = recvfrom(socket_, buffer, len, flags, (struct sockaddr*) &addr_, &sizeaddr);
		//std::cout << "check = " << check  << std::endl;
		if (flags != MSG_PEEK)
		{	
//		std::cout << "check = " << check  << std::endl;
		//
		rcv.data_ = NULL;
		}
		if (flags == MSG_PEEK && check == -1)
		{
//		std::cout << "  - - - -    MSG_PEEK LE PD   - - - - " << check << std::endl;
		//rcv = NULL;
		//return rcv;
		}
//		if (flags == MSG_PEEK)
//		std::cout << " +++++ MSG_PEEK LE PD   +++++ " << check << std::endl;
		buffer[check] = 0;
		rcv.data_ = buffer;
		rcv.s_rcv = addr_;
//		if (check == -1)
//		std::cout << "FAUT VIRER" << std::endl;
  }
  else
  {
	rcv.data_ = NULL;
  }
  return rcv;
}

bool     WinSocket::SendData(in_addr ip, int port, char *buf, int len, int flags)
{
  int    check;
  struct sockaddr_in addr_;

  addr_.sin_family = AF_INET;
  addr_.sin_addr = ip;
  addr_.sin_port = port;
  check = sendto(socket_, buf, len, flags, (struct sockaddr*) &addr_, sizeof(addr_));
  if (check == SOCKET_ERROR)
	return false;
  return true;
}

#endif