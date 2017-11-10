/*
** main.c for main
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Mon Nov  6 11:28:04 2017 
** Last update Fri Nov 10 19:28:19 2017 
*/

# define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include "ftp_bounce.h"
#include "options.h"

# define BUF_SIZE 256

char	authentication(int sd, char *buffer,
		       const char *username, const char *password)
{
  char	*cmd;

  cmd = NULL;
  concat_strings(&cmd, "user ");
  concat_strings(&cmd, username);
  concat_strings(&cmd, "\r\n");
  if (write_next_cmd(sd, cmd) == -1
      || read_test_next_value(sd, buffer, "331") <= 0)
    return (0);

  cmd = NULL;
  concat_strings(&cmd, "pass ");
  concat_strings(&cmd, password);
  concat_strings(&cmd, "\r\n");
  if (write_next_cmd(sd, cmd) == -1
      || read_test_next_value(sd, buffer, "230") <= 0)
    return (0);
  return (1);
}

char		port_scan(int sd, char *cmd_port_ip)
{
  size_t	port;
  char		general_buffer[BUF_SIZE] = {0};
  char		*commands;
  size_t	buf_end;
    
  port = 1023;
  while (++port <= MAX_PORT)
    {
      snprintf(general_buffer, strlen(cmd_port_ip) + 8, "%s,%ld,%ld", cmd_port_ip, port / 256, port % 256);
      buf_end = strlen(general_buffer);
      general_buffer[buf_end] = '\r';
      general_buffer[buf_end + 1] = '\n';
      general_buffer[buf_end + 2] = 0;      
      if (write_next_cmd(sd, general_buffer) == -1
	  || read_test_next_value(sd, general_buffer, "200") <= 0)
  	return (0);
      commands = NULL;
      concat_strings(&commands, "list");
      concat_strings(&commands, "\r\n");
      if (write_next_cmd(sd, commands) == -1)
  	return (0);
      if (read_test_next_value(sd, general_buffer, "150") > 0
	  && read_test_next_value(sd, general_buffer, "226") > 0)
	fprintf(stdout, "[+] Port: %ld open\n", port);
      /* if (strncmp(general_buffer, "425", 3) && port < 1024) */
      /* 	fprintf(stdout, "Try higher ports\n"); */
      free(commands);
    }
  return (1);
}

int			main(int argc, char *argv[])
{
  int			sd;
  struct addrinfo	ftp_serv, *res;
  char			buffer[BUF_SIZE] = {0};
  char			*cmd_port_ip;
  char			*commands;
  struct s_options	options;

  options = get_args(argc, argv);

  fprintf(stdout, "options.help: %d\n", options.help);
  fprintf(stdout, "PROXY: %s\n", options.ftp);
  fprintf(stdout, "username: %s\n", options.username);
  fprintf(stdout, "password: %s\n", options.password);
  fprintf(stdout, "TARGET: %s\n", options.target);

  return (0);

  memset(&ftp_serv, 0, sizeof ftp_serv);
  ftp_serv.ai_family = AF_UNSPEC;
  ftp_serv.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(options.ftp, "ftp", &ftp_serv, &res)
      || (sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1
      || connect(sd, res->ai_addr, res->ai_addrlen))
    return (PRINT_ERROR(""), EXIT_FAILURE);

  if (read_test_next_value(sd, buffer, "220") <= 0)
    return (EXIT_FAILURE);

  if (!authentication(sd, buffer, options.username, options.password))
    return (EXIT_FAILURE);
  fprintf(stderr, "[+] Successfully authenticated to ftp \"proxy\" server\n");

  commands = NULL;
  concat_strings(&commands, "PORT ");
  concat_strings(&commands, replace_dots_with_comas(options.target));
  cmd_port_ip = strdup(commands);

  if (!port_scan(sd, cmd_port_ip))
    return (PRINT_ERROR("Could not scan"), EXIT_FAILURE);

  free(cmd_port_ip);
  free(commands);
  fprintf(stdout, "[+] Scan finished\n");
  return (EXIT_SUCCESS);
  /* (void)options; */
}

# undef BUF_SIZE
