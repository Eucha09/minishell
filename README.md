# minishell

bash나 zsh과 같은 간단한 쉘 만들기

## 동작 단계

1. 명령어 입력 (readline)
2. 어휘 분석 (lexcial analysis)
3. 구문 분석 (syntax analysis)
4. 실행 (Execution)

## 어휘 분석 (Lexical Analysis)

어휘 분석(Lexical Analysis) 단계에서는 단순히 터미널에 들어온 사용자 입력을 토큰(token) 단위로 나누는 과정이다.

- token : 쉘에서 입력을 처리하기 위해 적절한 단위로 명령문을 나누어야 하는데 이때 명령문을 나누는 최소 단위   
ex) echo "hello world" > file1   
-> token : ```echo```, ```hello world```, ```>```, ```file1``` 

## 구문 분석 (Syntax Analysis)

어휘 분석에서 생성된 토큰들을 받아 주어진 문법에 맞는지를 검사하고, 문법에 맞으면 구문 트리를 생성하는 과정이다.

구문 분석방법에는 여러가지가 있겠지만 저흰 재귀적 하향식 구문 분석 방식을 사용하였다.

### Syntax 규칙 정의

구문 분석하기 위해서는 문법 정의를 할 필요가 있다.   
[Shell Grammar Rules](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02)를 참고해 필요한 부분만 가져와 아래와 같이 정의하였다.

```
 <command_line>		::=	<command> '|' <command_line>
 			|	<command>
 
 <command>		::=	<simple_command> <redirect_list>
			|	<simple_command>
 
 <redirect_list>	::=	<io_redirect> <redirect_list>
			|	<io_redirect>
 
 <io_redirect>		::=	'>' <filename>
			|	'<' <filename>
			|	'>>' <filename>
			|	'<<' <here_end>
                             
 <simple_command>	::=	<cmdpath> <arg_list>
			|	<cmdpath>

 <arg_list>		::=	<arg> <arg_list>
			|	<arg>
```

### 구문 트리 Parse Tree

구문 분석으로 통해 생성된 구문 트리는 단순 이진 트리 구조이며, 아래와 같이 정의되어 있다.

```c
typedef struct s_astnode
{
    int			type;
    char		*data;
    struct s_astnode*	left;
    struct s_astnode*	right;

}	t_astnode;
```

## 실행 (Execution)

## 빌트인 함수 구현 (Implement the builtins)

## 참고자료

- https://velog.io/@sham/minishell%EA%B3%BC-readline#%ED%81%B4%EB%9F%AC%EC%8A%A4%ED%84%B0-%EB%A7%A5-%EA%B8%B0%EC%A4%80-readline-%EC%84%A4%EC%B9%98-%EB%B0%8F-%EC%82%AC%EC%9A%A9 (readline)
- https://github.com/Swoorup/mysh (shell 동작 순서)
- https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02 (Shell Grammar Rules)
- https://epicarts.tistory.com/163 (트리 구조로 파싱)
