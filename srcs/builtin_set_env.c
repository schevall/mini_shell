/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:33:46 by schevall          #+#    #+#             */
/*   Updated: 2017/03/17 16:49:41 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static int	parse_setenv(char **cmds)
{
	int len;

	len = 1;
	if (!cmds[len])
		return (0);
	while (cmds[len])
		len++;
	if (len > 3)
	{
		ft_printf("usage: setenv [NAME] [value]\n");
		return (0);
	}
	return (1);
}

static void	make_setenv(char *name, char *value, char **env)
{
	char	*new;
	char	*tmp;

	if (!(new = ft_strjoin_free(name, 0, "=", 0)))
		ms_errors(MALLOC, NULL, NULL);
	if (value)
	{
		if (!(new = ft_strjoin_free(new, 1, value, 0)))
			ms_errors(MALLOC, NULL, NULL);
	}
	tmp = *env;
	*env = new;
	ft_strdel(&tmp);
}

static void	add_env(char *name, char *value, char ***env)
{
	char	*new_var;
	char	**new_tab;
	char	**tmp;
	int		len;

	if (!(new_var = ft_strjoin_free(name, 0, "=", 0)))
		ms_errors(MALLOC, NULL, NULL);
	if (value)
	{
		if (!(new_var = ft_strjoin_free(new_var, 1, value, 0)))
			ms_errors(MALLOC, NULL, NULL);
	}
	len = ft_tablen((const char**)*env);
	tmp = *env;
	if (!(new_tab = ft_strndup_tab((const char**)*env, len + 2)))
		ms_errors(MALLOC, NULL, NULL);
	ft_strdel_tab(tmp);
	new_tab[len] = new_var;
	*env = new_tab;
}

void		cmd_set_env(char **cmds, char ***env)
{
	int		i;
	int		len;
	char	*buf;

	i = -1;
	if (parse_setenv(cmds))
	{
		len = ft_strlen(cmds[1]) + 1;
		buf = ft_strjoin(cmds[1], "=");
		while ((*env)[++i])
		{
			if (!ft_strncmp(buf, (*env)[i], len))
			{
				len = -1;
				break ;
			}
		}
		ft_strdel(&buf);
		if (len == -1)
			make_setenv(cmds[1], cmds[2], *env + i);
		else if (len != -1)
			add_env(cmds[1], cmds[2], env);
	}
}

void	format_cmd_for_setenv(char *name, char *value, char ***env)
{
	char	**cmds_setenv;

	if (!(cmds_setenv = (char**)ft_memalloc(sizeof(char*) * 4)))
		ms_errors(MALLOC, NULL, NULL);
	if (!(cmds_setenv[0] = ft_strdup("setenv")))
		ms_errors(MALLOC, NULL, NULL);
	if (!(cmds_setenv[1] = ft_strdup(name)))
		ms_errors(MALLOC, NULL, NULL);
	if (value)
	{
		if (!(cmds_setenv[2] = ft_strdup(value)))
			ms_errors(MALLOC, NULL, NULL);
	}
	cmd_set_env(cmds_setenv, &(*env));
	ft_strdel_tab(cmds_setenv);
}
