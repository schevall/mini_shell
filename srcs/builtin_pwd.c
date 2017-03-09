/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:01:21 by schevall          #+#    #+#             */
/*   Updated: 2017/03/09 19:05:30 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	cmd_pwd(char ***env)
{
	int i;

	i = 0;
	if (!env)
		return ;
	while ((*env)[i])
	{
		if (!ft_strncmp("PWD", (*env)[i], 3))
		{
			ft_printf("%s\n", (*env)[i] + 4);
			break ;
		}
		i++;
	}
}
