/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:16:50 by anoteris          #+#    #+#             */
/*   Updated: 2025/01/11 18:43:15 by anoteris         ###   ########.fr       */
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

// Simple struct to stock args to simplify everything

typedef struct s_args
{
	int		c;
	char	**v;
	bool	here_doc;
}				t_args;

// Defines explicit exit codes

# define EXIT_NO_PERM		126
# define EXIT_CMD_NOT_FOUND	127

//	|- ~~ -|  Pipex  |- ~~ -|

int		pipex(t_args *arg);

//	|- ~~ -|  Cmd  |- ~~ -|

char	**get_cmd_args(char *cmd_args);

//	|- ~~ -|  Fd  |- ~~ -|

void	set_fd(int fd_in, int fd_out);
int		get_infile(t_args *arg);
int		get_fd_out(t_args *arg, int cmd_index, int fd[2]);
int		get_empty_pipe_out(void);

//	|- ~~ -| Utils |- ~~ -|

void	free_str_array(char **to_free);
char	**get_all_paths(void);
bool	check_perm(char *cmd, bool *found_cmd);
void	double_close(t_args *arg, int cmd_index, int fd[2], int fd_in);
bool	is_only_space(char *str);

//	|- ~~ -| Error |- ~~ -|

void	exec_error(t_args *arg, char **cmd_args, int *pid);
void	outfile_error(t_args *arg, int *pid);
int		pipe_error(int fd_in);
int		fork_error(t_args *arg, int cmd_index, int fd[2], int fd_in);

#endif