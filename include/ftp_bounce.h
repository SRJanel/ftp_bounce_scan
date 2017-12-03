/*
** ftp_bounce.h for FTP_BOUNCE_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Fri Nov 10 18:02:46 2017 
** Last update Sun Dec  3 21:19:30 2017 
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
# define MESSAGE_FTP_UNVULN_1024	ADD_LF("[-] Proxy server cannot scan ports below 1024.")
# define MESSAGE_FTP_TRY_1024_UP	ADD_LF("[*] Trying to scan ports from 1024 and upwards.")
# define MESSAGE_FTP_NOT_VULN		ADD_LF("[-] Proxy server does not seem to be vulnerable")
# define FTP_CODE_150			"150"
# define FTP_CODE_200			"200"
# define FTP_CODE_220			"220"
# define FTP_CODE_226			"226"
# define FTP_CODE_425			"425"
# define FTP_CODE_331			"331"
# define FTP_CODE_230			"230"
# define FTP_CODE_500			"500"

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
