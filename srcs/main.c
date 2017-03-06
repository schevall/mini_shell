/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 17:09:53 by schevall          #+#    #+#             */
/*   Updated: 2017/03/06 19:13:04 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	funct_tab(char **cmds, char ***env)
{
	ft_printf("init funct_tab, cmds[0] = [%s]\n", cmds[0]);
	if (!ft_strcmp(cmds[0], "env"))
		cmd_env(*env);
	else if (!ft_strcmp(cmds[0], "echo"))
		cmd_echo(cmds);
	else if (!ft_strcmp(cmds[0], "setenv"))
		cmd_set_env(cmds, env);
	else if (!ft_strcmp(cmds[0], "unsetenv"))
		cmd_unset_env(cmds, env);
	else if (!ft_strcmp(cmds[0], "\n"))
		return ;
	else
		return ;
}

int		is_builtin(char *cmd)
{
	ft_printf("init is_builtin, cmd = [%s]\n", cmd);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "setenv"))
		return (1);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (1);
	else if (!ft_strcmp(cmd, "\n"))
		return (1);
	else
		return (0);
}

char	**get_potentials_paths(char **env,char *cmd)
{
	char **paths;
	int i;

	i = 0;
	while (ft_strncmp("PATH", *env, 4))
		env++;
	*env += 4;
	paths = ft_strsplit(*env, ':');
	while (paths[i])
	{
		ft_printf("paths[i] = [%s]\n", paths[i]);
		paths[i] = ft_strjoin_free(paths[i], 1 , "/", 0);
		paths[i] = ft_strjoin_free(paths[i], 1, cmd, 0);
		ft_printf("paths[i] = [%s]\n", paths[i]);
		i++;
	}
	return (paths);
}

int		can_access(char **potentials_path, int i)
{
	if (access(potentials_path[i], F_OK) != -1)
	{
		if (access(potentials_path[i], X_OK) != -1)
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}

int		is_pathed(char **path, char *cmd, char **env)
{
	char **potentials_path;
	int i;
	
	i = 0;
	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (0);
	potentials_path = get_potentials_paths(env, cmd);
//	ft_printf("potentials_path[0] = [%s]\n", potentials_path[0]);
	while (potentials_path[i])
	{
//		ft_printf("boucle, potentials_path = [%s]\n", potentials_path[i]);
		if (can_access(potentials_path, i) == 1)
			break ;
		i++;
	}
	if (potentials_path[i])
	{
		*path = ft_strdup(potentials_path[i]);
		i = -1;
	}
	ft_strdel_tab(potentials_path);
	ft_printf("i = %d rigth_path = [%s]\n", i, *path);
	return (i);
}

void	run_cmds(char **cmds, char ***env)
{
	pid_t pid;
	char *path;

	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(cmds[0]))
			funct_tab(cmds, env);
		else if (is_pathed(&path, cmds[0], *env) == -1)
		{
			if (execve(path, cmds, *env) == -1)
				ft_printf("exec error\n");
			ft_strdel(&path);
		}
		else
			ft_printf("command not found: %s\n", cmds[0]);
	}
	else
		wait(NULL);
}

void	parse(char ***cmds, char *line)
{
//	ft_printf("line = [%s]\n", line);
	*cmds = ft_strsplit(line, ' ');
	if (!(*cmds[0]))
		*(cmds[0]) = ft_strdup("\n");
//	ft_printf("cmds[0] = [%s]\n", *cmds[0]);
}

int		main(int ac, char **av, const char **env_ini)
{
	char **env;
	char **cmds;
	char *line;

	(void)ac;
	(void)av;
	env = ft_strdup_tab(env_ini);
	while (ft_printf("$> ") && get_next_line(0, &line))
	{
		parse(&cmds, line);
		run_cmds(cmds, &env);
		ft_strdel(&line);
		ft_strdel_tab(cmds);
	}
	ft_strdel_tab(env);
	return (0);
}
