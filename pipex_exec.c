/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:05:37 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/11 17:14:34 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ ;

static int	child_fd(t_args *arg, int cmd_index, int fd[2], int fd_in)
{
	int	fd_out ;

	if (cmd_index < (arg->c - (4 + arg->here_doc)))
		close(fd[0]);
	fd_out = get_fd_out(arg, cmd_index, fd);
	if (fd_out != -1)
	{
		set_fd(fd_in, fd_out);
		return (0);
	}
	else
	{
		close(fd_in);
		return (-1);
	}
}

static void	child_exec(t_args *arg, int cmd_index, int *pid)
{
	char	**cmd_args ;

	cmd_args = get_cmd_args(arg->v[cmd_index + 2 + arg->here_doc]);
	if (!cmd_args)
	{
		free(arg);
		free(pid);
		if (errno == EACCES)
			exit(EXIT_NO_PERM);
		exit(EXIT_CMD_NOT_FOUND);
	}
	execve(cmd_args[0], cmd_args, environ);
	exec_error(arg, cmd_args, pid);
}

int	recursive_pipex(t_args *arg, int cmd_index, int *pid)
{
	static int		fd[2];
	int				fd_in;

	if (cmd_index > 0)
		fd_in = recursive_pipex(arg, (cmd_index - 1), pid);
	else
		fd_in = get_infile(arg);
	if (fd_in == -1)
		return (get_empty_pipe_out());
	if (cmd_index < (arg->c - (4 + arg->here_doc)) && pipe(fd) == -1)
		return (pipe_error(fd_in));
	pid[cmd_index] = fork();
	if (pid[cmd_index] < 0)
		return (fork_error(arg, cmd_index, fd, fd_in));
	if (pid[cmd_index] == 0)
	{
		if (child_fd(arg, cmd_index, fd, fd_in) == -1)
			outfile_error(arg, pid);
		child_exec(arg, cmd_index, pid);
	}
	double_close(arg, cmd_index, fd, fd_in);
	if (cmd_index < (arg->c - (4 + arg->here_doc)))
		return (fd[0]);
	return (0);
}

int	pipex(t_args *arg)
{
	pid_t			*pid ;
	int				cmd_index ;
	int				exit_status ;
	int				i;

	cmd_index = (arg->c - (4 + arg->here_doc));
	pid = malloc((cmd_index + 1) * sizeof(pid_t));
	ft_memset(pid, -1, (cmd_index + 1) * sizeof(pid_t));
	exit_status = EXIT_SUCCESS;
	recursive_pipex(arg, cmd_index, pid);
	i = -1 ;
	while (++i <= cmd_index)
		waitpid(pid[i], &exit_status, 0);
	if (pid[i - 1] == -1)
		return (free(pid), EXIT_FAILURE);
	free(pid);
	if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
		return (WEXITSTATUS(exit_status));
	return (EXIT_SUCCESS);
}
