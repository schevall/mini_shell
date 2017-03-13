/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 13:47:18 by schevall          #+#    #+#             */
/*   Updated: 2017/03/13 14:50:55 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static size_t	parse_echo(char **cmds, int *start)
{
	int		i;
	int		j;
	size_t	len;

	len = 0;
	if (!ft_strcmp(cmds[*start], "-n"))
		(*start)++;
	i = *start;
	while (cmds[i])
		len += ft_strlen(cmds[i++]);
	i = *start;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (cmds[i][j] == 34 || cmds[i][j] == 39)
				len--;
			j++;
		}
		i++;
	}
	return (len);
}

static char		*make_print_echo(char **cmds, size_t len, int start)
{
	char	*print;
	int		j;
	int		k;

	k = 0;
	print = ft_memalloc(len + 1);
	while (cmds[start])
	{
		j = 0;
		while (cmds[start][j])
		{
			if (cmds[start][j] != 34 && cmds[start][j] != 39)
			{
				print[k] = cmds[start][j];
				k++;
			}
			j++;
		}
		if (cmds[start + 1])
			print[k] = ' ';
		k++;
		start++;
	}
	return (print);
}

void			cmd_echo(char **cmds, char ***env)
{
	int		start;
	size_t	len;
	char	*print;

	start = 1;
	len = parse_echo(cmds, &start);
	print = make_print_echo(cmds, len, start);
	if (*cmds[start] == '$' && ft_is_env(cmds[start] + 1, env))
		ft_printf("%s\n", ft_get_env(cmds[start] + 1, env));
	else if (start == 2)
		ft_printf("%s%%\n", print);
	else
		ft_printf("%s\n", print);
}
