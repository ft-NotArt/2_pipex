/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:15:37 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/26 07:37:32 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ ;

int	recursive_pipe(int argc, char *argv[], int cmd_index, int fd_in)
{
	int		fd[2];
	pid_t	pid ;
	char	**cmd_args ;
	int	exit_status ;

	exit_status = EXIT_SUCCESS;
	if (cmd_index < (argc - 4) && pipe(fd) == -1)
		return (errno);
	pid = fork();
	if (pid < 0)
		return (errno);
	if (pid == 0)
	{
		set_fd(fd_in, get_fd_out(argc, argv, cmd_index, fd));
		cmd_args = get_cmd_args(argv[cmd_index + 2]);
		if (!cmd_args)
			exit(EXIT_FAILURE);
		execve(cmd_args[0], cmd_args, environ);
	}
	(double_close(argc, cmd_index, fd, fd_in), waitpid(pid, &exit_status, 0));
	if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status))
		return (WEXITSTATUS(exit_status));
	if (cmd_index < (argc - 4))
		return (recursive_pipe(argc, argv, (cmd_index + 1), fd[0]));
	return (0);
}

int	main(int argc, char *argv[])
{
	int	infile_fd ;

	if (argc < 5)
		return (ft_putstr_fd("Too few arguments\n", STDOUT_FILENO), 1);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		return (perror("Error opening infile "), 1);
	if (recursive_pipe(argc, argv, 0, infile_fd))
	{
		if (errno)
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
	return (0);
}
