/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:12:18 by schevall          #+#    #+#             */
/*   Updated: 2017/03/10 18:37:26 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>

typedef void (*sighandler_t)(int);
typedef struct stat t_stat;
typedef struct dirent t_dir;

void	*cmd_env(char **cmds, char ***env);
void	cmd_echo(char **cmds);
void	cmd_set_env(char **cmds, char ***env);
void	cmd_unset_env(char **cmds, char ***env);
int		cmd_cd(char **cmds, char ***env);
void	cmd_exit(char **cmds, char ***env);
void	cmd_pwd(char ***env);
char	*ft_get_env(char *name, char ***env);
char	*get_prompt(char **prompt, char ***env);
int		minishell_errors(int error, char *value, char *ps);

enum
{
	CMD_NOT_FOUND,
	PERM_DENIED,
	NOT_DIR,
	NOT_FOUND,
	IS_DIR,
	PATH_TROUBLE,
	PATH_TOO_LONG,
	NAME_TOO_LONG,
};

#endif
