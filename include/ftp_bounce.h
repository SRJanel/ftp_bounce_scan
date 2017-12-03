/*
** ftp_bounce.h for FTP_BOUNCE_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Fri Nov 10 18:02:46 2017 
** Last update Sun Dec  3 23:33:45 2017 
*/

#ifndef FTP_BOUNCE_H_
# define FTP_BOUNCE_H_

# include <stdio.h>
# include <netdb.h>

# define ALWAYS_INLINE			__attribute__((always_inline)) __inline__
# define PRINT_ERROR(MESG)		fprintf(stderr, "%s (%s:%s:%d): %s\n", MESG, \
						__extension__ __FILE__, __FUNCTION__, __LINE__, \
						strerror(errno))
# define MAX_PORT			65535
# define BUF_SIZE			256

# define CR				"\r"
# define LF				"\n"
# define ADD_LF(MESG)			MESG LF
# define ADD_CRLF(MESG)			MESG CR LF

char					*replace_dots_with_comas(char *);
char					write_next_cmd(int, const char *);
void					concat_strings(char **, const char *);
char					read_test_next_value(int, char *, char *);
char					test_server_response(const char *, const char *);
char					resolve_hostname(const char *, const char *,
							 struct addrinfo **, char **);
void					build_cmd_list(char **);
void					build_cmd_port(char **, size_t);

#endif /* !FTP_BOUNCE_H_ */
