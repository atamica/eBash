#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	// init
	// tst args ?
	// input
	// parce
	// execute
	// tst status
	// free
	// exit(status)

	char* input, shell_prompt[100], dir[4096];
	int	status = 1;
    while (status)
    {
        // getting the current user's path

        printf("%s: ", getcwd(dir, 4096));
        // inputing...
        input = readline(shell_prompt);
        // eof
        if (!input)
		{
			status = 0;
			break ;
		}
            
		// path autocompletion when tabulation hit
        // rl_bind_key('\t', rl_complete);
        // adding the previous input into history
        add_history(input);

        /* do stuff */
printf("start > ac=%i av=%p env=%p (%s)\n", ac, (void *)av, (void *)env, input);
        // Т. к. вызов readline() выделяет память, но не освобождает (а возвращает), то эту память нужно вернуть (освободить).
        free(input);
	}
	return (0);
}
