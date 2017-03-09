/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/09 19:20:21 by schevall         ###   ########.fr       */
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
	cmds_setenv[3] = ft_strdup(value);
	cmds_setenv[4] = ft_strdup("1");
	cmd_set_env(cmds_setenv, &(*env));
	ft_strdel_tab(cmds_setenv);
}

int		check_cd_error(char **cmds)
{
	int i;
	t_stat buf;

	i = 0;
	ft_printf("init check_cd_error, cmds[1] = [%s]\n", cmds[1]);
	if (access(cmds[1], F_OK) != -1)
	{
		if (lstat((const char*)cmds[1], &buf) != -1)
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
		ft_printf("cd: no such file or directory: %s\n", cmds[1]);
	return (i);
}

void	get_new_path(char *path, char **new_path, char *cur_path, char ***env)
{
	ft_printf("init get_new_path, cur_path = [%s]\n", cur_path);
	ft_printf("path = [%s]\n", path);
	if (*path == '/')
		*new_path = ft_strdup(path);
	else if (!ft_strcmp(path, ".."))
	{
		get_backward_path(&cur_path);
		*new_path = ft_strdup(cur_path);
	}
	else
	{
		*new_path = ft_strdup(cur_path);
		*new_path = ft_strjoin_free(*new_path, 1, "/", 0);
		*new_path = ft_strjoin_free(*new_path, 1, path, 1);
	}
	ft_printf("end get_new_path, new_path = [%s]\n", *new_path);
}

int		cmd_cd(char **cmds, char ***env)
{
	char *cur_path;
	char *new_path;

	ft_printf("init cmd_cd\n");
	if (cmds[1] && !ft_strcmp(cmds[1], "-"))
	{
		set_env_for_cd("PWD", ft_get_env("OLDPWD", env), &(*env));
		chdir(ft_get_env("OLDPWD", env));
		return (1);
	}
	cur_path = getcwd(NULL, 0);
	set_env_for_cd("OLDPWD", cur_path, &(*env));
	if (!cmds[1] || !ft_strcmp(cmds[1], "~"))
	{
		set_env_for_cd("PWD", ft_get_env("HOME", env), &(*env));
		chdir(ft_get_env("HOME", env));
		return (1);
	}
	else if (check_cd_error(cmds))
	{
		new_path = ft_memalloc(PATH_MAX);
		get_new_path(cmds[1], &new_path, cur_path, env);
		if (new_path)
			chdir((const char*)new_path);
		ft_strdel(&cur_path);
		cur_path = getcwd(NULL, 0);
		set_env_for_cd("PWD", cur_path, &(*env));
		ft_printf("after chdir new_path = [%s]\n", new_path);
		return (1);
	}
	return (0);
}
