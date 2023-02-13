# minishell

bash나 zsh과 같은 간단한 쉘 만들기

<img src="images/minishell.png" width="500"/>

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
 
<command>		::=	<simple_command>

<simple_command>	::=	<cmd_prefix> <cmd_word> <cmd_suffix>
			|	<cmd_prefix> <cmd_word>
			|	<cmd_prefix>
			|	<cmd_name> <cmd_suffix>
			|	<cmd_name>
 
<cmd_name>		::=	WORD

<cmd_word>		::=	WORD

<cmd_prefix>		::=	<io_redirect> <cmd_prefix>
			|	<io_redirect>

<cmd_suffix>		::=	<io_redirect> <cmd_suffix>
			|	<io_redirect>
			|	WORD <cmd_suffix>
			|	WORD

<io_redirect>		::=	'>' <filename>
			|	'<' <filename>
			|	'>>' <filename>
			|	'<<' <here_end>

<filename>		::=	WORD

<here_end>		::= WORD
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

### 구문 분석 예 

```< file1 cat -e | grep "hello world" > file2```

위 명령어를 입력하면 아래 그림과 같이 재귀적으로 하강 파싱을 한다.   
구문에 문제가 있을 시 ```Syntax Error```를 발생시키고 문제가 없을 시에는 구문 트리를 생성하게 된다.

<div align="center">
  <img src="images/parse_tree1.png" width="700"/>
</div>

아래 그림은 구문에 문제가 없을 시 생성되는 실제 트리의 형태이다.

<div align="center">
  <img src="images/parse_tree2.png" width="500"/>
</div>

## 실행 (Execution)

구문 트리까지 생성되었다면 실행 파트에선 트리를 순회하며 명령어들을 실행시켜주면 된다.

## 빌트인 함수 (Implement the builtins)

## 체크사항

- here_doc에서 ```<<end<<end2``` 와 같이 붙여쓸 경우 오류 발생

	떨어져 있을 경우 정상 작동 ```<<end <<end2```

- cat | cat | cat 으로 명령어 기다리다가 ctrl + d 면 정상 종료되지만

	ctrl + c 면 ```$minishell $minishell``` 등 read_line이 두개로 중복됨

- unset PATH, ls

- echo ctrl + v tab 하면 스페이스만 나와야되는데 아님

## 참고자료

- https://velog.io/@sham/minishell%EA%B3%BC-readline#%ED%81%B4%EB%9F%AC%EC%8A%A4%ED%84%B0-%EB%A7%A5-%EA%B8%B0%EC%A4%80-readline-%EC%84%A4%EC%B9%98-%EB%B0%8F-%EC%82%AC%EC%9A%A9 (readline)
- https://github.com/Swoorup/mysh (shell 동작 순서)
- https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02 (Shell Grammar Rules)
- https://epicarts.tistory.com/163 (트리 구조로 파싱)
