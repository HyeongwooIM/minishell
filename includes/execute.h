/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:15:54 by him               #+#    #+#             */
/*   Updated: 2023/01/27 12:01:31 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <sys/stat.h>

typedef struct s_token	t_token;
typedef struct s_rdir	t_rdir;
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

//ft_strjoin2.c
char	**ft_strjoin2(char *str, char **arr);

// find_env_add.c
t_env	*find_env_add(char *key);

// ft_error_exit.c
void	ft_error_exit(char *str, int error_no);
void	ft_command_error(char *cmd);

// ft_builtin.c
void	single_builtin(t_cmd *cmd);
int		check_builtin(char *cmd_name);
int		is_builtin(t_cmd *cmd);

// find_env.c
t_env	*find_env(char *key);

// ft_strcmp.c
int		ft_strcmp(const char *str1, const char *str2);

// ft_execute.c
void	execute(t_cmd	*cmd);

// ft_rdir.c
int		ft_rdir(t_rdir *rdir);

// ft_exit.c
void	ft_exit(t_cmd	*cmd);

// ft_cd.c
void	ft_cd(t_cmd	*cmd);

// ft_echo.c
void	ft_echo(t_cmd	*cmd);

// ft_env.c
void	ft_env(t_cmd	*cmd);

// ft_pwd.c
void	ft_pwd(void);

// ft_export.c
void	ft_export(char **str);

// ft_unset.c
void	ft_unset(t_cmd *cmd);

// ft_fork.c
void	ft_fork(int pipe_cnt, t_cmd *cmd);

// ft_here_doc.c
int		check_heredoc(t_cmd *cmd);

// ft_exe.c
void	ft_exe(t_cmd *cmd, t_env *env);

// signal.c
void	ignore_signal(void);
void	heredoc_sigint_handler(int signo);

#endif
