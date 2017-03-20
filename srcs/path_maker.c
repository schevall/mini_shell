/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:29:31 by schevall          #+#    #+#             */
/*   Updated: 2017/03/20 15:13:11 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static char	**get_potentials_paths(char **env, char *cmd)
{
	char	**paths;
	int		i;

	i = 0;
	if (!ft_get_env("PATH", env))
		return (NULL);
	paths = ft_strsplit((*ft_get_env("PATH", env) + 5), ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin_free(paths[i], 1, "/", 0);
		paths[i] = ft_strjoin_free(paths[i], 1, cmd, 0);
		i++;
	}
	return (paths);
}

int			can_access(char **potentials_path, int i)
{
	if (!ft_strchr(potentials_path[i], '/'))
		return (0);
	if (access(potentials_path[i], F_OK) != -1)
	{
		if (!access(potentials_path[i], X_OK))
			return (1);
		else
		{
			ms_errors(P_DN, potentials_path[i], "minishell");
			return (1);
		}
	}
	else
		return (-1);
}

int			is_pathed(char **path, char *cmd, char **env)
{
	char	**potentials_path;
	int		i;

	i = 0;
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (0);
	if (!(potentials_path = get_potentials_paths(env, cmd)))
		return (0);
	while (potentials_path[i])
	{
		if (can_access(potentials_path, i) == 1)
		{
			*path = ft_strdup(potentials_path[i]);
			break ;
		}
		i++;
	}
	if (potentials_path[i])
		i = -1;
	ft_strdel_tab(potentials_path);
	return (i);
}
