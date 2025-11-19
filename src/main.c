#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_shell sh;
    char    *input;
    t_token *tokens;
    t_cmd   *cmds;
    t_cmd   *tmp;

    (void)argc;
    (void)argv;

    // Initialize shell struct with environment
    if (init_shell(&sh, envp) < 0)
    {
        perror("init_shell");
        return 1;
    }
    while (1)
    {
        // Set signal handlers
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, SIG_IGN);
        g_signal = 0;

        input = readline("minishell> ");
        if (!input)
            break ; // EOF (Ctrl+D)
        // Ctrl+C pressed
        if (g_signal == SIGINT)
        {
            sh.last_status = 130;
            free(input);
            continue ;
        }
        if (*input)
            add_history(input);
        // Tokenize input
        tokens = NULL;
        if (!lexer(&tokens, input))
        {
            fprintf(stderr, "Error: memory allocation failed in lexer\n");
            free(input);
            continue ;
        }
        // Debug: print tokens
        // print_tokens(tokens);

        cmds = parse_tokens(tokens);
        free_tokens(tokens);
        if (!cmds)
        {
            fprintf(stderr, "Error: failed to parse tokens\n");
            free(input);
            continue ;
        }
        // Debug: print commands
        // print_commands(cmds);
        tmp = cmds;
        while (tmp)
        {
            expand_variables(tmp, &sh);
            tmp = tmp->next;
        }
        // Execute pipeline (handles parent/child builtins)
        execute_pipeline(cmds, &sh);
        free_tokens(tokens);
        free_cmds(cmds);
        free(input);
    }
    rl_clear_history();
    free_shell(&sh);
    return (sh.last_status);
}
