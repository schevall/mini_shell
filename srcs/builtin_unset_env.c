/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 18:46:05 by schevall          #+#    #+#             */
/*   Updated: 2017/03/06 19:13:09 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	erase_var(char *name, char ***env, int len)
{
	int tab_len;
	char **new_tab;
	int j;
	int i;

	j = 0;
	i = 0;
	ft_printf("\ninit erase_var, name = [%s]\n\n", name);
	tab_len = ft_tablen((const char**)*env) - 1;
	new_tab = (char**)ft_memalloc(sizeof(char*) * (tab_len + 1));
	while ((*env)[j])
	{
		if (ft_strncmp((*env)[j], name, len))
		{
			new_tab[i] = ft_strdup((*env)[j]);
			i++;
		}
		j++;
	}
	*env = new_tab;
}

void	cmd_unset_env(char **cmds, char ***env)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(cmds[1]);
	while ((*env)[i])
	{
		if (!ft_strncmp(cmds[1], (*env)[i], len))
			erase_var(cmds[1], env, len);
		i++;
	}
}