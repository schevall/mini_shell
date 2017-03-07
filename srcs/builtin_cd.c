/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 12:56:00 by schevall          #+#    #+#             */
/*   Updated: 2017/03/07 15:36:40 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	parse_cd(char **new_path, char **cmds)
{
	*(new_path) = ft_strdup(cmds[1]);
}

int		cmd_cd(char **cmds, char ***env)
{
	char *cur_path;
	char *new_path;
	char *cmd;
//	char *cmd_char
	size_t size;
	size_t	len;

	ft_printf("init cmd_cd\n");
	if (!getcwd(cur_path, size))
		ft_printf("getcwd error\n");
	ft_printf("cur_path = [%s], size = [%zu]\n", cur_path, size);
	len = ft_strlen(cur_path) - 1;
	ft_printf("cur_path len = [%zu]\n", len);
//	cmd_char = ft_strdup("setenv OLDPWD = ");
//	cmd_char = ft_strjoin_free(cmd, 1, cur_path, 0);
//	cmd = ft_split(cmd_char, " ");
//	cmd_set_env(cmd, env);
	while (cur_path[len] != '/')
		len--;
	new_path = ft_strndup(cur_path, len);
	new_path = ft_strjoin_free(new_path, 1, cmds[1], 0);
	cmd = ft_strdup("setenv PWD = ");
	cmd = ft_strjoin_free(cmd, 1, new_path, 0);
	cmd_set_env(&cmd, env);
	ft_printf("new_path = [%s], size = [%zu]\n", new_path, len);
	chdir((const char*)new_path);
	ft_printf("after chdir new_path = [%s], size = [%zu]\n", new_path, len);
	getcwd(new_path, size);
	ft_printf("after getcw new_path = [%s], size = [%zu]\n", new_path, len);
	exit(1);
	parse_cd(&new_path, cmds);
	return (0);
}
