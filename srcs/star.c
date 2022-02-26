#include "minishell.h"

static size_t	is_in_pattern(char *str, char **parts, size_t fl_star)
{
	size_t	l;
	char	*ptr;

	l = amount_elements(parts);
	if (!l && fl_star)
		return (1);	// "*"
 	if (l == 1 && !fl_star)	// "!*"
		return (!ft_strncmp(str, *parts, ft_strlen(str)));
	ptr = *parts;
	while (parts && *parts && str && *str)
	{
		l = ft_strlen(*parts);
		if ((fl_star & 1) && (*parts == ptr) && ft_strncmp(str, ptr, l))
			return (0);	//	"M*"
		if ((fl_star & 2) && !(*(parts + 1)))
			return ((ft_strlen(str) >= l) && !(ft_strncmp(str + ft_strlen(str) - ft_strlen(*parts), \
					*parts, l)));	//	"*t"
		str = ft_strnstr(str, *parts++, l);
		if (!str)
			return (0);
		str += l;
	}
	return (1);
}

static t_list	*filenames_from_dir(char *path, char **parts, size_t fl_star)
{
	t_list			*res;
	DIR				*dir;
	struct dirent	*entry;

	res = NULL;
	if (path)
	{
		if ((dir = opendir(path)))
		{
			while ((entry = readdir(dir)) != NULL)
				if (is_in_pattern(entry->d_name, parts, fl_star) && \
					(*entry->d_name != '.'))
				{
					if (res)
						ft_lstadd_back(&res, \
							ft_lstnew(ft_strdup(entry->d_name)));
					else
						res = ft_lstnew(ft_strdup(entry->d_name));
				}
			closedir(dir);
		}
	}
	return (res);
}

static size_t	flag_star(char *str)
{
	size_t	fl;

	fl = 0;
	if (str)
	{
		fl = (ft_strchr(str, '*') != NULL) << 2;
		fl += fl && (*str != '*');
		fl += (fl && (*(str + ft_strlen(str) - 1) != '*')) << 1;
	}
	return (fl);
}

char	**star(char *str, t_d *d)
{
	char	*path;
	char	**res;
	char	**parts;
	size_t	amount;
	t_list	*list_of_fnames;
	t_list	*tmp;

	res = NULL;
	//  path = pwd
	if_err_fatal(path = malloc(LEN_PATH), 2, d);
	if (getcwd(path, LEN_PATH))
	{
		parts = ft_split(str, '*');
		list_of_fnames = filenames_from_dir(path, parts, flag_star(str));
		free2(parts);
		amount = ft_lstsize(list_of_fnames);
		if_err_fatal(res = malloc(sizeof(char *) * (amount + 1)), 2, d);
		res[amount] = NULL;
		parts = res;
		tmp = list_of_fnames;
		while (tmp)
		{
			*parts++ = ft_strdup(tmp->content);
			tmp = tmp->next;
		}
		ft_lstclear(&list_of_fnames, free);
	}
	free(path);
	return (res);
}

/* char	*star_to_char(char *str, t_d *d)
{
	char	*path;
	char	*res;
	char	*ptr;
	char	**parts;
	t_list	*list_of_fnames;
	t_list	*tmp;

	res = NULL;
	if_err_fatal(path = malloc(LEN_PATH), 2, d);
	if (getcwd(path, LEN_PATH))
	{
		parts = ft_split(str, '*');
		list_of_fnames = filenames_from_dir(path, parts, flag_star(str));
		free2(parts);
		if_err_fatal(res = malloc(sizeof(char) * \
			ft_lstcalc_total_len(list_of_fnames)), 2, d);
		ptr = res;
		tmp = list_of_fnames;
		while (tmp)
		{
			ptr += ft_strlcpy(ptr, tmp->content, ft_strlen(tmp->content));
			tmp = tmp->next;
			*ptr++ = (SP * (tmp != NULL));
		}
		ft_lstclear(&list_of_fnames, free);
	}
	free(path);
	return (res);
} */
