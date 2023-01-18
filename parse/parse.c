//
// Created by jiyun on 2023/01/07.
//

// " ", ' ', $ 치환
// input token화
// token으로 실행부로 옮길 구조체 완성하기

#include "../minishell.h"
#include "./parse.h"

t_info g_info;


void	input_tokenize(char *input, t_token *tokens)
{
	t_token	*chunks;

	/* token 할당 */

	chunks = new_token(0, NULL);
	//null 가드

	/* while
	 * chunk_lst 만들기
	 	* size 재기(일단 white space 기준으로)
	*/
	make_chunk_lst(input, chunks);

	/* "$" 치환 맟 '' 제거 */
    make_token_lst(chunks, tokens);

	/* while
	 * token_lst 만들기
	 	* parse error 검사
	 	* lst 생성 및 추가
	 	* 청크 리스트를 토큰 리스트에 깊은 복사 하면서 cmd 인지 cmd에 딸린 옵션인지.. 확인하고 type 바꿔주기
	*/
}

int	main(void)
{
	char *input;
	t_token *tokens;

	while (1)
	{
		input = readline("minishell$ ");
		tokens = new_token(0, NULL);
		// token화 하기
		input_tokenize(input, tokens); // error를 받아서 여기서 free하기
        make_cmd_lst(tokens);
	}

	/* 확인용 */
	while (tokens != NULL)
	{
		printf("%s\n", tokens->word);
		tokens = tokens->next;
	}
	printf("\n");
}

//테스트
