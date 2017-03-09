/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:53 by schevall          #+#    #+#             */
/*   Updated: 2017/03/09 19:05:51 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*ft_get_env(char *name, char ***env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	ft_printf("init ft_get_env\n");
	while ((*env)[i])
	{
		if (!ft_strncmp(name, (*env)[i], 4))
		{
			while ((*env)[i][j] != '=')
				j++;
			j++;
			return (ft_strdup((*env)[i] + j));
		}
		i++;
	}
	return (NULL);
}

void	*cmd_env(char **cmds, char ***env)
{
	int i;
	char **tmp_env;

	i = 0;
	if (cmds[1] && !ft_strcmp(cmds[1], "-i"))
	{
		tmp_env = (char**)ft_memalloc(1);
		tmp_env[0] = NULL;
		return (tmp_env);
	}
	if (!*env)
		return (NULL);
	while ((*env)[i])
	{
		ft_printf("%s\n", (*env)[i]);
		i++;
	}
	return (NULL);
}
