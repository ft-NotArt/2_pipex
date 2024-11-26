/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:16:50 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/26 04:37:38 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

void	free_str_array(char **to_free);
char	**get_cmd_args(char *cmd_args);
bool	check_perm(char *cmd, bool *found_cmd);
char	**get_all_paths(void);
void	set_fd(int fd_in, int fd_out);
int		get_fd_out(int argc, char *argv[], int cmd_index, int fd[2]);
void	double_close(int argc, int cmd_index, int fd[2], int fd_in);

#endif