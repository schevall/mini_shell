/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 16:30:53 by schevall          #+#    #+#             */
/*   Updated: 2017/03/16 18:54:22 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

int		ft_is_env(char *name, char ***env)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(name);
	while ((*env)[i])
	{
		if (!ft_strncmp(name, (*env)[i], len))
			return (1);
		i++;
	}
	return (0);
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
	return (NULL);
}

void	*cmd_env(char **cmds, char ***env)
{
	int		i;
	char	**tmp_env;

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
