#include "../include/minishell.h"

volatile sig_atomic_t g_signal = 0;
t_shell *g_shell = NULL;

void handle_sigint(int signo)
{
    g_signal = signo;
    write(STDOUT_FILENO, "\n", 1);
}
