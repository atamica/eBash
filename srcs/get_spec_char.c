#include "minishell.h"

char	*ft_get_spec_ch(char *str, char c)
{
	char *pos;
	int i;
	int j;
	char s_quote;
	char d_quote;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	pos = ft_strchr(str, c);
	if (!pos || (pos == str))
		return (pos);
	i = 0;
	while (str[i])
	{
		while (pos && *pos && *(pos - 1) == '\\')
			pos = ft_strchr(pos + 1, c);
		j = i;
		while (str[j] && str[j] != DQ && str[j] != SQ)
			j++;
		if (str[j] && str[j] == DQ && c != DL)
			d_quote = 1;
		else if (str[j] && str[j] == SQ)
			s_quote = 1;
		if (str[j] && (str + j) > pos)
			return (pos);
		else if (str + j < pos)
		{
			j++;
			if (d_quote)
			{
				while (str[j] && str[j] != DQ)
					j++;
				if (str[j] && (str + j) < pos)
					d_quote = 0;
				else if (str[j])
					pos = ft_strchr(str + j + 1, c);
			}
			else if (s_quote)
			{
				while (str[j] && str[j] != SQ)
					j++;
				if (str[j] && (str + j) < pos)
					s_quote = 0;
				else if (str[j])
					pos = ft_strchr(str + j + 1, c);
			}
		}
		if (str[j])
			i = j + 1;
		else 
			i = j;
	}
	return (pos);
}

char	*ft_get_spec_char(char *str, char c, t_esc_chars escapes)
{
	char *pos;
	int i;
	int j;
	char s_quote;
	char d_quote;

	//pos = NULL;
	if (c == '$')
		escapes = ESC_SQ;
	s_quote = 0;
	d_quote = 0;
	i = 0;
	//printf("%s\n", str);
	pos = ft_strchr(str, c);
	//printf("%p\n", pos);
	//printf("%c\n", *pos);
	if (!pos)
		return (NULL);
	if (pos == str)
		return (pos);
	//else
	//	break;
	i = 0;
	while (str[i])
	{
		if (escapes == ESC_SL_DQ_SQ)
		{
			while (pos && *pos && *(pos - 1) == '\\')
			{
			//if (pos != str && *(pos - 1) == '\\')
				pos = ft_strchr(pos + 1, c);
			}
		}
		j = i;
		while (str[j] && (((escapes == ESC_SL_DQ_SQ || escapes == ESC_DQ_SQ) \
			  && str[j] != '"' && str[j] != '\'') || \
			  ((escapes == ESC_SQ || escapes == ESC_SL_SQ) && str[j] != '\'')))
			j++;
		if (str[j] && str[j] == '"')
			d_quote = 1;
		else if (str[j] && str[j] == '\'')
			s_quote = 1;
		if (str[j] && (str + j) > pos)
		{
			return (pos);
		}
		else if (str + j < pos)
		{	
			j++;
			if (d_quote)
			{
				while (str[j] && str[j] != '"')
					j++;
				if (str[j] && (str + j) < pos)
					d_quote = 0;
				else if (str[j])
					pos = ft_strchr(str + j + 1, c);
			}
			else if (s_quote)
			{
				while (str[j] && str[j] != '\'')
					j++;
				
				if (str[j] && (str + j) < pos)
					s_quote = 0;
				else if (str[j])
				{
					pos = ft_strchr(str + j + 1, c);
				}
			}
		}
		if (str[j])
			i = j + 1;
		else 
			i = j;
	}
	return (pos);
}

void free_mem(char **res, int i, char *strbuf)
{
	free(strbuf);
	while(i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
}

char** ft_get_cmd_set_m(char *str, char c)
{
	int count;
	int i;
	int j;
	char **res;
	char *buf;
	char *strbuf;
	
	res = NULL;
	count = 0;
	i = 0;
	if (!str || !(*str))
		return (NULL);
	strbuf = ft_strdup(str);
	buf = strbuf;
	while (buf)
	{
		count++;
		if (*buf == c)
			*buf = 0;
		buf = ft_get_spec_char(buf + 1, c, ESC_SL_DQ_SQ);
	}
	res = malloc(sizeof(char*) * count + 1);
	if (!res)
		return (NULL);
	i = 0;
	buf = strbuf;
	while (count)
	{	
		res[i] = ft_strdup(buf);
		j = 0;
		while (res[i][j] && res[i][j] == ' ')
		{
			printf("%c\n", res[i][j]);
			j++;
		}
		if (!(res[i][j]) && count != 1)
		{
			free_mem(res, i, strbuf);
			return (NULL);
		}
		buf = buf + ft_strlen(buf) + 1;
		count--;
		i++;
	}
	res[i] = 0;
	free(strbuf);
	return (res);
}

char **ft_mem4tokens(char *str)
{
	int count;
	char **res;

	count = 0;
	while (str)
	{
		count++;
		if (*str == ' ')
			*str = 0;
		str = ft_get_spec_char(str + 1, ' ', ESC_DQ_SQ);
	}
	res = malloc(sizeof(char*) * count + 1);
	if (!res)
		return (NULL);
	return (res);
}

void ft_copy_tokens(char *strbuf, char **res, int count)
{
	int i;

	i = 0;
	while (count)
	{	
		if (*strbuf)
		{
			res[i] = ft_strdup(strbuf);
			i++;
		}
		strbuf = strbuf + ft_strlen(strbuf) + 1;
		count--;
	}
	res[i] = 0;
}

char**	ft_get_tokens(char *str)
{
	int count;
//	int i;
	char **res;
	//char *buf;
	char *strbuf;

	res = NULL;
	count = 0;
//	i = 0;
	if (!str || !(*str))
		return (NULL);
	strbuf = ft_strdup(str);
	//buf = strbuf;
	res = ft_mem4tokens(strbuf);
/* 	while (buf)
	{
		count++;
		if (*buf == ' ')
			*buf = 0;
		buf = ft_get_spec_char(buf + 1, ' ', ESC_DQ_SQ);
	}
	res = malloc(sizeof(char*) * count + 1);
	if (!res)
		return (NULL); */
	ft_copy_tokens(strbuf, res, count);
/* 	i = 0;
	//buf = strbuf;
	while (count)
	{	
		if (*buf)
		{
			res[i] = ft_strdup(buf);
			i++;
		}
		buf = buf + ft_strlen(buf) + 1;
		count--;
	}
	res[i] = 0; */
	free(strbuf);
	return (res);
}

/* t_errors ft_get_redirections(char *str, t_cmd *cmd)
{
	char *pos;
	char *buf;
	char *end;
//	t_errors err_code;
	int i;

	pos = NULL;
	pos = ft_get_spec_ch(str, '>');
	//printf("1*\n");
	if (pos && *(pos + 1) == '>')
	{	
		//printf("2*\n");
		buf = ft_get_spec_ch(pos + 2, '>');
		if (buf && *buf)
			return (ERROR);
		cmd->redir.code_out |= D_RIGHT;
	}
	else if (pos)
	{
		//printf("3*\n");
		buf = ft_get_spec_ch(pos + 1, '>');
		if (buf && *buf)
			return (ERROR);
		cmd->redir.code_out |= S_RIGHT;
	}
	//printf("4*\n");
	pos = ft_get_spec_ch(str, '<');
	if (pos && *(pos + 1) == '<')
	{	
		//printf("5*\n");
		buf = ft_get_spec_ch(pos + 2, '>');
		if (buf && *buf)
			return (ERROR);
		cmd->redir.code_in |= D_LEFT;
		i = 2;
		while (pos[i] && pos[i] == ' ')
			i++;
		end = ft_strchr((pos + i), ' '); //- (pos + i);
		if (!end && pos[i])
			cmd->here_stop = ft_strdup(pos + i);
		else if (pos[i])
		{
			buf = malloc(sizeof(char)*(end - (pos + i)) + 1);
			if (!buf)
				return(ERROR);
			ft_strlcpy(buf, pos + i, (end - (pos + i)));
			cmd->here_stop = buf;
		}
	}
	else if (pos)
	{
		//printf("6*\n");
		buf = ft_get_spec_ch(pos + 1, '>');
		if (buf && *buf)
			return (ERROR);
		cmd->redir.code_in |= S_LEFT;
	}
	return (SUCCSESS);
} */

/* int ft_get_fdes(t_d *d, t_cmd *cmd, char *str, int mode)
{
	int i;
	char *end;
	char *buf;
	char fd;
	int redir;

	i = 0;
	redir = find_redir(str);
	if (redir == ERROR || !redir)
		return(ERROR);
	if (redir & S_LEFT)
	{
		while (str[i] && str[i] != '<')
			i++;
	}
	else if (redir & D_LEFT)
	{
		while (str[i] && str[i] != '<')
			i++;
		i++;
	}
	if (redir & S_RIGHT)
	{
		while (str[i] && str[i] != '>')
			i++;
	}
	else if (redir & D_RIGHT)
	{
		while (str[i] && str[i] != '>')
			i++;
		i++;	
	}
	i++;
	while (str[i] && str[i] == ' ')
		i++;
	end = ft_strchr((str + i), ' '); //- (pos + i);
	if (!end && str[i])
		buf = ft_strdup(str + i);
	else if (str[i])
	{
		//buf = malloc(sizeof(char)*(end - (pos + i)) + 1);
		buf = ft_substr(str, i, (end - (str + i)));
		if (!buf)
			return(ERROR);
		//ft_strlcpy(buf, pos + i, (end - (pos + i)));
		//cmd->here_stop = buf;
	}
	return (SUCCSESS);
} */


/* char *ft_get_env_pos(char *str)
{
	char *pos;
	
	pos = ft_get_spec_char(str, '$', ESC_SL_DQ_SQ);
	if (!pos) 
	{
		if (*(pos + 1) != '{' && *(pos + 1) != '('))
		return (NULL);
	
} */



