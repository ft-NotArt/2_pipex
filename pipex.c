/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoteris <noterisarthur42@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:15:37 by anoteris          #+#    #+#             */
/*   Updated: 2024/11/30 15:00:50 by anoteris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	t_args	*arg;
	bool	here_doc ;
	int		exit_status ;

	if (argc < 5)
		return (ft_putstr_fd("Too few arguments\n", STDOUT_FILENO), 1);
	here_doc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (here_doc && argc < 6)
		return (ft_putstr_fd("Too few arguments\n", STDOUT_FILENO), 1);
	arg = malloc(sizeof(t_args));
	arg->c = argc ;
	arg->v = argv ;
	arg->here_doc = here_doc;
	exit_status = pipex(arg);
	free(arg);
	if (here_doc)
		unlink("/tmp/here_doc_pipex");
	return (exit_status);
}
