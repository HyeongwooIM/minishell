/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:55:18 by woohyeong         #+#    #+#             */
/*   Updated: 2023/01/26 14:44:54 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_pwd(char	*cwd)
{
	char	*cwd_temp;
	t_env	*env_pwd;
	t_env	*env_oldpwd;

	env_pwd = find_env_add("PWD");
	env_oldpwd = find_env_add("OLDPWD");
	if (env_oldpwd->value)
		free(env_oldpwd->value);
	env_oldpwd->value = env_pwd->value;
	env_pwd->value = ft_strdup(cwd);
	if (!env_pwd->value)
		ft_error_exit("1-malloc error", 1);
}

void	ft_cd(t_cmd	*cmd)
{
	char	get_cwd[PATH_MAX];
	char	*cd_path;
	char	*path;

	if (!cmd)
		exit(1);
	path = *cmd->content;
	if (cmd && cmd->content == 0)
		exit(1);
	if (chdir(path))
		exit(1);
	if (!getcwd(get_cwd, PATH_MAX))
		exit(1);
	edit_pwd(get_cwd);
}
