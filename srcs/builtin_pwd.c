/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:01:21 by schevall          #+#    #+#             */
/*   Updated: 2017/03/15 14:52:44 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	cmd_pwd(char ***env)
{
	char *path;

	if (!(path = getcwd(NULL, 0)))
		minishell_errors(PATH_TROUBLE, path, "pwd");
	else
	{
		ft_printf("%s\n", path);
		ft_strdel(&path);
	}
}
