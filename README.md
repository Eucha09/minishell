# minishell

bash나 zsh과 같은 간단한 쉘 만들기

## 동작 단계

1. 명령어 입력 (readline)
2. 어휘 분석 (lexcial analysis)
3. 문법 분석 (syntax analysis)
4. 실행 (Execution)

## 어휘 분석 (Lexical Analysis)

어휘 분석(Lexical Analysis) 단계에서는 단순히 터미널에 들어온 사용자 입력을 토큰(token) 단위로 나누는 과정이다.

- token : 쉘에서 입력을 처리하기 위해 적절한 단위로 명령문을 나누어야 하는데 이때 명령문을 나누는 최소 단위   
ex) echo "hello world" > file1   
token : ```echo```, ```hello world```, ```>```, ```file1``` 



## 문법 분석 (Syntax Analysis)

The grammer symbols
```
 <command_line>		::=	<command>
                 	|	<command_line> '|' <command>
 
 <command>		::=	<simple_command>
			|	<simple_command> <redirect_list>
 
 <redirect_list>	::=	<io_redirect>
                 	|	<redirect_list> <io_redirect>
 
 <io_redirect>		::=	'<' <filename>
                 	|	'>' <filename>
                 	|	'>>' <filename>
                 	|	'<<' <here_end>
                             
 <simple_command>	::=	<pathname>
                 	|	<simple_command>  <token>
```

## 실행 (Execution)

## 빌트인 함수 구현 (Implement the builtins)

## 참고자료

- https://velog.io/@sham/minishell%EA%B3%BC-readline#%ED%81%B4%EB%9F%AC%EC%8A%A4%ED%84%B0-%EB%A7%A5-%EA%B8%B0%EC%A4%80-readline-%EC%84%A4%EC%B9%98-%EB%B0%8F-%EC%82%AC%EC%9A%A9 (readline)
- https://github.com/Swoorup/mysh (shell 동작 순서)
- https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02 (Shell Grammar Rules)
- https://epicarts.tistory.com/163 (트리 구조로 파싱)
