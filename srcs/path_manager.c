/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:23:29 by schevall          #+#    #+#             */
/*   Updated: 2017/03/13 14:51:52 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static int	check_path_errors_aux(int j, char *buf, char *path)
{
	if (j > NAME_MAX)
		return (minishell_errors(NAME_TOO_LONG, path, "minishell"));
	if (access(buf, F_OK) == -1)
		return (minishell_errors(NOT_FOUND, buf, "minishell"));
	if (access(buf, X_OK) == -1)
		return (minishell_errors(PERM_DENIED, buf, "minishell"));
	return (0);
}

int			check_path_errors(char *path)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	buf = ft_memalloc(PATH_MAX);
	if (ft_strlen(path) >= PATH_MAX)
		return (minishell_errors(PATH_TOO_LONG, NULL, "minishell"));
	while (path[i])
	{
		j = 0;
		while (path[i] && path[i] != '/')
		{
			buf[i] = path[i];
			j++;
			i++;
		}
		if (path[i] == '/')
			buf[i] = path[i];
		if (check_path_errors_aux(j, buf, path))
			return (1);
		i++;
	}
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
