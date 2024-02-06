#include "minirt.h"

/**
 * @brief displays input string followed by a new line to
 * standard error
 * @param str string to be displayed (without \\n)
 * @return KO
*/
t_ok	err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (KO);
}

/**
 * @brief displays input string followed by a new line to
 * standard output
 * @param str string to be displayed (without \\n)
 * @return OK
*/
t_ok	msg(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (OK);
}
