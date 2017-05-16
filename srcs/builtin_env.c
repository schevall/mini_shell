/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:53 by schevall          #+#    #+#             */
/*   Updated: 2017/03/20 18:23:39 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int		ft_is_env(char *name, char ***env)
{
	int		len;
	int		i;
	char	*buf;

	i = 0;
	if (!name)
		return (0);
	buf = ft_strjoin(name, "=");
	len = ft_strlen(buf);
	while ((*env)[i])
	{
		if (!ft_strncmp(buf, (*env)[i], len))
		{
			i = -1;
			break ;
		}
		i++;
	}
	ft_strdel(&buf);
	return (i = -1 ? 1 : 0);
}

char	**ft_get_env(char *name, char **env)
{
	if (!name)
		return (NULL);
	while (*env)
	{
		if (!(ft_strncmp(name, *env, ft_strlen(name))))
			return (env);
		env++;
	}
	return (env);
}

void	set_env_tmp(char *cmds, char ***env)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (cmds[i] != '=')
		i++;
	name = ft_strsub(cmds, 0, i);
	value = ft_strsub(cmds, i + 1, ft_strlen(cmds));
	format_cmd_for_setenv(name, value, env);
	ft_strdel(&name);
	ft_strdel(&value);
}

void	cmd_env_aux(char **cmds, char ***tmp_env, int *exec, int *i)
{
	ft_printf("cmds[%d] = %s\n", *i, cmds[*i]);
	if (!ft_strcmp(cmds[*i], "-i"))
	{
		ft_strdel_tab(*tmp_env);
		*tmp_env = (char**)ft_memalloc(sizeof(char*));
	}
	else if (ft_strchr(cmds[*i], '='))
		set_env_tmp(cmds[*i], tmp_env);
	else if (!is_path(cmds[*i]) && ft_strcmp(cmds[*i], "env"))
	{
		*exec = 1;
		run_cmds(cmds + *i, tmp_env, "env");
	}
}

void	cmd_env(char **cmds, char ***env)
{
	int		i;
	char	**tmp_env;
	int		exec;

	exec = 0;
	i = 0;
	if (cmds[1] && !ft_strcmp(cmds[1], "-i"))
		tmp_env = (char**)ft_memalloc(sizeof(char*));
	else
		tmp_env = ft_strdup_tab((const char**)*env);
	while (cmds[++i])
		cmd_env_aux(cmds, &tmp_env, &exec, &i);
	if (!exec)
		ft_print_tab(tmp_env);
	ft_strdel_tab(tmp_env);
}
