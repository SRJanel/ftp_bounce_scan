/*
** build_cmd.c for build_cmd
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sun Dec  3 00:58:47 2017 
** Last update Sun Dec  3 01:55:50 2017 
*/

#include <stdio.h>
#include <stdlib.h>
#include "ftp_bounce.h"

void	build_cmd_list(char **ptr)
{
  *ptr = NULL;
  concat_strings(ptr, "list");
  concat_strings(ptr, "\r\n");
}

void	build_cmd_port(char **ptr, size_t port)
{
  char	port_tmp[4];

  snprintf(port_tmp, 4, ",%ld", port / 256);
  concat_strings(ptr, port_tmp);
  snprintf(port_tmp, 4, ",%ld", port % 256);
  concat_strings(ptr, port_tmp);
  concat_strings(ptr, "\r\n");
}
