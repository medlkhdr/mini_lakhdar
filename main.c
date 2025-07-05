#include "minishell.h"
#include <sys/wait.h>
int g_exit_status = 0;
int main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lst_cmd	*cmds;
	t_env		*envir;
	(void)argc;
	(void)argv;
	envir = get_env(argc, argv, envp);
	while (1)
	{
		input = readline("minishell:$ ");
		cmds = parsing(input, envir, &g_exit_status);

		t_cmd *cmd = cmds->head;
		excute_commands(cmd);
		if (cmds)
			free_all(cmds->k);
		free(input);
	}
	return (g_exit_status);
}
