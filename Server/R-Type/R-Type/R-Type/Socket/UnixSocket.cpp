#include	"UnixSocket.hpp"

#ifdef		__linux__

UnixSocket::UnixSocket()
{ }

UnixSocket::~UnixSocket()
{ }

bool     UnixSocket::CreateSocket(int domain, int type, int protocol)
{
  if ((socket_ = socket(domain, type, protocol)) < 0)
	return false;
  return true;
}

bool     UnixSocket::BindSocket(int family, int port)
{
  struct sockaddr_in sockad;
  int    len;

   sockad.sin_family = family;
   sockad.sin_port = htons(port);
   sockad.sin_addr.s_addr = htonl(INADDR_ANY);
   len = sizeof(sockaddress);
   if(bind(socket_, (struct sockaddr*)&sockad, len) < 0)
	 return false;
   return true;
}

receive     UnixSocket::RecvData(int len, int flags)
{
  int    check;
  char   *buffer = new char[len];
  struct sockaddr_in addr_;
  int    sizeaddr = sizeof(addr_);
  receive   rcv;

  check = recvfrom(socket_, buffer, len, flags, (struct sockaddr*) &addr_, &sizeaddr);
  buffer[check] = 0;
  rcv.data_ = buffer;
  rcv.s_rcv = addr_;
  return rcv;
}

bool     UnixSocket::SendData(std::string ip, int port, char *buf, int len, int flags)
{
  int    check;
  struct sockaddr_in addr_;

  addr_.sin_family = AF_INET;
  addr_.sin_addr.s_addr = inet_addr(ip.c_str());
  addr_.sin_port = htons(port);
  check = sendto(socket_, buf, len, flags, (struct sockaddr*) &addr_, sizeof(addr_));
  if (check == SOCKET_ERROR)
	return false;
  return true;
}

#endif		/* __linux__ */