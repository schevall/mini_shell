/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/14 18:49:55 by schevall         ###   ########.fr       */
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

	if (!(cmds_setenv = ft_memalloc(sizeof(char*) * 4)))
		minishell_errors(MALLOC, NULL, NULL);
	if (!(cmds_setenv[0] = ft_strdup("setenv")))
		minishell_errors(MALLOC, NULL, NULL);
	if (!(cmds_setenv[1] = ft_strdup(name)))
		minishell_errors(MALLOC, NULL, NULL);
	if (value)
	{
		if (!(cmds_setenv[2] = ft_strdup(value)))
			minishell_errors(MALLOC, NULL, NULL);
	}
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
		if (!(*path = ft_strdup_free(*path)))
			minishell_errors(MALLOC, NULL, NULL);
		if (!(*path = ft_strjoin_free(*path, 1, "/", 0)))
			minishell_errors(MALLOC, NULL, NULL);
		if (!(*path = ft_strjoin_free(*path, 1, cmd, 0)))
			minishell_errors(MALLOC, NULL, NULL);
	}
}

static int	cmd_cd_cases(char *type, char ***env, char *path)
{
	char *tmp;

	if (!ft_strcmp("go back", type))
	{
		tmp = ft_get_env("OLDPWD", env);
		ft_printf("%s\n", tmp);
		ft_strdel(&tmp);
		tmp = ft_get_env("OLDPWD", env);
		set_env_for_cd("PWD", tmp, &(*env));
		chdir(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	else if (!ft_strcmp("go home", type))
	{
		tmp = ft_get_env("HOME", env);
		set_env_for_cd("PWD", tmp, &(*env));
		chdir(tmp);
		ft_strdel(&tmp);
		return (1);
	}
	else if (!ft_strcmp("tilde_path", type))
	{
		tmp = ft_get_env("HOME", env);
		path = ft_strjoin_free(tmp, 1, path + 1, 0);
		if (check_path_errors(path))
		{
			ft_strdel(&path);
			return (0);
		}
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
	ft_strdel(&path);
	if (cmds[1] && *cmds[1] == '~' && ft_strcmp(cmds[1], "~"))
		return (cmd_cd_cases("tilde_path", &(*env), cmds[1]));
	if (!cmds[1] || !ft_strcmp(cmds[1], "~"))
		return (cmd_cd_cases("go home", &(*env), NULL));
	else if (!check_path_errors(cmds[1]))
	{
		path = getcwd(NULL, 0);
		get_new_path(cmds[1], &path, env);
		if (path)
		{
			chdir(path);
			ft_strdel(&path);
		}
		path = getcwd(NULL, 0);
		set_env_for_cd("PWD", path, &(*env));
		ft_strdel(&path);
		return (1);
	}
	return (0);
}
