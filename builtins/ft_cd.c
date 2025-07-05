#include "../minishell.h"

static char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*get_home(t_env *env)
{
	char	*home = get_env_value(env, "HOME");
	if (!home)
	{
		ft_printf(STDERR_FILENO, "bash: cd: HOME not set\n");
		return (NULL);
	}
	return (ft_strdup(home));
}

static void	update_env(t_env *envi, char *key, const char *new_value)
{
	t_env *env;

	env = envi;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_value);
			return;
		}
		env = env->next;
	}
}

static char	*get_target_path(int ac, char *path, t_env *env)
{
	if (ac == 1 || path == NULL || ft_strcmp(path, "~") == 0)
		return (get_home(env));
	return (ft_strdup(path));
}

int	count_word(char **str)
{
	int	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	ft_cd(t_cmd *cmd)
{
	char	*target_p;
	char	*oldpwd;
	char	*newpwd;
	int		ac;
	t_env	*env = *cmd->env;

	ac = count_word(cmd->args);
	if (ac > 2)
	{
		ft_printf(STDERR_FILENO, "bash: cd: too many arguments\n");
		return (-1);
	}
	if (ac == 2 && ft_strcmp(cmd->args[1], ".") == 0)
		return (0);

	oldpwd = getcwd(NULL, 0);

	target_p = get_target_path(ac, (ac == 2 ? cmd->args[1] : NULL), env);
	if (!target_p)
	{
		free(oldpwd);
		return (-1);
	}

	if (chdir(target_p) == -1)
	{
		ft_printf(STDERR_FILENO, "bash: cd: %s: %s\n", target_p, strerror(errno));
		free(target_p);
		free(oldpwd);
		return (-1);
	}

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		ft_printf(STDERR_FILENO, "bash: cd: error retrieving current directory\n");
		newpwd = ft_strdup("");
	}

	update_env(env, "OLDPWD", oldpwd ? oldpwd : "");
	update_env(env, "PWD", newpwd);

	free(oldpwd);
	free(newpwd);
	free(target_p);
	return (0);
}
