/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_get_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 12:09:34 by schevall          #+#    #+#             */
/*   Updated: 2017/03/14 18:20:46 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

char	*get_prompt(char **prompt, char ***env)
{
	char	*path;
	char	*new_prompt;
	int		len;
	int		start;

	if (*prompt)
		ft_strdel(prompt);
	path = ft_get_env("PWD", env);
	len = ft_strlen(path) - 1;
	start = len;
	while (start && path[start] != '/')
		start--;
	new_prompt = ft_strsub(path, start + 1, len);
	ft_strdel(&path);
	new_prompt = ft_strjoin_free(new_prompt, 1, " $> ", 0);
	return (new_prompt);
}
