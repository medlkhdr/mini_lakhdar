/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:30:13 by mohabid           #+#    #+#             */
/*   Updated: 2025/07/04 12:21:30 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env)
{
	t_env *curr;

	curr = env;
	while (curr)
	{
		if(curr->value[0])
			ft_printf(STDOUT_FILENO, "%s=%s\n", curr->key , curr->value);
		curr = curr->next;
	}
	return (0);
}
