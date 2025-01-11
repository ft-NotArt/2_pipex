/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 04:31:13 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/11 18:43:11 by anoteris         ###   ########.fr       */
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

int	get_fd_out(t_args *arg, int cmd_index, int fd[2])
{
	int	fd_out ;
	int	flags ;

	if (cmd_index == (arg->c - (4 + arg->here_doc)))
	{
		flags = O_WRONLY | O_CREAT ;
		if (arg->here_doc)
			flags = flags | O_APPEND ;
		else
			flags = flags | O_TRUNC ;
		fd_out = open(arg->v[(arg->c - 1)], flags, 0644);
		if (fd_out < 0)
		{
			perror("Error opening outfile ");
			return (-1);
		}
	}
	else
		fd_out = fd[1];
	return (fd_out);
}

static int	read_here_doc(t_args *arg)
{
	char	*line ;
	char	*limiter ;
	int		fd ;

	fd = open("/tmp/here_doc_pipex", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error opening/creating '/tmp/here_doc' ");
		return (-1);
	}
	limiter = ft_strjoin(arg->v[2], "\n");
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
	return (0);
}

int	get_infile(t_args *arg)
{
	int	infile_fd ;

	if (arg->here_doc)
	{
		if (read_here_doc(arg) == -1)
			return (-1);
		infile_fd = open("/tmp/here_doc_pipex", O_RDONLY);
		if (infile_fd < 0)
		{
			perror("Error opening infile ");
			return (-1);
		}
	}
	else
	{
		infile_fd = open(arg->v[1], O_RDONLY);
		if (infile_fd < 0)
		{
			perror("Error opening infile ");
			return (-1);
		}
	}
	return (infile_fd);
}

int	get_empty_pipe_out(void)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	close(fd[1]);
	return (fd[0]);
}
