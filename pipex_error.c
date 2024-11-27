/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:23:22 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/27 22:04:19 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_error(int cmd_index, int argc, int fd[2], char **cmd_args)
{
	if (cmd_index < (argc - 4))
		close(fd[0]);
	if (cmd_args)
	{
		free_str_array(cmd_args);
		exit(EXIT_FAILURE);
	}
}

int	exit_error(int exit_status, int cmd_index, int argc, int fd[2])
{
	if (cmd_index < (argc - 4))
		close(fd[0]);
	return (WEXITSTATUS(exit_status));
}
