/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:31:09 by yim               #+#    #+#             */
/*   Updated: 2023/01/29 17:50:00 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	printf("\n-----------------------------------------------\n");
	env(envp);
	export(envp, "C=hello");
	export(envp, "hhhhh=hello");
	export(envp, "kk=hello");
	export(envp, "kkk=hello");
	printf("\n-----------------------------------------------\n");
	export(envp, NULL);
}
