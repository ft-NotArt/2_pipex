/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:15:37 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/27 22:35:54 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	recursive_pipe(int argc, char *argv[], int cmd_index, int fd_in)
{
	int		fd[2];
	pid_t	pid ;
	int		exit_status ;

	exit_status = EXIT_SUCCESS;
	if (cmd_index < (argc - 4) && pipe(fd) == -1)
		return (errno);
	pid = fork();
	if (pid < 0)
		return (errno);
	if (pid == 0)
	{
		set_fd(fd_in, get_fd_out(argc, argv, cmd_index, fd));
		if (cmd_index < (argc - 4))
			close(fd[0]);
		child_exec(argc, argv, cmd_index, fd);
	}
	(double_close(argc, cmd_index, fd, fd_in), waitpid(pid, &exit_status, 0));
	if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
		return (exit_error(exit_status, cmd_index, argc, fd));
	if (cmd_index < (argc - 4))
		return (recursive_pipe(argc, argv, (cmd_index + 1), fd[0]));
	return (0);
}

int	main(int argc, char *argv[])
{
	bool	here_doc ;
	int		exit_status ;

	if (argc < 5)
		return (ft_putstr_fd("Too few arguments\n", STDOUT_FILENO), 1);
	here_doc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (here_doc && argc < 6)
		return (ft_putstr_fd("Too few arguments\n", STDOUT_FILENO), 1);
	exit_status = recursive_pipe(argc, argv, here_doc,
			get_infile(argv, here_doc));
	if (exit_status)
	{
		if (errno)
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (exit_status);
	}
	if (here_doc)
		unlink("/tmp/here_doc");
	return (0);
}
