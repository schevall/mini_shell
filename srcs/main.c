/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 17:09:53 by schevall          #+#    #+#             */
/*   Updated: 2017/03/16 18:54:14 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	funct_tab(char **cmds, char ***env)
{
	if (!ft_strcmp(cmds[0], "\n"))
		return ;
	else if (!ft_strcmp(cmds[0], "env"))
		cmd_env(cmds, &(*env));
	else if (!ft_strcmp(cmds[0], "echo"))
		cmd_echo(cmds, env);
	else if (!ft_strcmp(cmds[0], "setenv"))
		cmd_set_env(cmds, &(*env));
	else if (!ft_strcmp(cmds[0], "unsetenv") && cmds[1])
		cmd_unset_env(cmds, &(*env));
	else if (!ft_strcmp(cmds[0], "cd"))
		cmd_cd(cmds, &(*env));
	else if (!ft_strcmp(cmds[0], "exit"))
		cmd_exit(cmds, env);
	else if (!ft_strcmp(cmds[0], "pwd"))
		cmd_pwd(env);
	else
		return ;
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "\n"))
		return (1);
	else if  (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "setenv"))
		return (1);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else
		return (0);
}

static void	run_cmds(char **cmds, char ***env)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (can_access(cmds, 0) == 1)
			execve(cmds[0], cmds, *env);
		else if (is_pathed(&path, cmds[0], *env) == -1)
		{
			execve(path, cmds, *env);
			ft_strdel(&path);
		}
		else
			ms_errors(CMD_NOT_FOUND, cmds[0], "minishell");
		exit(EXIT_SUCCESS);
	}
	else
		wait(NULL);
}

static char	**parse(char **cmds, char *line)
{
	if (!*line)
	{
		cmds = (char**)ft_memalloc(sizeof(char*) * 2);
		cmds[0] = (char*)ft_memalloc(2);
		cmds[0][0] = '\n';
		return (cmds);
	}
	else
		return (ft_strsplit_whitespace(line));
}

int			main(int ac, char **av, const char **env_ini)
{
	char **env;
	char **cmds;
	char *line;
	char *prompt;

	(void)ac;
	(void)av;
	env = ft_strdup_tab(env_ini);
	get_prompt(&prompt, env);
	while (ft_printf("%s", prompt) && get_next_line(0, &line) > 0)
	{
		cmds = parse(cmds, line);
		if (is_builtin(cmds[0]))
			funct_tab(cmds, &env);
		else if (!is_path(cmds[0]))
			run_cmds(cmds, &env);
		ft_strdel(&line);
		ft_strdel_tab(cmds);
		get_prompt(&prompt, env);
	}
	ft_strdel_tab(env);
	return (0);
}
