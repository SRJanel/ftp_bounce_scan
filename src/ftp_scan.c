/*
** ftp_scan.c for ftp_scan
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Mon Dec  4 18:23:29 2017 
** Last update Mon Dec  4 18:28:17 2017 
*/

#include <stdlib.h>
#include <string.h>
#include "ftp_bounce.h"
#include "messages.h"

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

static char	security_checks(size_t *port, char *cmd_recv)
{
  char		ret;

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
#ifdef _SECURE_RUN
  port = 1024;
#endif /* !_SECURE_RUN */
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
