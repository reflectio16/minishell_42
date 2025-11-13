#include "../include/minishell.h"

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
