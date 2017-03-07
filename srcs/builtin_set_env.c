/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:33:46 by schevall          #+#    #+#             */
/*   Updated: 2017/03/07 15:36:06 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static int	parse_setenv(char **cmds, int *mode)
{
	if (cmds[2] && ft_strcmp(cmds[2], "="))
	{
		ft_printf("usage: setenv [NAME] [=] [value] [overide_mode]\n");
		return (0);
	}
	if (cmds[4] && ft_atoi(cmds[4]) == 1)
		*mode = 1;
	else
		*mode = 0;
	return (1);
}

static void	make_setenv(char *name, char *value, char **var)
{
	char *new;
	char *tmp;

	ft_printf("\ninit make_setenv, name = [%s], value = [%s]\n\n", name, value);
	new = ft_strjoin_free(name, 1, "=", 0);
	new = ft_strjoin_free(new, 1, value, 1);
	tmp = *var;
	*var = new;
	ft_strdel(&tmp);
}

static void	add_env(char *name, char *value, char ***env)
{
	char *new_var;
	char **new_tab;
	int len;

	ft_printf("\ninit add_env, name = [%s], value = [%s]\n\n", name, value);
	new_var = ft_strjoin_free(name, 1, "=", 0);
	new_var = ft_strjoin_free(new_var, 1, value, 1);
	len = ft_tablen((const char**)*env);
	new_tab = ft_strndup_tab((const char**)*env, len + 2);
	new_tab[len] = new_var;
	*env = new_tab;
}

void	cmd_set_env(char **cmds, char ***env)
{
	int mode;
	int found;
	int i;
	int len;

	ft_printf("init setenv\n");
	i = 0;
	found = 0;
	if (parse_setenv(cmds, &mode))
	{
		len = ft_strlen(cmds[1]);
		while ((*env)[i])
		{
			if (!ft_strncmp(cmds[1], (*env)[i], len))
			{
				ft_printf("NAME FOUND\n");
				found = 1;
				break ;
			}
			i++;
		}
		if (found && mode)
			make_setenv(cmds[1], cmds[3], &(*env)[i]);
		else if (!found)
			add_env(cmds[1], cmds[3], env);
	}
}
