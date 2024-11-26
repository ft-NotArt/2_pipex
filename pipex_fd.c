/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:31:13 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/26 07:44:57 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_fd(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

int	get_fd_out(int argc, char *argv[], int cmd_index, int fd[2])
{
	int	fd_out ;

	if (cmd_index == (argc - 4))
	{
		// TODO: 	ptit strcmp sur agrv[1] si c'est here_doc
		//			on met le flag append pas trunc
		fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("Error opening outfile ");
			exit(EXIT_FAILURE);
		}
	}
	else
		fd_out = fd[1];
	return (fd_out);
}
