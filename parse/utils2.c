//
// Created by jiyun on 2023/01/17.
//

#include "../minishell.h"
#include "./parse.h"

/* parse error 검사
 * lst 생성 및 추가
 * 청크 리스트를 토큰 리스트에 깊은 복사 하면서 cmd 인지 cmd에 딸린 옵션인지.. 확인하고 type 바꿔주기
 */

int have_cmd_type(t_token  *tokens)
{
    while (tokens->word != NULL)
    {
        if (tokens->type == CMD)
            return (1);
        tokens = tokens->next;
    }
    return (0);
}