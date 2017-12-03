/*
** messages.h for MESSAGES_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sun Dec  3 21:56:25 2017 
** Last update Sun Dec  3 22:10:32 2017 
*/

#ifndef MESSAGES_H_
# define MESSAGES_H_

# define MSG_CONN_PROXY		"[+] Successfully authenticated to FTP (proxy) server:\n"
# define MSG_SCAN_BEGIN		"[+] Begin scan\n"
# define MSG_SCAN_END		"[+] Scan finished\n"
# define MSG_PORT_OPEN		"[+] PORT: %ld open\n"
# define ERR_CONN_PROXY		"[-] Could not connect to FTP (proxy) server\n"
# define ERR_RESOLV_PROXY	"[-] Could not resolve proxy IP\n"
# define ERR_RESOLV_TARGET	"[-] Could not resolve target IP\n"
# define ERR_SCAN		"[-] Could not scan\n"

#endif /* !MESSAGES_H_ */
