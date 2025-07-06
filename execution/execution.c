#include "../minishell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>

char *join_path(const char *dir, const char *cmd)
{
	int		len = strlen(dir) + strlen(cmd) + 2;
	char	*full = malloc(len);

  if (!full)
		return (NULL);
			strcpy(full, dir);
	full[strlen(dir)] = '/';          // insert the slash
	strcpy(full + strlen(dir) + 1, cmd);
	return (full);
}

char *get_env_value(char **envp, const char *key)
{
	int		i = 0;
	size_t	key_len = strlen(key);

	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (envp[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

char *get_cmd_path(const char *cmd, char **envp)
{
	char	**dirs;
	char	*path_var;
	char	*full;
	int		i;

	if (strchr(cmd, '/'))	{
		if (access(cmd, X_OK) == 0)
			return strdup(cmd);
		else
			return NULL;
	}

	path_var = get_env_value(envp, "PATH");
	if (!path_var)
		return NULL;

	dirs = ft_split(path_var, ':');
	if (!dirs)
		return NULL;

	for (i = 0; dirs[i]; i++)
	{
		full = join_path(dirs[i], cmd);
		if (full && access(full, X_OK) == 0)
		{
			// ft_free_split(dirs);
			return (full);
		}
		free(full);
	}
	// ft_free_split(dirs);
	return NULL;
}

char *join_vk(const char *key, const char *value)
{
	size_t	len_key = strlen(key);
	size_t	len_val = strlen(value ? value : "");
	char	*str = malloc(len_key + len_val + 2);

	if (!str)
		return (NULL);
	strcpy(str, key);
	str[len_key] = '=';
	strcpy(str + len_key + 1, value ? value : "");
	return str;
}

char **switchtochar(t_env *env)
{
	int		count = 0;
	t_env	*tmp = env;
	char	**envp;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);

	tmp = env;
	int i = -1;
	while (++i < count)
	{
		envp[i] = join_vk(tmp->key, tmp->value);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return NULL;
		}
		tmp = tmp->next;
	}
	envp[count] = NULL;
	return envp;
}
void open_files(t_redir *r)
{
	t_redir *last_in = NULL;
	t_redir *last_out = NULL;

	while (r)
	{
		if (r->index == R_APPEND)
			r->fd = open(r->files, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (r->index == R_OUT)
			r->fd = open(r->files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->index == R_IN)
			r->fd = open(r->files, O_RDONLY);
		if (r->index == R_IN || r->index == R_HEREDOC)
			last_in = r;
		else if (r->index == R_OUT || r->index == R_APPEND)
			last_out = r;
		r = r->next;
	}

	if (last_in && last_in->fd >= 0)
		dup2(last_in->fd, STDIN_FILENO);
	if (last_out && last_out->fd >= 0)
		dup2(last_out->fd, STDOUT_FILENO);
}

void excute_commands(t_cmd *cmds)
{
	t_cmd *cmd;
	cmd = cmds;
	cmd->fds[1] = dup(STDOUT_FILENO);
	cmd->fds[0] = dup(STDIN_FILENO);
	open_files(cmd->files);
	if (strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->args);
	else if(strcmp(cmd->args[0], "export")==0)
		ft_export(cmd);
	else if(strcmp(cmd->args[0] , "env") == 0)
		ft_env(*cmd->env);
	else if(strcmp(cmd->args[0] , "cd") == 0)
		ft_cd(cmd);
	else
	{
		pid_t pid = fork();
		if(pid == 0)
		{
			char *path = get_cmd_path(cmd->args[0], cmd->envp);
			execve(path, cmd->args, cmd->envp);
		}
		else
			wait(NULL);
	}

	dup2(cmd->fds[0], STDIN_FILENO);
	dup2(cmd->fds[1], STDOUT_FILENO);
	close(cmd->fds[0]);
	close(cmd->fds[1]);
}