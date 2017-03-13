/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/13 14:53:58 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	get_backward_path(char **path)
{
	int		i;

	i = ft_strlen(*path);
	while ((*path)[i] != '/')
	{
		if ((*path)[i] != '/')
			(*path)[i] = '\0';
		i--;
	}
}

static void	set_env_for_cd(char *name, char *value, char ***env)
{
	char	**cmds_setenv;

	cmds_setenv = ft_memalloc(sizeof(char*) * 6);
	cmds_setenv[0] = ft_strdup("setenv");
	cmds_setenv[1] = ft_strdup(name);
	cmds_setenv[2] = ft_strdup("=");
	if (value)
		cmds_setenv[3] = ft_strdup(value);
	cmds_setenv[4] = ft_strdup("1");
	cmd_set_env(cmds_setenv, &(*env));
	ft_strdel_tab(cmds_setenv);
}

static void	get_new_path(char *cmd, char **path, char ***env)
{
	if (*cmd == '/')
	{
		if (!(*path = ft_strdup(cmd)))
			minishell_errors(MALLOC, NULL, NULL);
	}
	else if (!ft_strcmp(cmd, ".."))
	{
		get_backward_path(path);
		if (!(*path = ft_strdup_free(*path)))
			minishell_errors(MALLOC, NULL, NULL);
	}
	else
	{
		*path = ft_strdup_free(*path);
		*path = ft_strjoin_free(*path, 1, "/", 0);
		*path = ft_strjoin_free(*path, 1, cmd, 1);
	}
}

static int	cmd_cd_cases(char *type, char ***env, char *path)
{
	if (!ft_strcmp("go back", type))
	{
		ft_printf("%s\n", ft_get_env("OLDPWD", env));
		set_env_for_cd("PWD", ft_get_env("OLDPWD", env), &(*env));
		chdir(ft_get_env("OLDPWD", env));
		return (1);
	}
	else if (!ft_strcmp("go home", type))
	{
		set_env_for_cd("PWD", ft_get_env("HOME", env), &(*env));
		chdir(ft_get_env("HOME", env));
		return (1);
	}
	else if (!ft_strcmp("tilde_path", type))
	{
		path = ft_strjoin_free(ft_get_env("HOME", env), 0, path + 1, 0);
		if (check_path_errors(path))
			return (0);
		set_env_for_cd("PWD", path, &*env);
		chdir(path);
		ft_strdel(&path);
		return (1);
	}
	return (0);
}

int			cmd_cd(char **cmds, char ***env)
{
	char	*path;

	if (cmds[1] && !ft_strcmp(cmds[1], "-"))
		return (cmd_cd_cases("go back", &(*env), NULL));
	if (!(path = getcwd(NULL, 0)))
		return (0);
	set_env_for_cd("OLDPWD", path, &(*env));
	if (cmds[1] && *cmds[1] == '~' && ft_strcmp(cmds[1], "~"))
		return (cmd_cd_cases("tilde_path", &(*env), cmds[1]));
	if (!cmds[1] || !ft_strcmp(cmds[1], "~"))
		return (cmd_cd_cases("go home", &(*env), NULL));
	else if (!check_path_errors(cmds[1]))
	{
		get_new_path(cmds[1], &path, env);
		if (path)
		{
			chdir(path);
			ft_strdel(&path);
		}
		path = getcwd(NULL, 0);
		set_env_for_cd("PWD", path, &(*env));
		return (1);
	}
	return (0);
}
