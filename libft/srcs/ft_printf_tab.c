/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 16:40:02 by schevall          #+#    #+#             */
/*   Updated: 2017/03/08 17:28:57 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_tab(char *name, char **tab)
{
	int i;

	ft_printf("\ninit print_tab, name = [%s]\n\n", name);
	i = 0;
	while (tab[i])
	{
		ft_printf("ligne n.[%d] = [%s]\n", i, tab[i]);
		i++;
	}
	ft_printf("\nend printtab\n\n");
}
