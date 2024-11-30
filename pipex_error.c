/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 20:23:22 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/30 15:01:45 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Only handling errno 'ENOEXEC 8 Exec format error'
// as idk what else could make execve fail
void	exec_error(t_args *arg, char **cmd_args, int *pid)
{
	free_str_array(cmd_args);
	free(arg);
	free(pid);
	if (errno == ENOEXEC)
		exit(EXIT_NO_PERM);
	exit(EXIT_FAILURE);
}

void	outfile_error(t_args *arg, int *pid)
{
	free(arg);
	free(pid);
	exit(EXIT_FAILURE);
}

int	pipe_error(int fd_in)
{
	close(fd_in);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (-1);
}

int	fork_error(t_args *arg, int cmd_index, int fd[2], int fd_in)
{
	if (cmd_index < (arg->c - (4 + arg->here_doc)))
	{
		close(fd[0]);
		close(fd[1]);
	}
	close(fd_in);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (-1);
}
