/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:31:09 by yim               #+#    #+#             */
/*   Updated: 2023/01/29 21:33:09 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	printf("\n-----------------------------------------------\n");
	export(envp, NULL);
	export(envp, "A=hello");
	export(envp, "C=hello");
	export(envp, "hhhhh=hello");
	export(envp, "kk=hello");
	export(envp, "kkk");
	export(envp, "kkk=hello");
	unset(envp, "kkk");
	cd("libft", envp);
	printf("\n-----------------------------------------------\n");
	export(envp, NULL);
	pwd();
	env(envp);
	system("leaks minishell");
}
