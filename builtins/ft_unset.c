#include "../minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i = 0;

	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_node(t_env **env, const char *key)
{
	t_env	*prev = NULL;
	t_env	*curr = *env;

	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;

			free(curr->key);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_cmd *cmd)
{
	t_env	**env = cmd->env;
	char	**args = cmd->args;
	int		i = 1;

	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			ft_printf(STDERR_FILENO, "bash: unset: `%s`: not a valid identifier\n", args[i]);
		else
			remove_env_node(env, args[i]);
		i++;
	}
	return (0);
}
