/*
** messages.h for MESSAGES_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sun Dec  3 21:56:25 2017 
** Last update Sun Dec  3 23:35:14 2017 
*/

#ifndef MESSAGES_H_
# define MESSAGES_H_

# define MSG_FTP_UNVULN_1024	"[-] Proxy server cannot scan ports below 1024.\n"
# define MSG_FTP_TRY_1024_UP	"[*] Trying to scan ports from 1024 and upwards.\n"
# define MSG_FTP_NOT_VULN	"[-] Proxy server does not seem to be vulnerable\n"
# define MSG_CONN_PROXY		"[+] Successfully authenticated to FTP (proxy) server:\n"
# define MSG_SCAN_BEGIN		"[+] Begin scan\n"
# define MSG_SCAN_END		"[+] Scan finished\n"
# define MSG_PORT_OPEN		"[+] PORT: %ld open\n"
# define ERR_CONN_PROXY		"[-] Could not connect to FTP (proxy) server\n"
# define ERR_RSLV_PROXY		"[-] Could not resolve proxy IP\n"
# define ERR_RSLV_TARGET	"[-] Could not resolve target IP\n"
# define ERR_SCAN		"[-] Could not scan\n"

/*
** FTP CODES
*/
# define FTP_CODE_150			"150"
# define FTP_CODE_200			"200"
# define FTP_CODE_220			"220"
# define FTP_CODE_226			"226"
# define FTP_CODE_425			"425"
# define FTP_CODE_331			"331"
# define FTP_CODE_230			"230"
# define FTP_CODE_500			"500"

#endif /* !MESSAGES_H_ */
