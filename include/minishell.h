/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 13:41:06 by meelma            #+#    #+#             */
/*   Updated: 2025/11/10 13:43:24 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../Libft/libft.h"
# include "../Libft/get_next_line.h"


typedef enum e_token_type
{
    T_WORD,         // Strings, posibly quoted)
    T_PIPE,         // |
    T_REDIR_IN,     // <
    T_REDIR_OUT,    // >
    T_APPEND,       // >>
    T_HEREDOC       // <<
}   t_token_type;

typedef struct s_token
{
    char            *value;     // The actual token string
    t_token_type    type;       // What kind of token this is (likely an enum)
    struct s_token  *next;      // Pointer to the next token in the list
}   t_token;

typedef struct s_cmd
{
    char            **argv;     // ["echo", "hello"]
    char            *infile;    // "<" or "<<"
    char            *outfile;   // ">" or ">>"
    int             append;     // 1 if >>
    int             heredoc;    // 1 if <<
    struct s_cmd    *next;      // for pipes
}   t_cmd;

/* lexer.c */
t_token	*lexer(char *input);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);

/* utils */
t_token	*new_token(char *val, t_token_type type);
void	add_token(t_token **lst, t_token *new);









# endif
