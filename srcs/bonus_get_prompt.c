/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_get_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 12:09:34 by schevall          #+#    #+#             */
/*   Updated: 2017/03/16 18:54:28 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	get_prompt(char **prompt, char **env)
{
	int		len;
	int		start;
	char	*new_prompt;

	if (*prompt)
		ft_strdel(prompt);
	if (!(new_prompt = ft_strdup(*ft_get_env("PWD", env) + 4)))
		new_prompt = ft_strdup("");
	len = ft_strlen(new_prompt);
	start = len;
	while (start && new_prompt[start] != '/')
		start--;
	if (!strchr(new_prompt, '/') || !ft_strcmp(new_prompt, "/"))
		start = -1;
	*prompt = ft_strsub(new_prompt, start + 1, len);
	ft_strdel(&new_prompt);
	*prompt = ft_strjoin_free(*prompt, 1, " $> ", 0);
}
