/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 18:33:59 by schevall          #+#    #+#             */
/*   Updated: 2017/03/14 17:32:05 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	cmd_exit(char **cmds, char ***env)
{
	ft_strdel_tab(cmds);
	ft_strdel_tab(*env);
	exit(EXIT_SUCCESS);
}
