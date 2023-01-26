#ifndef EXECUTE_H
#define EXECUTE_H

#include "minishell.h"
#include <sys/stat.h>

typedef struct s_token t_token;
typedef struct s_rdir t_rdir;
typedef struct s_cmd t_cmd;


typedef struct s_env t_env;

void execute(t_cmd *cmd);
int pipe_count(t_cmd *cmd);
int		check_heredoc(t_cmd	*cmd);
int	check_builtin(char *cmd_name);
void	single_builtin(t_cmd *cmd);
void	ft_echo(t_cmd	*cmd);
void	ft_cd(t_cmd *cmd);
void ft_pwd();
void ft_export(char **str);
void ft_unset(t_cmd *cmd);
void ft_env(t_cmd *cmd);
void ft_exit(t_cmd *cmd);
void ft_fork(int pipe_cnt, t_cmd *cmd);
int	ft_rdir(t_rdir *rdir);
void ft_exe(t_cmd *cmd, t_env *env);
t_env *find_env_add(char *key);
t_env *find_env(char *key);
int	ft_strcmp(const char *str1, const char *str2);
char **ft_strjoin2(char *str, char **arr);
void close_all_pipe(int **pipes);
void	ft_error_exit(char *str, int error_no);
void	ft_error_return(char *str, int error_no);
int 	is_builtin(t_cmd *cmd);
void	heredoc_sigint_handler(int signo);
void	ignore_signal(void);
void	ft_command_error(char *cmd);

#endif


// 1. pipe check and count
// 	- 파이프 체크 및 갯수 카운트
// 2. heredoc check and create
// 	- cmd->is_heredoc 확인하여 히어독이 있다면 ft_heredoc 실행 
// 	- ft_heredoc 에서 rdir 리스트에서 type==HEREDOC으로 가기 make_here_doc실행
// 	- make_here_doc에서 readline통해서 pipe에 값들 저장 endline만나면 종료.
// 3. 싱글 빌트인인지 확인 하여 싱글 빌트인이면 포크 없이 함수 실행.
