/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_get_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 12:09:34 by schevall          #+#    #+#             */
/*   Updated: 2017/03/20 18:21:49 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

static void	make_prompt(char **new_prompt, char **env)
{
	char *target;

	if (!(target = *ft_get_env("PWD", env)))
	{
		if (!(*new_prompt = ft_strdup("")))
			ms_errors(MALLOC, NULL, "minishell");
	}
	else
	{
		if (!(*new_prompt = ft_strdup(*ft_get_env("PWD", env) + 4)))
			ms_errors(MALLOC, NULL, "minishell");
	}
}

void		get_prompt(char **prompt, char **env)
{
	int		len;
	int		start;
	char	*new_prompt;
	char	*target;

	if (*prompt)
		ft_strdel(prompt);
	make_prompt(&new_prompt, env);
	len = ft_strlen(new_prompt);
	start = len;
	while (start && new_prompt[start] != '/')
		start--;
	if (!strchr(new_prompt, '/') || !ft_strcmp(new_prompt, "/"))
		start = -1;
	if (!(*prompt = ft_strsub(new_prompt, start + 1, len)))
		ms_errors(MALLOC, NULL, "minishell");
	ft_strdel(&new_prompt);
	if (!(*prompt = ft_strjoin_free(*prompt, 1, " $> ", 0)))
		ms_errors(MALLOC, NULL, "minishell");
}
