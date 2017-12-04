/*
** ftp_bounce.h for FTP_BOUNCE_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Fri Nov 10 18:02:46 2017 
** Last update Mon Dec  4 18:32:05 2017 
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

/*
** src/utils.c
*/
char					test_server_response(const char *, const char *);
char					read_test_next_value(int, char *, char *);
char					write_next_cmd(int, const char *);
char					*replace_dots_with_comas(char *);
void					concat_strings(char **, const char *);

/*
** src/network/utils.c
*/
char					resolve_hostname(const char *, const char *,
							 struct addrinfo **, char **);

/*
** src/build_cmd.c
*/
void					build_cmd_list(char **);
void					build_cmd_port(char **, size_t);

/*
** src/ftp_scan.c
*/
char					authentication(int, char *,
						       const char *, const char *);
char					port_scan(int, char *);

#endif /* !FTP_BOUNCE_H_ */
