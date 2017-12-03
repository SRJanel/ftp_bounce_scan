/*
** main.c for main
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Mon Nov  6 11:28:04 2017 
** Last update Sun Dec  3 23:36:07 2017 
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

char	authentication(int sd, char *buffer,
		       const char *username, const char *password)
{
  char	*cmd;
  char	ret;

  if (read_test_next_value(sd, buffer, FTP_CODE_220) <= 0)
    return (0);
  cmd = NULL;
  ret = 1;
  asprintf(&cmd, ADD_CRLF("user %s"), username);
  if (write_next_cmd(sd, cmd) == -1
      || read_test_next_value(sd, buffer, FTP_CODE_331) <= 0)
    return (!ret);
  free(cmd);
  asprintf(&cmd, ADD_CRLF("pass %s"), password);
  if ((write_next_cmd(sd, cmd) == -1
       || read_test_next_value(sd, buffer, FTP_CODE_230) <= 0))
    ret = 0;
  free(cmd);
  return (ret);
}

char	security_checks(size_t *port, char *cmd_recv)
{
  char	ret;

  ret = 0;
  if (*port < 1024 && !strncmp(cmd_recv, FTP_CODE_500, 3))
    {
      fprintf(stderr, MSG_FTP_UNVULN_1024	\
	      MSG_FTP_TRY_1024_UP);
      *port = 1023;
      ret = 1;
    }
  else if (*port >= 1024 && !strncmp(cmd_recv, FTP_CODE_500, 3))
    {
      fprintf(stderr, MSG_FTP_NOT_VULN);
      ret = 2;
    }
  return (ret);

}

#ifdef _SECURE_RUN
# undef MAX_PORT
# define MAX_PORT 1026
#endif /* !_SECURE_RUN */
char		port_scan(int sd, char *target)
{
  size_t	port;
  char		*cmd_send;
  char		cmd_recv[BUF_SIZE] = {0};
  char		sec_check;
  char		*cmd_port_ip = NULL;

  port = 0;
  concat_strings(&cmd_port_ip, "PORT ");
  concat_strings(&cmd_port_ip, replace_dots_with_comas(target));
  while (++port <= MAX_PORT)
    {
      cmd_send = strdup(cmd_port_ip);
      build_cmd_port(&cmd_send, port);
      if (write_next_cmd(sd, cmd_send) == -1
	  || read_test_next_value(sd, cmd_recv, FTP_CODE_200) == -1)
  	return (0);
      if ((sec_check = security_checks(&port, cmd_recv)) == 1)
	continue ;
      else if (sec_check == 2)
	break ;
      free(cmd_send);
      build_cmd_list(&cmd_send);
      if (write_next_cmd(sd, cmd_send) == -1)
  	return (0);
      if (read_test_next_value(sd, cmd_recv, FTP_CODE_150) > 0
	  && read_test_next_value(sd, cmd_recv, FTP_CODE_226) > 0)
	fprintf(stdout, MSG_PORT_OPEN, port);
      free(cmd_send);
    }
  free(cmd_port_ip);
  return (1);
}

int			main(int argc, char *argv[])
{
  int			sd;
  struct addrinfo	*result;
  char			buffer[BUF_SIZE] = {0};
  struct s_options	options;
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
  fprintf(stderr, MSG_CONN_PROXY " '%s'\n", options.ftp);
  freeaddrinfo(result);
  if (!(resolve_hostname(options.target, NULL, &result, &target)))
    return (PRINT_ERROR(ERR_RSLV_TARGET), EXIT_FAILURE);  

  /* fprintf(stdout, "Target: %s\n", target); */
  fprintf(stderr, MSG_SCAN_BEGIN);
  if (!port_scan(sd, target))
    return (PRINT_ERROR(ERR_SCAN), EXIT_FAILURE);
  fprintf(stdout, MSG_SCAN_END);
  freeaddrinfo(result);
  return (EXIT_SUCCESS);
}
