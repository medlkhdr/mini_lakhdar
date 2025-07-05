/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:28:20 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 16:28:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	arg_count(char **av)
{
	int	count;

	count = 0;
	while (NULL != av[count])
		count++;
	return (count);
}
int check(char *str)
{
	int i;

	i = 0;
	if(!str[i])
		return 0;
	if(str[i] == '-')
		i++;
	while(str[i] == 'n')
		i++;
	if(!str[i])
		return 1;
	return 0;
}

int	ft_echo(char **av)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (arg_count(av) == 1)
		return (ft_printf(STDOUT_FILENO, "\n"));
	if (arg_count(av) > 1)
	{
		while (ft_strcmp(av[i], "-n") == 0 || check(av[i]))
		{
			option = 1;
			i++;
		}
		while (av[i] != NULL)
		{
			ft_printf(STDOUT_FILENO, "%s", av[i]);
			if (av[i + 1] != NULL)
				ft_printf(STDOUT_FILENO, " ");
			i++;
		}
	}
	if (option == 0)
		ft_printf(STDOUT_FILENO, "\n");
	return (0);
}
