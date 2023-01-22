#include "minishell.h"

int is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->name, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->name, "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd);
	return (0);
}

int	single_builtin(t_cmd *cmd)
{
	int	p_in;
	int	p_out;

	p_in = dup(STDIN_FILENO);
	p_out = dup(STDOUT_FILENO);
	ft_rdir(cmd->rdir);
	if (ft_strcmp(cmd->name, "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->name, "cd") == 0)
		ft_cd(cmd);
	else if (ft_strcmp(cmd->name, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->name, "export") == 0)
		ft_export(cmd);
	else if (ft_strcmp(cmd->name, "unset") == 0)
		ft_unset(cmd);
	else if (ft_strcmp(cmd->name, "env") == 0)
		ft_env(cmd);
	else if (ft_strcmp(cmd->name, "exit") == 0)
		ft_exit(cmd);
	dup2(p_in, STDIN_FILENO);
	dup2(p_out, STDOUT_FILENO);
	return (0);
}

int	check_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (1);
	return (0);
}