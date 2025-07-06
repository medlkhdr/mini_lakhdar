/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:48:00 by marvin            #+#    #+#             */
/*   Updated: 2025/06/24 16:48:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_value(t_env *env, char *key)
{
	t_env	*curr;

	if (!env)
		ft_printf(STDERR_FILENO, "no environement");
	if (!key)
		return (NULL);
	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
				return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (NULL);
}

void	update_val(t_env *env, char *key, char *new_val)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(new_val);
			return ;
		}
		curr = curr->next;
	}
}

char *resolve_cd_target(t_cmd *cmd)
{
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		return get_value(*cmd->env, "HOME");
	else
		return ft_strdup(cmd->args[1]);
}

char *cd_to_path(t_cmd *cmd, char *oldpwd)
{
	char *target;
	char *pwd;
	
	target = resolve_cd_target(cmd);
	if (!target || chdir(target) == -1)
	{
		if (!cmd->args[1] )
			ft_printf(2, "bash: cd: HOME not set\n");
		else
			ft_printf(STDERR_FILENO, "bash: cd: %s: %s\n", cmd->args[1], strerror(errno));
		free(oldpwd);
		free(target);
		return (NULL);
	}
	free(target);
	pwd = getcwd(NULL, 0);
	return (pwd);
}
