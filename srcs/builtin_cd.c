/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/10 18:37:06 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	get_backward_path(char **path)
{
	int i;

	i = ft_strlen(*path);
	while ((*path)[i] != '/')
	{
		if ((*path)[i] != '/')
			(*path)[i] = '\0';
		i--;
	}
}

void	set_env_for_cd(char *name, char *value, char ***env)
{
	char **cmds_setenv;

	cmds_setenv = ft_memalloc(sizeof(char*) * 6);
	cmds_setenv[0] = ft_strdup("setenv");
	cmds_setenv[1] = ft_strdup(name);
	cmds_setenv[2] = ft_strdup("=");
	if (value)
		cmds_setenv[3] = ft_strdup(value);
	cmds_setenv[4] = ft_strdup("1");
	ft_printf("after set_env_for_cd\n");
	cmd_set_env(cmds_setenv, &(*env));
	ft_strdel_tab(cmds_setenv);
	ft_printf("after set_env_for_cd, del\n");
}

int		check_cd_error(char **cmds)
{
	int i;
	t_stat buf;

	i = 0;
	if (access(cmds[1], F_OK) != -1)
	{
		if (stat(cmds[1], &buf) != -1)
		{
			if (S_ISDIR(buf.st_mode))
			{
				if (access(cmds[1], X_OK) != -1)
					i = 1;
				else
					ft_printf("cd: permission denied: %s\n", cmds[1]);
			}
			else
				ft_printf("cd: not a directory: %s\n", cmds[1]);
		}
		else
			ft_printf("lstat trouble\n"); //a virer
	}
	else
		ft_printf("cd: such file or directory: %s\n", cmds[1]);
	return (i);
}

void	get_new_path(char *cmd, char **path, char ***env)
{
	char *tmp;

	if (*cmd == '/')
		*path = ft_strdup(cmd);
	else if (!ft_strcmp(cmd, ".."))
	{
		get_backward_path(path);
		tmp = *path;
		*path = ft_strdup(*path);
		ft_strdel(&tmp);
	}
	else
	{
		tmp = *path;
		*path = ft_strdup(*path);
		ft_strdel(&tmp);
		*path = ft_strjoin_free(*path, 1, "/", 0);
		*path = ft_strjoin_free(*path, 1, cmd, 1);
	}
}

int		cmd_cd_cases(char *type, char ***env)
{
	if (!ft_strcmp("go back", type))
	{
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
	else if (!ft_strcmp("path trouble", type))
	{
		minishell_errors(PATH_TROUBLE, "pwd", NULL);
		return (0);
	}
	return (0);
}

int		cmd_cd(char **cmds, char ***env)
{
	char *path;

	if (cmds[1] && !ft_strcmp(cmds[1], "-"))
		return (cmd_cd_cases("go back", &(*env)));
	if (!(path = getcwd(NULL, 0)))
		return (cmd_cd_cases("path trouble", &(*env)));
	set_env_for_cd("OLDPWD", path, &(*env));
	if (!cmds[1] || !ft_strcmp(cmds[1], "~"))
		return (cmd_cd_cases("go home", &(*env)));
	else if (check_cd_error(cmds))
	{
		get_new_path(cmds[1], &path, env);
		if (path)
			chdir(path);
		ft_strdel(&path);
		path = getcwd(NULL, 0);
		set_env_for_cd("PWD", path, &(*env));
		return (1);
	}


	return (0);
}
