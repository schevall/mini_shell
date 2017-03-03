/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 11:11:27 by schevall          #+#    #+#             */
/*   Updated: 2017/03/02 15:45:59 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

const char *quisuis;

int		main()
{
	pid_t	father;

	quisuis = "Le pere";
	father = fork();
	if (father == 0)
	{
		father = fork();
		if (father == 0)
		{
			wait(NULL);
			quisuis = "Le petit fils";
			printf("je suis %s\n", quisuis);
		}
		else
		{
			wait(NULL);
			quisuis = "Le fils";
			printf("je suis %s\n", quisuis);
		}
	}
	else
	{
		wait(NULL);
		printf("je suis %s\n", quisuis);
	}
}


