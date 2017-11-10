/*
** options.h for OPTIONS_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sat Oct 14 21:57:19 2017 
** Last update Fri Nov 10 19:10:47 2017 
*/

#ifndef OPTIONS_H_
# define OPTIONS_H_

extern struct s_options {
  int	help;
  char	*ftp;
  char	*username;
  char	*password;
  char	*target;
}	get_args(int argc, char **argv);

#endif /* !OPTIONS_H_ */
