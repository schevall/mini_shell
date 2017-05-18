/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/20 18:23:41 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	get_new_path(char *cmd, char **cur_path, char ***env)
{
	char *tmp;
	char *tmp2;

	if (*cmd == '/')
	{
		ft_strdel(cur_path);
		*cur_path = ft_strdup(cmd);
	}
	else if (*cmd == '~')
	{
		tmp = *ft_get_env("HOME", *env) + 5;
		tmp2 = cmd + 2;
		ft_strdel(cur_path);
		if (ft_sprintf(cur_path, "%s/%s", tmp, tmp2) == -1)
			ms_errors(MALLOC, NULL, NULL);
	}
	else
	{
		if (!(tmp = ft_strdup_free(*cur_path)))
			ms_errors(MALLOC, NULL, NULL);
		if (ft_sprintf(cur_path, "%s/%s", tmp, cmd) == -1)
			ms_errors(MALLOC, NULL, NULL);
		ft_strdel(&tmp);
	}
}

int			change_path(char *path, char ***env)
{
	chdir(path);
	ft_strdel(&path);
	path = getcwd(NULL, 0);
	format_cmd_for_setenv("PWD", path, &(*env));
	ft_strdel(&path);
	return (0);
}

int			cmd_cd_cases(char *type, char ***env, char *cur_path)
{
	char *new_path;
	char *target;

	if (!ft_strcmp("go back", type))
	{
		if (!(ft_get_env("OLDPWD", *env)))
			return (ms_errors(OPWD_NOT, NULL, "cd"));
		target = *ft_get_env("OLDPWD", *env) + 7;
		if (access(target, F_OK) == -1)
			return (ms_errors(NO_F, (*ft_get_env("OLDPWD", *env) + 7), "cd"));
		if (access(target, X_OK) == -1)
			return (ms_errors(P_DN, (*ft_get_env("OLDPWD", *env) + 7), "cd"));
		if (!(new_path = ft_strdup(target)))
			return (ms_errors(MALLOC, NULL, NULL));
		ft_printf("%s\n", new_path);
		format_cmd_for_setenv("OLDPWD", cur_path, &(*env));
	}
	else if (!ft_strcmp("go home", type))
	{
		if (!(new_path = ft_strdup(*ft_get_env("HOME", *env) + 5)))
			return (ms_errors(MALLOC, NULL, NULL));
	}
	ft_strdel(&cur_path);
	return (change_path(new_path, env));
}

void		get_backward(char **path)
{
	int		i;
	char	*tmp;

	i = ft_strlen(*path);
	while (i && (*path)[i] != '/')
		i--;
	tmp = ft_strsub(*path, 0, i);
	ft_strdel(path);
	*path = tmp;
}

int			cmd_cd(char **cmds, char ***env)
{
	char *path;

	if (!(path = getcwd(NULL, 0)) && cmds[1])
		return (cd_error(cmds, env));
	if (cmds[1] && !ft_strcmp(cmds[1], "-"))
		return (cmd_cd_cases("go back", &(*env), path));
	format_cmd_for_setenv("OLDPWD", path, &(*env));
	if (!cmds[1] || !ft_strcmp(cmds[1], "~"))
		return (cmd_cd_cases("go home", &(*env), path));
	get_new_path(cmds[1], &path, env);
	if (!check_path_errors(path))
		return (change_path(path, env));
	if (path)
		ft_strdel(&path);
	return (1);
}
