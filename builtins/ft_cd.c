#include "../minishell.h"

int arg_count(char **av)
{
	int	count;
	int	i;
	
	i = 0;
	count = 0;
	while (av[i])
	{
		count++;
		i++;
	}
	return (count);
}

static void update_pwd_vars(t_env *env, char *oldpwd, char *pwd)
{
	if (oldpwd)
		update_val(env, "OLDPWD", oldpwd);
	if (pwd)
		update_val(env, "PWD", pwd);
	free(oldpwd);
	free(pwd);
}

int	ft_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;
	int		count;
	
	if (!cmd || !cmd->env || !(*cmd->env))
		return (-1);
	count = arg_count(cmd->args);
	if (count > 2)
	{
		ft_printf(STDERR_FILENO, "cd: too many arguments\n");
		return (-1);
	}
	oldpwd = getcwd(NULL, 0);
	pwd = cd_to_path(cmd, oldpwd);
	if (!pwd)
		return (-1);
	update_pwd_vars(*cmd->env, oldpwd, pwd);
	return (0);
}
