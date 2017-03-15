/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/15 19:18:02 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

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

static int	get_new_path(char *cmd, char **path, char ***env)
{
	char *tmp;

	if (*cmd == '/')
	{
		ft_strdel(path);
		if (!(*path = ft_strdup(cmd)))
			return (minishell_errors(MALLOC, NULL, NULL));
		return (0);
	}
	else if (*cmd == '~')
	{
		if (!(tmp = ft_strdup(*ft_get_env("HOME", *env) + 5)))
			return (minishell_errors(MALLOC, NULL, NULL));
	}
	else
	{
		tmp = ft_strdup(*path);
		ft_strdel(path);
	}
	if (ft_sprintf(path, "%s/%s", tmp, cmd) == -1)
		return (minishell_errors(MALLOC, NULL, NULL));
	return (0);
}

static int	cmd_cd_cases(char *type, char ***env, char *cur_path)
{
	char *new_path;
	char *tmp;

	if (!ft_strcmp("go back", type))
	{
		if (!(new_path = ft_strdup(*ft_get_env("OLDPWD", *env) + 7)))
			return (minishell_errors(MALLOC, NULL, NULL));
		ft_printf("%s\n", new_path);
		set_env_for_cd("OLDPWD", cur_path, &(*env));
	}
	else if (!ft_strcmp("go home", type))
	{
		if (!(new_path = ft_strdup(*ft_get_env("HOME", *env) + 5)))
			return (minishell_errors(MALLOC, NULL, NULL));
	}
	set_env_for_cd("PWD", new_path, &(*env));
	ft_strdel(&cur_path);
	chdir(new_path);
	ft_strdel(&new_path);
	return (1);
}

int			cd_error(char **cmds, char ***env)
{
	char **path;

	path = ft_get_env("PWD", *env);
	check_path_errors(*path);
	return (1);
}

int			cmd_cd(char **cmds, char ***env)
{
	char *path;

	if (!(path = getcwd(NULL, 0)) && cmds[1])
		return (cd_error(cmds, env));
	if (cmds[1] && !ft_strcmp(cmds[1], "-"))
		return (cmd_cd_cases("go back", &(*env), path));
	set_env_for_cd("OLDPWD", path, &(*env));
	if (!cmds[1] || !ft_strcmp(cmds[1], "~"))
		return (cmd_cd_cases("go home", &(*env), path));
	get_new_path(cmds[1], &path, env);
	if (!check_path_errors(path))
	{
		chdir(path);
		ft_strdel(&path);
		path = getcwd(NULL, 0);
		set_env_for_cd("PWD", path, &(*env));
		ft_strdel(&path);
		return (0);
	}
	return (1);
}
