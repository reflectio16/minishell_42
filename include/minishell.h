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
bool    lexer(t_token **tokens, char *input);
char    *extract_word(const char *input, int *i);
bool    add_special_token(t_token **tokens, const char *input, int *i);

/* utils */
t_token *new_token(char *value, t_token_type type);
void	add_token(t_token **lst, t_token *new);
void    free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmd);
int     is_special_char(char c);
int     is_space(char c);
char    *remove_quotes(char *str);
bool    add_word_token(t_token **tokens, const char *input, int *i);
bool    append_token(t_token **tokens, char *value, t_token_type type);
void	print_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);
t_cmd   *new_cmd(void);
void    add_arg(t_cmd *cmd, char *arg);
void    add_redir(t_cmd *cmd, t_token_type type, char *file);
int     is_builtin(char *cmd);
int     builtin_is_parent(char *cmd_name);
int     exec_builtin_child(t_cmd *cmd);

/* Errors*/
void	error(char *msg);

/* parcer.c */
t_cmd	*parse_tokens(t_token *tokens);

/* parse_input.c */
void	handle_word_token(t_cmd *cmd, t_token *token);
void	handle_redir_token(t_cmd *cmd, t_token **token);
void	handle_pipe_token(t_cmd **current);
void	init_cmd(t_cmd **cmd_head, t_cmd **current);

/* Execution */
void    execute_pipeline(t_cmd *cmds, char **envp);
int     apply_redirections(t_cmd *cmd);
void	execute_command(t_cmd *cmd, char **envp, int *prev_fd);
int     open_heredoc(t_redir *r);

/* Built-in */
void    echo_print_args(char **argv, int i);
int     builtin_echo(char **argv);

/* debug */
void    print_redirs(t_redir *r);
void    print_commands(t_cmd *cmd);





# endif
