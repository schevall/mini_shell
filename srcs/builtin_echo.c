/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 13:47:18 by schevall          #+#    #+#             */
/*   Updated: 2017/03/17 14:11:22 by schevall         ###   ########.fr       */
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
	print = (char*)ft_memalloc(len + 1);
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

static void			echo_env_var(char *print, char ***env)
{
	char	**var;
	int		i;
	int		len;

	i = 0;
	var = ft_strsplit(print, '$');
	while (var[i])
	{
		if (ft_is_env(var[i], env))
		{
			len = ft_strlen(var[i]) + 1;
			ft_printf("%s", *ft_get_env(var[i], *env) + len);
		}
		else
			ft_printf("$%s", var[i]);
		i++;
	}
	ft_printf("\n");
}

void			cmd_echo(char **cmds, char ***env)
{
	int		start;
	size_t	len;
	char	*print;
	char	*var;

	start = 1;
	len = parse_echo(cmds, &start);
	print = make_print_echo(cmds, len, start);
	if (ft_strchr(print, '$'))
		echo_env_var(print, env);
	else if (start == 2)
		ft_printf("%s", print);
	else
		ft_printf("%s\n", print);
	ft_strdel(&print);
}
