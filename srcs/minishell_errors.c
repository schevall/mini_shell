/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:33:35 by schevall          #+#    #+#             */
/*   Updated: 2017/03/10 18:37:17 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	error_getcwd(char *value)
{
	ft_printf_fd(2, "%s: error retrieving current directory: ", value);
	ft_printf_fd(2, "getcwd: cannot access parent directories: ");
	ft_printf_fd(2, "No such file or directory\n");
}

int		minishell_errors(int error, char *value, char *ps)
{
	if (error == CMD_NOT_FOUND)
		ft_printf_fd(2, "%s: %s: command not found\n", ps, value);
	else if (error == PERM_DENIED)
		ft_printf_fd(2, "%s: %s: permission denied\n", ps, value);
	else if (error == NOT_DIR)
		ft_printf_fd(2, "%s: %s: not a directory\n", ps, value);
	else if (error == NOT_FOUND)
		ft_printf_fd(2, "%s: %s: not such file or  directory\n", ps, value);
	else if (error == IS_DIR)
		ft_printf_fd(2, "%s: %s: is a directory\n", ps, value);
	else if (error == PATH_TROUBLE)
		error_getcwd(value);
	else if (error == PATH_TOO_LONG || error == NAME_TOO_LONG)
		ft_printf_fd(2, "%s: %s: file name too long\n", ps, value);
	return (1);
}
