//
// Created by jiyun on 2023/01/07.
//

#include "minishell.h"

t_info g_info;

t_env	*new_env(char *key, char *value)
{
	t_env *node;

	node = malloc(sizeof(t_env) * 1);
	if (!node)
		ft_error_exit("malloc error", 1);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	save_envs(char *envp[])
{
	t_env	*cur;
	t_env	*head;
	t_env	*tmp;
	char	**path;
	int		i;

	path = ft_split(envp[0], '=');
	cur = new_env(path[0], path[1]);
	head = cur;
	free_arr2(path);
	i = 1;
	while (envp[i] != NULL)
	{
		path = ft_split(envp[i], '=');
		tmp = new_env(path[0], path[1]);
		cur->next = tmp;
		cur = cur-> next;
		i++;
		free_arr2(path);
	}
	g_info.env_lst = head;
}

char	*join_three(char *start, char *end, char *middle)
{
	char *join_two;
	char *ret;

	join_two = ft_strjoin(start, middle);
	ret = ft_strjoin(join_two, end);
	free(join_two);
	return (ret);
}

int get_size(t_env *envs)
{
	int	size;

	size = 0;
	while (envs != NULL)
	{
		envs = envs->next;
		size++;
	}
	return (size);
}

char	**lst_to_arr(t_env *envs)
{
	char **arr;
	t_env *tmp;
	int size;
	int i;

	tmp = envs;
	size = get_size(envs);
	arr = malloc(sizeof(char *) * size + 1);
	if (!arr)
		ft_error_exit("malloc error", 1);;
	i = 0;
	while (i < size && envs != NULL)
	{
		arr[i] = join_three(envs->key, envs->value, "=");
		envs = envs->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd *tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free(cmds->name);
		free_arr2(cmds->content);
		free_rdir_lst(cmds->rdir);
		free(cmds);
		cmds = tmp;
	}
}

void	handle_terminal()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void debug_print_redirs(t_rdir* rdir, int i) {
	if (rdir == NULL)
		return ;
	printf("  redir%d: type=%d here_doc_fd=%d with=%s\n", i, rdir->type, rdir->here_doc_fd, rdir->with);
	debug_print_redirs(rdir->next, ++i);
}


void debug_print_cmds(t_cmd* cmd, int i) {
	if (cmd == NULL)
		return ;
	if (cmd->name != NULL)
		printf("name%d: %s\n", i, cmd->name);
	else
		printf("  name is empty\n");
	if (cmd->content != NULL) {
		for (int i = 0; cmd->content[i] != NULL; i++) {
			printf("  content%d: %s\n", i, cmd->content[i]);
		}
	} else {
		printf("  content is empty\n");
	}
	if (cmd->rdir == NULL)
		printf("  rdir is empty\n");
	debug_print_redirs(cmd->rdir, 0);
	printf("  is_heredoc = %s", cmd->is_heredoc == 0 ? "false\n" : "true\n");
	debug_print_cmds(cmd->next, ++i);
}

int main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmds;

	if (argc != 1)
	{
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		exit(FAIL);
	}
	save_envs(envp);
	while(1)
	{
		cmds = NULL;
		handle_terminal();
		define_signal();
		parse(&cmds);
        debug_print_cmds(cmds, 0);
        printf("------------------------------\n");
		execute(cmds);
		free_cmds(cmds);
	}
}
