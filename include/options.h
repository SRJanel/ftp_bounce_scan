/*
** options.h for OPTIONS_H_
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sat Oct 14 21:57:19 2017 
** Last update Tue Dec  5 16:02:26 2017 
*/

#ifndef OPTIONS_H_
# define OPTIONS_H_

# define OPTIONS_WITH_ARG_TABLE						\
  ENTRY(ftp, required_argument, 'f')					\
  ENTRY(username, required_argument, 'u')				\
  ENTRY(password, optional_argument, 'p')				\
  ENTRY(target, required_argument, 't')

# define OPTIONS_WITHOUT_ARG_TABLE		\
  ENTRY(help, 'h')

# define OPTSTRING	"t:f:u:p:h"

/*
** ________________________________________________
** ------------------------------------------------
*/
# define STRINGIFY(x) #x
# define MAKE_STRING(x) STRINGIFY(x)

struct s_options {
# define ENTRY(FIELD, UNUSED1, UNUSED2) char *FIELD;
  OPTIONS_WITH_ARG_TABLE
# undef ENTRY
# define ENTRY(FIELD, UNUSED1) int FIELD;
  OPTIONS_WITHOUT_ARG_TABLE
# undef ENTRY
}	get_args(int argc, char **argv);

#endif /* !OPTIONS_H_ */
