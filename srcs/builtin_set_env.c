/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:33:46 by schevall          #+#    #+#             */
/*   Updated: 2017/03/14 18:49:58 by schevall         ###   ########.fr       */
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

static void	make_setenv(char *name, char *value, char **var)
{
	char	*new;

	if (!(new = ft_strjoin_free(name, 0, "=", 0)))
		minishell_errors(MALLOC, NULL, NULL);
	if (value)
	{
		if (!(new = ft_strjoin_free(new, 1, value, 0)))
			minishell_errors(MALLOC, NULL, NULL);
	}
	*var = new;
}

static void	add_env(char *name, char *value, char ***env)
{
	char	*new_var;
	char	**new_tab;
	char	**tmp;
	int		len;

	if (!(new_var = ft_strjoin_free(name, 0, "=", 0)))
		minishell_errors(MALLOC, NULL, NULL);
	if (value)
	{
		if (!(new_var = ft_strjoin_free(new_var, 1, value, 0)))
			minishell_errors(MALLOC, NULL, NULL);
	}
	len = ft_tablen((const char**)*env);
	tmp = *env;
	if (!(new_tab = ft_strndup_tab((const char**)*env, len + 2)))
		minishell_errors(MALLOC, NULL, NULL);
	ft_strdel_tab(tmp);
	new_tab[len] = new_var;
	*env = new_tab;
}

void		cmd_set_env(char **cmds, char ***env)
{
	int		found;
	int		i;
	int		len;

	i = 0;
	found = 0;
	if (parse_setenv(cmds))
	{
		len = ft_strlen(cmds[1]);
		while ((*env)[i])
		{
			if (!ft_strncmp(cmds[1], (*env)[i], len))
			{
				found = 1;
				break ;
			}
			i++;
		}
		if (found)
			make_setenv(cmds[1], cmds[2], &(*env)[i]);
		else if (!found)
			add_env(cmds[1], cmds[2], &(*env));
	}
}
