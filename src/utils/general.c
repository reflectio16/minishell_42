#include "../include/minishell.h"

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}
