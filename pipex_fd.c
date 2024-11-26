/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:31:13 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/26 14:04:59 by anoteris         ###   ########.fr       */
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
	int	flags ;

	if (cmd_index == (argc - 4))
	{
		flags = O_WRONLY | O_CREAT ;
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			flags = flags | O_APPEND ;
		else
			flags = flags | O_TRUNC ;
		fd_out = open(argv[(argc - 1)], flags, 0644);
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

static void	read_here_doc(char *argv[])
{
	char	*line ;
	char	*limiter ;
	int		fd ;

	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error opening/creating '/tmp/here_doc' ");
		exit(EXIT_FAILURE);
	}
	limiter = ft_strjoin(argv[2], "\n");
	if (!limiter)
		(ft_putstr_fd(strerror(errno), STDERR_FILENO), exit(EXIT_FAILURE));
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(line, limiter))
	{
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	free(limiter);
	close(fd);
}

int	get_infile(char *argv[], bool here_doc)
{
	int	infile_fd ;

	if (here_doc)
	{
		read_here_doc(argv);
		infile_fd = open("/tmp/here_doc", O_RDONLY);
		if (infile_fd < 0)
		{
			perror("Error opening infile ");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd < 0)
		{
			perror("Error opening infile ");
			exit(EXIT_FAILURE);
		}
	}
	return (infile_fd);
}
