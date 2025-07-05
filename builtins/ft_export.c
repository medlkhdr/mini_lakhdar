/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlakhdar <mlakhdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:54:21 by med               #+#    #+#             */
/*   Updated: 2025/07/03 16:33:53 by mlakhdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i = 0;

	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*get_key(const char *arg)
{
	int		len = 0;

	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len));
}

char	*get_value(const char *arg)
{
	char	*equal = ft_strchr(arg, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

void	insert_sorted(t_env **env, t_env *new_node)
{
	t_env	*prev = NULL;
	t_env	*curr = *env;

	while (curr && ft_strcmp(curr->key, new_node->key) < 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
	{
		new_node->next = *env;
		*env = new_node;
	}
	else
	{
		prev->next = new_node;
		new_node->next = curr;
	}
}

void	add_or_update_env(t_env **env, char *arg)
{
	char	*key = get_key(arg);
	char	*value = get_value(arg);
	t_env	*curr = *env;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (value)
			{
				free(curr->value);
				curr->value = value;
			}
			free(key);
			return;
		}
		curr = curr->next;
	}
	t_env *new_node = malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value ? value : ft_strdup("");
	new_node->next = NULL;
	insert_sorted(env, new_node);
}

void	add_update(t_cmd **cmd)
{
	t_env *env = *(*cmd)->env;
	char **args = (*cmd)->args;
	int i = 1;

	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_printf(STDERR_FILENO, "bash: export: `%s`: not a valid identifier\n", args[i]);
		}
		else
		{
			add_or_update_env(&env, args[i]);
		}
		i++;
	}
	*(*cmd)->env = env;
}

int	ft_export(t_cmd *cmd)
{
	int ac = count_word(cmd->args);
	t_env *curr = *cmd->env;

	if (ac == 1)
	{
		while (curr)
		{
			ft_printf(STDOUT_FILENO, "declare -x %s", curr->key);
			if (curr->value)
				ft_printf(STDOUT_FILENO, "=\"%s\"", curr->value);
			ft_printf(STDOUT_FILENO, "\n");
			curr = curr->next;
		}
	}
	else
		add_update(&cmd);
	return (0);
}
