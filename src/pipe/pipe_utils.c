/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolpi <mvolpi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:55:58 by mich              #+#    #+#             */
/*   Updated: 2023/04/12 18:10:37 by mvolpi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	count_pipe(t_shell *shell, int i)
{
	int	pipe_counter;

	pipe_counter = 0;
	while (shell->lst.input[++i])
	{
		if (is_pipe(shell->lst.input[i]) == 1)
			pipe_counter++;
	}
	return (pipe_counter);
}

int	process_child(int *fd, int c, t_shell *shell, int i)
{
	int	d;

	d = 0;
	change_in(shell, c);
	if (i)
		dup2(shell->stdout, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	shell->here_pipe = 1;
	shell->out_pipe = dup(STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	d = check_red(shell->lst.input, shell, i);
	if (d == 0)
	{
		clean_parse(shell);
		executor(shell);
	}
	return (1);
}
