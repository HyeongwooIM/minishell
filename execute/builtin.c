#include "../minishell.h"

int	single_builtin(t_cmd *cmd, t_env env)
{
	if (ft_strcmp(cmd->name, "echo"))
		ft_echo(cmd);
	else if (ft_strcmp(cmd->name, "cd"))
		ft_cd(cmd);
	else if (ft_strcmp(cmd->name, "pwd"))
		ft_pwd();
	else if (ft_strcmp(cmd->name, "export"))
		ft_export(cmd);
	else if (ft_strcmp(cmd->name, "unset"))
		ft_unset(cmd);
	else if (ft_strcmp(cmd->name, "env"))
		ft_env(cmd);
	else if (ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd);
	return (0);
}

int	check_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo"))
		return (1);
	else if (ft_strcmp(cmd_name, "cd"))
		return (1);
	else if (ft_strcmp(cmd_name, "pwd"))
		return (1);
	else if (ft_strcmp(cmd_name, "export"))
		return (1);
	else if (ft_strcmp(cmd_name, "unset"))
		return (1);
	else if (ft_strcmp(cmd_name, "env"))
		return (1);
	else if (ft_strcmp(cmd_name, "exit"))
		return (1);
	return (0);
}