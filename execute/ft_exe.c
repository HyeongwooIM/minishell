/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woohyeong <woohyeong@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:30:00 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/25 15:52:04 by woohyeong        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_make_path(char *paths, char *cmd)
{
	char	*part_path;
	char	*res;

	part_path = ft_strjoin(paths, "/");
	if (!part_path)
		ft_error_exit("malloc error", 1);
	res = ft_strjoin(part_path, cmd);
	if (!res)
		ft_error_exit("malloc error", 1);
	free(part_path);
	return (res);
}

char	*no_path(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == 0)
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
			ft_error_exit("is a directory", 1);
		return (cmd);
	}
	ft_putstr_fd(cmd, 1);
	ft_error_exit("No such file or directory", 1);
	return (0);
}

char	*yes_path(char *cmd, t_env *env)
{
	char		*path;
	char		**paths;
	struct stat	buf;
	int			i;

	if (*cmd == 0)
		return (0);
	paths = ft_split(env->value, ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_make_path(paths[i], cmd);
		if (stat(path, &buf) == 0)
		{
			if ((buf.st_mode & S_IFMT) == S_IFDIR)
			{
				ft_putstr_fd(path, 2);
				ft_putstr_fd("is a directory\n", 2);
			}
			return (path);
		}
		free(path);
	}
	return (0);
}

char	*find_path(char *cmd, t_env *env, int *is_path)
{
	int	i;

	*is_path = 0;
	env = find_env("PATH");
	if (!env)
		return (no_path(cmd));
	else
	{
		*is_path = 1;
		return (yes_path(cmd, env));
	}
	return (0);
}

void	ft_exe(t_cmd *cmd, t_env *env)
{
	char	**content;
	char	*path;
	char	**envp;
	int		is_path;

	path = find_path(cmd->name, env, &is_path);
	if (!path)
	{
		path = cmd->name;
		if (!is_path)
		{
			content = ft_strjoin2(path, cmd->content);
			envp = lst_to_arr(env);
			if (execve(path, content, envp) == -1)
			{
				ft_putstr_fd(cmd->name, 2);
				ft_error_exit("No such file or directory", 1);
			}
		}
	}
	content = ft_strjoin2(path, cmd->content);
	envp = lst_to_arr(env);
	if (execve(path, content, envp) == -1)
		ft_command_error(cmd->name);
}
