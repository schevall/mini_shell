/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:36:57 by schevall          #+#    #+#             */
/*   Updated: 2017/03/03 14:38:57 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strdel_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_strdel(&tab[i]);
	free(tab);
}
