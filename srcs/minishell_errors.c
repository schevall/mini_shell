/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 11:33:35 by schevall          #+#    #+#             */
/*   Updated: 2017/03/16 18:54:25 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	error_getcwd(char *ps)
{
	ft_printf_fd(2, "%s: error retrieving current directory: ", ps);
	ft_printf_fd(2, "getcwd: cannot access parent directories: ");
	ft_printf_fd(2, "No such file or directory\n");
}

int			ms_errors(int error, char *value, char *ps)
{
	if (error == CMD_NOT_FOUND)
		ft_printf_fd(2, "%s: %s: command not found\n", ps, value);
	else if (error == P_DN)
		ft_printf_fd(2, "%s: %s: permission denied\n", ps, value);
	else if (error == NOT_DIR)
		ft_printf_fd(2, "%s: %s: not a directory\n", ps, value);
	else if (error == NO_F)
		ft_printf_fd(2, "%s: %s: No such file or directory\n", ps, value);
	else if (error == IS_DIR)
		ft_printf_fd(2, "%s: %s: is a directory\n", ps, value);
	else if (error == PATH_TROUBLE)
		error_getcwd(ps);
	else if (error == PATH_TOO_LONG || error == NAME_TOO_LONG)
		ft_printf_fd(2, "%s: %s: file name too long\n", ps, value);
	else if (error == MALLOC)
		ft_printf_fd(2, "A malloc error has occured\n");
	else if (error == OPWD_NOT)
		ft_printf_fd(2, "%s: Oldpwd not set\n", ps);
	return (1);
}
