/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:15:54 by schevall          #+#    #+#             */
/*   Updated: 2017/03/06 14:02:58 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	cmd_echo_print(char **cmds, int i)
{
	while (cmds[i])
		{
			ft_printf("%s", cmds[i]);
			if (cmds[i + 1])
				ft_printf(" ");
			i++;
		}
}

void	cmd_echo(char **cmds)
{
	int i;

	i = 1;
	ft_printf("init cmd_echo\n");
	if (!ft_strcmp(cmds[1], "-n"))
	{
		i++;
		cmd_echo_print(cmds, i);
	}
	else
	{
		cmd_echo_print(cmds, i);
		ft_printf("\n");
	}
}

