/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:23:29 by schevall          #+#    #+#             */
/*   Updated: 2017/03/20 15:02:38 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static int	check_path_errors_aux(int j, char *sub_path, char *path)
{
	t_stat buf;

	if (j > NAME_MAX)
		return (ms_errors(NAME_TOO_LONG, path, "minishell"));
	if (access(sub_path, F_OK) == -1)
		return (ms_errors(NO_F, sub_path, "minishell"));
	if (stat(sub_path, &buf) == -1)
		return (ms_errors(NOT_DIR, path, "minishell"));
	if (access(sub_path, X_OK) == -1)
		return (ms_errors(P_DN, sub_path, "minishell"));
	return (0);
}

int			check_path_errors(char *path)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	if (ft_strlen(path) >= PATH_MAX)
		return (ms_errors(PATH_TOO_LONG, NULL, "minishell"));
	buf = ft_memalloc(PATH_MAX);
	while (path[i] && i < ft_strlen(path) && i > -1)
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
			i = -2;
		i++;
	}
	ft_strdel(&buf);
	return (i = -1 ? 1 : 0);
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
		return (ms_errors(IS_DIR, path, "minishell"));
	return (0);
}
