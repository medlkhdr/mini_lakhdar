#include "../minishell.h"

t_lst_cmd *parsing(char *input , t_env *env , int *g_exit_status)
{
	t_lst_hk	*x;
	t_lst_token	*lst_token;
	t_lst_cmd *lst;

	x = malloc(sizeof(t_lst_hk));
	if (!x)
		return (NULL);
	x->head = NULL;
	trim_space(&input);
	lst_token = tokenizer(input, x);
	if ((!lst_token || !lst_token->head) || syntax_analyser(lst_token) == 2)
	{
		*g_exit_status = 2;
		free_all(x);
		return (NULL);
	}
	expander(lst_token, x ,env, *g_exit_status);
	lst = fill_struct(lst_token, x ,env,  g_exit_status);
	lst->k = x;
	return (lst);
}
