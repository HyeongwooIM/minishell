#ifndef EXECUTE_H
#define EXECUTE_H


void execute(t_cmd *cmd);
int pipe_count(t_cmd *cmd);

void	check_heredoc(t_cmd	*cmd);

int	check_builtin(char *cmd_name);
int	single_builtin(t_cmd *cmd, t_env env);
void	ft_echo(t_cmd	*cmd);
void	ft_cd(t_cmd *cmd);
void ft_pwd();
void ft_export(t_cmd *cmd);
void ft_unset(t_cmd *cmd);
void ft_env(t_cmd *cmd);
void ft_exit(t_cmd *cmd);
void ft_fork(int pipe_cnt, t_cmd *cmd);
void pipe_close(int **pipes, int i, int pipe_cnt);
void ft_rdir(t_rdir *rdir);
void ft_exe(t_cmd *cmd, t_env *env);

t_env *find_env_add(char *key);
t_env *find_env(char *key);
int	ft_strcmp(const char *str1, const char *str2);
char **ft_strjoin2(char *str, char **arr);
#endif


// 1. pipe check and count
// 	- 파이프 체크 및 갯수 카운트
// 2. heredoc check and create
// 	- cmd->is_heredoc 확인하여 히어독이 있다면 ft_heredoc 실행 
// 	- ft_heredoc 에서 rdir 리스트에서 type==HEREDOC으로 가기 make_here_doc실행
// 	- make_here_doc에서 readline통해서 pipe에 값들 저장 endline만나면 종료.
// 3. 싱글 빌트인인지 확인 하여 싱글 빌트인이면 포크 없이 함수 실행.
