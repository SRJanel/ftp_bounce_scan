/*
** build_cmd.c for build_cmd
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sun Dec  3 00:58:47 2017 
** Last update Sun Dec  3 21:30:57 2017 
*/

#include <stdio.h>
#include <stdlib.h>
#include "ftp_bounce.h"

ALWAYS_INLINE void	build_cmd_list(char **ptr)
{
  *ptr = NULL;
  concat_strings(ptr, "list");
  concat_strings(ptr, "\r\n");
}

void	build_cmd_port(char **ptr, size_t port)
{
  char	port_tmp[9];

  snprintf(port_tmp, 8, ",%ld,%ld", port / 256, port % 256);
  concat_strings(ptr, port_tmp);
  concat_strings(ptr, "\r\n");
}
