/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:05:37 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/27 22:36:37 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

extern char	**environ ;

void	child_exec(int argc, char *argv[], int cmd_index, int fd[2])
{
	char	**cmd_args ;

	cmd_args = get_cmd_args(argv[cmd_index + 2]);
	if (!cmd_args)
		exit(EXIT_FAILURE);
	execve(cmd_args[0], cmd_args, environ);
	exec_error(cmd_index, argc, fd, cmd_args);
}
