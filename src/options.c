/*
** options.c for options
** 
** Made by SRJanel
** Login SRJanel <n******.******s@epitech.eu>
** 
** Started on  Sat Oct 14 21:53:05 2017 
** Last update Mon Dec  4 18:21:51 2017 
*/

#include <unistd.h>
#include <getopt.h>
#include "options.h"

struct s_options			get_args(int argc, char **argv)
  {
    int					c;
    int					index;
    struct s_options			options = {0};
    static struct option			long_options[] =
      {
# define ENTRY(FIELD, REQ, SHORTARG) {MAKE_STRING(FIELD), REQ, NULL, SHORTARG},
	OPTIONS_WITH_ARG_TABLE
# undef ENTRY
# define ENTRY(FIELD, SHORTARG) {MAKE_STRING(FIELD), no_argument, NULL, 1},
	OPTIONS_WITHOUT_ARG_TABLE
# undef ENTRY
	{NULL, 0, NULL, 0}
      };

    while (1)
      {
	if ((c = getopt_long(argc, argv,
			     OPTSTRING,
			     long_options, &index)) == -1)
	  break ;

	if (optarg && *optarg == '-') continue ;
# define ENTRY(FIELD, UNUSED1, SHORTARG) else if (c == SHORTARG && !options.FIELD) \
	  options.FIELD = optarg;
	OPTIONS_WITH_ARG_TABLE
#undef ENTRY
# define ENTRY(FIELD, SHORTARG) else if (c == SHORTARG) options.FIELD = 1;
	  OPTIONS_WITHOUT_ARG_TABLE
#undef ENTRY
	else if (c == '?')
	  options.help = 1;
      }
    return (options);
}
