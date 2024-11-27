/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:16:50 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/27 22:36:05 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// Includes

# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

//	|- ~~ -|  Cmd  |- ~~ -|

char	**get_cmd_args(char *cmd_args);

//	|- ~~ -|  Fd  |- ~~ -|

void	set_fd(int fd_in, int fd_out);
int		get_infile(char *argv[], bool here_doc);
int		get_fd_out(int argc, char *argv[], int cmd_index, int fd[2]);

//	|- ~~ -| Exec |- ~~ -|

void	child_exec(int argc, char *argv[], int cmd_index, int fd[2]);

//	|- ~~ -| Utils |- ~~ -|

void	free_str_array(char **to_free);
char	**get_all_paths(void);
bool	check_perm(char *cmd, bool *found_cmd);
void	double_close(int argc, int cmd_index, int fd[2], int fd_in);
bool	is_only_space(char *str);

//	|- ~~ -| Error |- ~~ -|

void	exec_error(int cmd_index, int argc, int fd[2], char **cmd_args);
int		exit_error(int exit_status, int cmd_index, int argc, int fd[2]);

#endif