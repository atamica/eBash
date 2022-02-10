#include "minishell.h"

static size_t	is_in_pattern(char *str, char **parts, size_t fl_star)
{
	size_t	l;
	char	*ptr;

	l = amount_elements(parts);
	ptr = *parts;
	if (!l && fl_star)
		return (1);	// "*"
 	if (l == 1 && !fl_star)
		return (!ft_strncmp(str, *parts, ft_strlen(str)));
	while (parts && *parts &&  str && *str)
	{
		if ((fl_star & 1) && (*parts == ptr) && \
				ft_strncmp(str, ptr, ft_strlen(ptr)))
			return (0);	//	"M*"
		if ((fl_star & 2) && !(*(parts + 1)))
			return ((ft_strlen(str) >= ft_strlen(*parts)) && !(ft_strncmp(str + ft_strlen(str) - ft_strlen(*parts), \
					*parts, ft_strlen(*parts))));	//	"*t"
		l = ft_strlen(*parts);
printf("B:str=(%s), part(%s) len_p=%zu ==> ", str, *parts, ft_strlen(*parts));
		str = ft_strnstr(str, *parts++, l);
printf("str=(%s)\n", str);
		if (str)
			str += l;
		else
			return (0);		
	}
	return (1);
}

static t_list	*filenames_from_dir(char *path,  char **parts, size_t fl_star)
{
	t_list			*res;
	DIR				*dir;
	struct dirent	*entry;

	res = NULL;
	if (path)
	{
		dir = opendir(path);
		if (dir)
		{
			while ((entry = readdir(dir)) != NULL)
				if ((entry->d_type == DT_REG) && \
						is_in_pattern(entry->d_name, parts, fl_star))
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

static size_t	is_exist_non_star(char *str)
{
	while (str && *str)
		if (*str++ != '*')
			return (1);
	return (0);
}

char	**star(char *str, t_d *d)
{
	char	*path;
	char	**res;
	char	**parts;
	size_t	amount;
	t_list	*list_of_fnames;
	t_list	*tmp;
	size_t	fl;

	res = NULL;
	amount = 0;
	if_err_fatal(path = malloc(LEN_PATH), 2, d);
	if (getcwd(path, LEN_PATH))
	{
		parts = ft_split(str, '*');
print_param(parts, "-->", '\n');
		fl = (ft_strchr(str, '*') != NULL) << 2;
		fl += (*str != '*') && is_exist_non_star(str + 1);
		fl += (fl && (*(str + ft_strlen(str) - 1) != '*')) << 1;
printf("len=%zu fl=%zu\n", amount_elements(parts), fl);
		list_of_fnames = filenames_from_dir(path, parts, fl);
		free2(parts);
		free(path);
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
	return (res);
}