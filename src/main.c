/*
** main.c for main
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Mon Nov  6 11:28:04 2017 
** Last update Mon Dec  4 18:28:37 2017 
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "ftp_bounce.h"
#include "options.h"
#include "messages.h"

static void	usage(const char *prog_name)
{
  fprintf(stderr, "USAGE: %s -f ftp_server -u username -p password -t target_server\n" \
	  "\t-f, --ftp\t\tftp \"proxy\" server to connect to\n"
	  "\t-u, --username\t\tUsername for ftp \"proxy\" server\n"
	  "\t-p, --password\t\tPassword for ftp \"proxy\" server\n"
	  "\t-t, --target\t\tTarget to scan\n",
	  prog_name);
}

int			main(int argc, char *argv[])
{
  int			sd;
  struct addrinfo	*result;
  struct s_options	options;
  char			buffer[BUF_SIZE] = {0};
  char			*target;

  options = get_args(argc, argv);
  if (options.help
      || !options.ftp || !options.username || !options.target)
    return (usage(argv[0]), EXIT_FAILURE);
  if (!(resolve_hostname(options.ftp, "ftp", &result, &target)))
    return (PRINT_ERROR(ERR_RSLV_PROXY), EXIT_FAILURE);  
  if ((sd = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1
      || connect(sd, result->ai_addr, result->ai_addrlen))
    return (fprintf(stderr, ERR_CONN_PROXY), EXIT_FAILURE);
  if (!authentication(sd, buffer, options.username, options.password))
    return (fprintf(stderr, "ERROR: %s", buffer), EXIT_FAILURE);
  fprintf(stdout, MSG_CONN_PROXY " '%s'\n", options.ftp);
  freeaddrinfo(result);
  if (!(resolve_hostname(options.target, NULL, &result, &target)))
    return (PRINT_ERROR(ERR_RSLV_TARGET), EXIT_FAILURE);  
  fprintf(stdout, MSG_SCAN_BEGIN);
  if (!port_scan(sd, target))
    return (PRINT_ERROR(ERR_SCAN), EXIT_FAILURE);
  fprintf(stdout, MSG_SCAN_END);
  freeaddrinfo(result);
  return (EXIT_SUCCESS);
}
