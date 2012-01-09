#ifndef    RECEIVE_HPP
#define    RECEIVE_HPP

#ifdef __linux__
#include <netinet/in.h>
#else
#include <winsock2.h>
#endif		/* __linux__ */

struct		receive
{
  struct sockaddr_in s_rcv;
  char        *data_;
};

#endif		/* RECEIVE_HPP */
