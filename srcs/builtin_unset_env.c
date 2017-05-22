/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 18:46:05 by schevall          #+#    #+#             */
/*   Updated: 2017/03/20 18:18:09 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	erase_var(char *name, char ***env, int len)
{
	int		tab_len;
	char	**new_tab;
	int		j;
	int		i;

	j = 0;
	i = 0;
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
	ft_strdel_tab(*env);
	*env = new_tab;
}

void		cmd_unset_env(char **cmds, char ***env)
{
	int		len;
	int		i;
	char	**current;

	i = 0;
	if (!cmds[1])
		return ;
	while ((*env)[i])
	{
		current = ft_strsplit((*env)[i], 61);
		len = ft_strlen(current[0]);
		if (!ft_strncmp(cmds[1], current[0], len))
		{
			erase_var(cmds[1], &(*env), len);
			break ;
		}
		ft_strdel(current);
		i++;
	}
}
