#include "minishell.h"

int main(int argc, char **argv)
{
	char	*pos;
	//char	*t = "echo \'abc \" --   \"\'  ls > f1"; // ls ">'>'>" '>">>"' f2
	char	*t = "echo \'abc \" --   \"\'|  ls > f1 |pwd"; // 
	char	c = '|';
	char	**cmdset_array = NULL;
	int		i;

	pos = ft_get_spec_ch(t, c);
	if (pos)
		printf("%s\n", pos);
	return (0);
}