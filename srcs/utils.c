/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:15:34 by eujeong           #+#    #+#             */
/*   Updated: 2023/02/04 13:09:25 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_minishell(void)
{
	int		fd;
	char	*line;

	fd = open("ascii_art", O_RDONLY);
	ft_printf("\n");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		ft_printf(COLOR_GREEN"%s"COLOR_RESET, line);
		free(line);
	}
	ft_printf("\n");
	close(fd);
}
