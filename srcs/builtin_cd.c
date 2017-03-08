/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/08 18:32:02 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	path_backward(char **path)
{
	size_t len;

	len = ft_strlen(*path) - 1;
	while ((*path)[len] && (*path)[len] != '/')
		len--;
	*path = ft_strndup(*path, len + 1);
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
	ft_printf("cmds_setenv[0] = [%s]\n", cmds_setenv[0]);
	ft_printf("cmds_setenv[1] = [%s]\n", cmds_setenv[1]);
	ft_printf("cmds_setenv[2] = [%s]\n", cmds_setenv[2]);
	ft_printf("cmds_setenv[3] = [%s]\n", cmds_setenv[3]);
	ft_printf("cmds_setenv[4] = [%s]\n", cmds_setenv[4]);
	cmd_set_env(cmds_setenv, env);
	ft_strdel_tab(cmds_setenv);
}

int		check_cd_error(char **cmds)
{
	int i;
	t_stat *buf;

	i = 0;
	ft_printf("init check_cd_error\n");
	if (access(cmds[1], F_OK) != -1)
	{
		if (!lstat(cmds[1], buf))
		{
			if (S_ISDIR(buf->st_mode))
			{
				if (access(cmds[1], X_OK) != -1)
					i = 1;
				else
					ft_printf("cd: permission denied: %s\n", cmds[1]);
			}
			else
				ft_printf("cd: not a directory: %s\n", cmds[1]);
		}
	}
	else
		ft_printf("cd: no such file or directory: %s\n", cmds[1]);
	return (i);
}

void	get_new_path(char *path, char **new_path, char *cur_path)
{
	ft_printf("init get_new_path, cur_path = [%s]\n", cur_path);
	ft_printf("path = [%s]\n", path);
	if (*path == '/')
		*new_path = ft_strdup(path);
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
	size_t	len;

	ft_printf("init cmd_cd\n");
	cur_path = ft_memalloc(1024);
	new_path = ft_memalloc(1024);
	if (!getcwd(cur_path, 1024))
		ft_printf("current path is too long\n");
	set_env_for_cd("OLDPWD", cur_path, env);
	if (check_cd_error(cmds))
	{
		get_new_path(cmds[1], &new_path, cur_path);
		set_env_for_cd("PWD", new_path, env);
		chdir((const char*)new_path);
		ft_printf("after chdir new_path = [%s], size = [%zu]\n", new_path, len);
		return (1);
	}
	return (0);
}
