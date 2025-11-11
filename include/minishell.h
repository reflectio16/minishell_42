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
    T_WORD,         // Strings, posibly quoted
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

typedef struct s_redir
{
    int             type;       // REDIR_IN, REDIR_OUT, APPEND, HEREDOC
    char            *filename;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **argv;     // e.g. ["ls", "-l", NULL]
    t_redir         *redirs;    // linked list of redirections
    struct s_cmd    *next;      // next command in pipeline
}   t_cmd;



/* lexer.c */
t_token	*lexer(char *input);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);

/* utils */
t_token	*new_token(char *val, t_token_type type);
void	add_token(t_token **lst, t_token *new);

/* parcer.c */
t_cmd	*parse_tokens(t_token *tokens);

/* parse_input.c */
void	handle_word_token(t_cmd *cmd, t_token *token);
void	handle_redir_token(t_cmd *cmd, t_token **token);
void	handle_pipe_token(t_cmd **current);
void	init_cmd(t_cmd **cmd_head, t_cmd **current);







# endif
