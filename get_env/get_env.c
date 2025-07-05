#include "../minishell.h"

char *get_ekey(char *str, int *index)
{
    int i = 0;
    while (str[i] && str[i] != '=')
        i++;
    *index = i;
    char *key = malloc(i + 1);
    if (!key)
        return NULL;
    strncpy(key, str, i);
    key[i] = '\0';
    return key;
}
char *get_evalue(char *str, int index)
{
    if (str[index] != '=')
        return NULL;
		
    char *value = strdup(str + index + 1);
    return value;
}

t_env *get_env(int ac, char **av, char **env)
{
	t_env *head;
	t_env *tail;
	t_env *curr;
	int (i), (j);

	(void)ac;
	(void)av;
	i = 0;
	head = NULL;
	tail = NULL;
	while (env[i])
	{
		curr = malloc(sizeof(t_env));
		if (!curr)
			return (NULL); 
		j = 0;
		curr->key = get_ekey(env[i], &j);
		curr->value = get_evalue(env[i], j);
		curr->next = NULL;
		if (!head)
		{
			head = curr;
			tail = curr;
		}
		else
		{
			tail->next = curr;
			tail = curr;
		}
		i++;
	}
	return (head);
}
