/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:12:18 by schevall          #+#    #+#             */
/*   Updated: 2017/03/20 16:01:55 by schevall         ###   ########.fr       */
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

typedef struct stat	t_stat;
typedef struct dirent	t_dir;

void	run_cmds(char **cmds, char ***env, char *ps);
void	cmd_env(char **cmds, char ***env);
void	cmd_echo(char **cmds, char ***env);
void	cmd_set_env(char **cmds, char ***env);
void	cmd_unset_env(char **cmds, char ***env);
int		cmd_cd(char **cmds, char ***env);
int		cmd_cd_cases(char *type, char ***env, char *cur_path);
int		change_path(char *path, char ***env);
void	get_backward(char **path);
int		cd_error(char **cmds, char ***env);
void	cmd_exit(char **cmds, char **env, char *exit, char *prompt);
void	cmd_pwd(char ***env);
void	format_cmd_for_setenv(char *name, char *value, char ***env);
int		ft_is_env(char *name, char ***env);
char	**ft_get_env(char *name, char **env);
void	ft_sigign_newprompt(int signal);
void	get_prompt(char **prompt, char **env);
int		ms_errors(int error, char *value, char *ps);
int		can_access(char **potentials_path, int i);
int		is_pathed(char **path, char *cmd, char **env);
int		is_path(char *path);
int		check_path_errors(char *path);

enum
{
	CMD_NOT_FOUND,
	P_DN,
	NOT_DIR,
	NO_F,
	IS_DIR,
	PATH_TROUBLE,
	PATH_TOO_LONG,
	NAME_TOO_LONG,
	MALLOC,
	OPWD_NOT,
};

#endif
