#include "error.h"

void	error_msg(const char *filename, const char *msg)
{
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(filename, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(": error: ", 2);
	ft_putendl_fd(msg, 2);
}