/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 17:09:53 by schevall          #+#    #+#             */
/*   Updated: 2017/03/10 18:37:10 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	funct_tab(char **cmds, char ***env)
{
	if (!ft_strcmp(cmds[0], "env"))
		cmd_env(cmds, &(*env));
	else if (!ft_strcmp(cmds[0], "echo"))
		cmd_echo(cmds);
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
	else if (!ft_strcmp(cmds[0], "\n"))
		return ;
	else
		return ;
}

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "env"))
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
	else if (!ft_strcmp(cmd, "\n"))
		return (1);
	else
		return (0);
}

char	**get_potentials_paths(char **env, char *cmd)
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
		paths[i] = ft_strjoin_free(paths[i], 1 , "/", 0);
		paths[i] = ft_strjoin_free(paths[i], 1, cmd, 0);
		i++;
	}
	return (paths);
}

int		can_access(char **potentials_path, int i)
{
	if (!ft_strchr(potentials_path[i], '/'))
			return (0);
	if (access(potentials_path[i], F_OK) != -1)
	{
		if (!access(potentials_path[i], X_OK))
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
	while (potentials_path[i])
	{
		if (can_access(potentials_path, i) == 1)
		{
			*path = ft_strdup(potentials_path[i]);
			break ;
		}
		i++;
	}
	if (potentials_path[i])
		i = -1;
	ft_strdel_tab(potentials_path);
	return (i);
}

void	run_cmds(char **cmds, char ***env)
{
	pid_t pid;
	char *path;

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
			minishell_errors(CMD_NOT_FOUND, cmds[0], "minishell");
		exit(EXIT_SUCCESS);
	}
	else
		wait(NULL);
}

void	parse(char ***cmds, char *line)
{
//	ft_printf("line = [%s]\n", line);
//	ajouter au parsing de quoi spliter dans tout les cas = tab ou \n
	*cmds = ft_strsplit(line, ' ');
	if (!(*cmds[0]))
		*(cmds[0]) = ft_strdup("\n");
//	ft_printf("cmds[0] = [%s]\n", *cmds[0]);
}

int		check_path_errors_aux(int j, char *buf, char *path)
{
		if (j > NAME_MAX)
			return (minishell_errors(NAME_TOO_LONG, path, "minishell"));
		if (access(buf, F_OK) == -1)
		{
			ft_printf("access F_OK = -1\n");
			return (minishell_errors(NOT_FOUND, buf, "minishell"));
		}
		if (access(buf, X_OK) == -1)
			return (minishell_errors(PERM_DENIED, buf, "minishell"));
		return (0);
}

int		check_path_errors(char *path)
{
	char *buf;
	int i;
	int j;

	i = 0;
	buf = ft_memalloc(PATH_MAX);
	if (ft_strlen(path) >= PATH_MAX)
		return (minishell_errors(PATH_TOO_LONG, NULL, "minishell"));
	while (path[i])
	{
		j = 0;
		while (path[i] && path[i] != '/')
		{
			buf[i] = path[i];
			j++;
			i++;
		}
		if (path[i] == '/')
			buf[i] = path[i];
		if (check_path_errors_aux(j, buf, path))
			return (1);
		i++;
	}
	return (0);
}

int		find_slash(char *path)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int		is_path(char *path)
{
	t_stat buf;

	if (!find_slash(path))
		return (0);
	if (stat(path, &buf) == -1)
		return (check_path_errors(path));
	else if (S_ISDIR(buf.st_mode))
		return (minishell_errors(IS_DIR, path, "minishell"));
	else if (access(path, X_OK) != -1)
		return (minishell_errors(PERM_DENIED, path, "minishell"));
	return (0);
}

int		main(int ac, char **av, const char **env_ini)
{
	char **env;
	char **cmds;
	char *line;
	char *prompt;

	(void)ac;
	(void)av;
	env = ft_strdup_tab(env_ini);
	signal(SIGINT, SIG_IGN);
	prompt = get_prompt(&prompt, &env);
	while (ft_printf("%s", prompt) && get_next_line(0, &line) > 0)
	{
		parse(&cmds, line);
		if (is_builtin(cmds[0]))
			funct_tab(cmds, &env);
		else if (!is_path(cmds[0]))
			run_cmds(cmds, &env);
		ft_strdel(&line);
		ft_strdel_tab(cmds);
		prompt = get_prompt(&prompt, &env);
	}
	ft_strdel(&prompt);
	ft_strdel_tab(env);
	return (0);
}
