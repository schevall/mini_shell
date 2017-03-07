/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:12:18 by schevall          #+#    #+#             */
/*   Updated: 2017/03/07 15:36:04 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/types.h>
# include <signal.h>


typedef struct dirent t_dir;

void	cmd_env(char **env);
void	cmd_echo(char **cmds);
void	cmd_set_env(char **cmds, char ***env);
void	cmd_unset_env(char **cmds, char ***env);
int		cmd_cd(char **cmds, char ***env);

#endif
