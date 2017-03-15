/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:23:29 by schevall          #+#    #+#             */
/*   Updated: 2017/03/15 19:18:07 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static int	check_path_errors_aux(int j, char *sub_path, char *path)
{
	t_stat buf;

	if (!(path = getcwd(NULL, 0)))
		return (minishell_errors(PATH_TROUBLE, NULL, "chdir"));
	if (j > NAME_MAX)
		return (minishell_errors(NAME_TOO_LONG, path, "minishell"));
	if (stat(sub_path, &buf) == -1)
		return (minishell_errors(NOT_DIR, path, "minishell"));
	if (access(sub_path, F_OK) == -1)
		return (minishell_errors(NOT_FOUND, sub_path, "minishell"));
	if (access(sub_path, X_OK) == -1)
		return (minishell_errors(PERM_DENIED, sub_path, "minishell"));
	return (0);
}

int			check_path_errors(char *path)
{
	char	*buf;
	int		i;
	int		j;

	i = -1;
	if (ft_strlen(path) >= PATH_MAX)
		return (minishell_errors(PATH_TOO_LONG, NULL, "minishell"));
	buf = ft_memalloc(PATH_MAX);
	while (path[++i])
	{
		j = 0;
		while (path[i] && path[i] != '/')
		{
			buf[i] = path[i];
			i++;
			j++;
		}
		if (path[i] == '/')
			buf[i] = path[i];
		if (check_path_errors_aux(j, buf, path))
			break ;
	}
	ft_strdel(&buf);
	return (0);
}

static int	find_slash(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int			is_path(char *path)
{
	t_stat	buf;

	if (!find_slash(path))
		return (0);
	if (stat(path, &buf) == -1)
		return (check_path_errors(path));
	else if (S_ISDIR(buf.st_mode))
		return (minishell_errors(IS_DIR, path, "minishell"));
	return (0);
}
