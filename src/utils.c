/*
** utils.c for utils
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Fri Nov 10 18:03:39 2017 
** Last update Sun Dec  3 02:10:59 2017 
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "ftp_bounce.h"

__attribute__((always_inline)) __inline__ char	test_server_response(const char *response, const char *exp)
{
  return (!strncmp(exp, response, 3));
}

char		read_test_next_value(int sd, char *buffer, char *exp)
{
  memset(buffer, 0, BUF_SIZE);
  if (read(sd, buffer, BUF_SIZE - 1) <= 0)
    return (-1);
  return (test_server_response(buffer, exp));
}

__attribute__((always_inline)) __inline__ char	write_next_cmd(int sd, const char *cmd)
{
  return (write(sd, cmd, strlen(cmd)));
}

char		*replace_dots_with_comas(char *ptr)
{
  ssize_t	i;
  
  i = -1;
  if (ptr)
    while (ptr[++i])
      if (ptr[i] == '.')
	ptr[i] = ',';
  return (ptr);
}

void	concat_strings(char **str1, const char *str2)
{
  if (!str2)
    return;
  if (!*str1)
    {
      if (!(*str1 = malloc(sizeof(char))))
        return;
      **str1 = 0;
    }
  if ((*str1 = realloc(*str1, strlen(*str1) + strlen(str2) + 1)))
    *str1 = strncat(*str1, str2, strlen(str2));
}
