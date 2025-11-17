#include "../include/minishell.h"

volatile sig_atomic_t g_signal = 0;
int g_exit_status = 0;

void handle_sigint(int signo)
{
    g_signal = signo;
    write(1, "\nminishell> ", 13);
}
