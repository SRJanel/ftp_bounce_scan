/*
** utils.c for utils
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Fri Dec  1 15:49:49 2017 
** Last update Sun Dec  3 22:11:26 2017 
*/

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "options.h"

char			resolve_hostname(const char *hostname, const char *service,
					 struct addrinfo **addr_info, char **ip)
{
  struct addrinfo	hints;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  return (!(getaddrinfo(hostname, service, &hints, addr_info)
	    || !(*ip = inet_ntoa(((struct sockaddr_in *)(*addr_info)->ai_addr)->sin_addr))));
}
