/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedback <feedback@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:35:36 by med               #+#    #+#             */
/*   Updated: 2025/07/02 11:56:48 by feedback         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
    if (str[i] == '-' || str[i] == '+')
       i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit((unsigned char)str[i]))
            return (0);
        i++;
    }
    return (1);
}

static void	valid_error(char *arg)
{
	ft_printf(2,"exit\n");
	ft_printf(2, "bash: exit: %s: numeric argument required\n", arg);
	exit(2);
}

int	ft_exit(char **av)
{
	int exit_status = 0;
	int count = count_word(av);
	if (av[1])
	{
		if (!is_valid_number(av[1]))
			valid_error(av[1]);
		exit_status = ft_atoi(av[1]);
		if (count > 2)
		{
			ft_printf(2, "minishell: exit: too many arguments\n");
			return (1);
		}
  }
	exit(exit_status);
}
