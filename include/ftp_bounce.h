/*
** ftp_bounce.h for FTP_BOUNCE_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Fri Nov 10 18:02:46 2017 
** Last update Fri Nov 10 18:17:12 2017 
*/

#ifndef FTP_BOUNCE_H_
# define FTP_BOUNCE_H_

# include <stdio.h>

# define PRINT_ERROR(MESG)	fprintf(stderr, "%s (%s:%s:%d): %s\n", MESG, \
					__extension__ __FILE__, __FUNCTION__, __LINE__, \
					strerror(errno))
# define MAX_PORT		65535

char				*replace_dots_with_comas(char *);
char				write_next_cmd(int, const char *);
void				concat_strings(char **, const char *);
char				read_test_next_value(int, char *, char *);

#endif /* !FTP_BOUNCE_H_ */
