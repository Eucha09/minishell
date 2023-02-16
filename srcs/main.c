/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:40:03 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/16 19:05:56 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_errno;

void	sh_exit(int code)
{
	ft_printf("exit\n");
	exit(code);
}

char	**dup_envp(char *envp[])
{
	int		i;
	char	**d_envp;

	i = 0;
	d_envp = (char **)malloc(sizeof(char *) * 250);
	if (d_envp == NULL)
		return (NULL);
	while (envp[i])
	{
		d_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	d_envp[i] = NULL;
	return (d_envp);
}

void	shell_init(int argc, char **argv, char **envp, char ***d_envp)
{
	(void)argc;
	(void)argv;
	*d_envp = dup_envp(envp);
	if (d_envp == NULL)
		exit(1);
	set_signal(HDL, IGN);
	print_minishell();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_lexer		lexer;
	t_astnode	*astree;
	char		*line;
	char		**d_envp;

	shell_init(argc, argv, envp, &d_envp);
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			sh_exit(0);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		lexer_build(line, ft_strlen(line), &lexer, d_envp);
		free(line);
		if (parse(&lexer, &astree))
			execute(astree, d_envp);
		astnode_delete(astree);
		lexer_clear(&lexer);
	}
	free_double_array(d_envp);
}
