#include "minishell.h"

int main(int argc, char **argv)
{
	char	*pos;
	char	*t = "*1echo \'abc \" --  || \"|\'*|*2*|*3 \" \' ls\' \"> f1 \"|\"4pwd *|*5 \" ${USER}\" << 345 *|1|7"; // 
	char	c = '|';
	char	**cmdset_array = NULL;
	char	**tokens = NULL;
	int		i, j;
	t_cmd cmd;

	cmd.here_stop = NULL;
	pos = ft_get_spec_char(t, c, ESC_SL_DQ_SQ);
	cmdset_array = ft_get_cmd_set_m(t, c);
	i = 0;
	if (cmdset_array)
	{
		while(cmdset_array[i])
		{
			printf("%s\n", cmdset_array[i]);
			tokens = ft_get_tokens(cmdset_array[i]);
			j = 0;
			if (tokens)
			{
				while(tokens[j])
				{
					if (tokens[j][0])
					{
						printf("t:\n");
						printf("%s\n", tokens[j]);
					}
					ft_get_redirections(tokens[j], &cmd);
					free(tokens[j]);
					j++;
				}
				free(tokens);
			}
			printf("cmdset end\n");
			i++;
		}
	}
	i = 0;
	if (cmdset_array)
	{
		i = 0;
		while(cmdset_array[i])
		{
			free(cmdset_array[i]);
			i++;
		}
		free(cmdset_array);
	}
	return (0);
}