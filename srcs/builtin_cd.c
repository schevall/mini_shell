/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/08 15:18:50 by schevall         ###   ########.fr       */
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
	cmd_set_env(cmds_setenv, env);
	ft_strdel_tab(cmds_setenv);
}

int		check_cd_error(char **cmds)
{
	t_stat *buf;
	if (lstat(cmds[1], buf))
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
	check_cd_error(cmds);
	new_path = ft_strjoin_free(new_path, 1, cmds[1], 0);
	chdir((const char*)new_path);
	ft_printf("after chdir new_path = [%s], size = [%zu]\n", new_path, len);
	return (0);
}
