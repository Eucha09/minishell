# minishell

bash나 zsh과 같은 간단한 쉘 만들기


## The Syntax Tree Parser

The grammer symbols
```
 <command_line>    ::=    <command>
                 |    <command_line> '|' <command>
 
 <command>        ::=    <simple_command>
                 |    <simple_command> <redirect_list>
 
 <redirect_list>    ::= <io_redirect>
                 |    <redirect_list> <io_redirect>
 
 <io_redirect>    ::= '<' <filename>
                 |    '>' <filename>
                 |    '>>' <filename>
                 |    '<<' <here_end>
                             
 <simple_command>::=    <pathname>
                 |    <simple_command>  <token>
```

## 참고자료

- https://github.com/Swoorup/mysh
- https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02
- https://epicarts.tistory.com/163