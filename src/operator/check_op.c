/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:17:48 by mich              #+#    #+#             */
/*   Updated: 2023/04/20 15:21:16 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

void	execute_redirection(t_shell *shell)
{
	shell->red.count_delete_str = 0;
	shell->red.j = shell->red.count_redirection;
	shell->lst.here_doc = ft_split(shell->lst.redirection[0], ' ');
	shell->do_redirection = 1;
	clean_parse(shell);
	exp_red(shell);
	if (shell->redirection_id == 1)
		go_input(shell);
	else if (shell->redirection_id == 2)
		go_output(shell);
	else if (shell->redirection_id == 3)
		go_append(shell);
}

void	redirection(t_shell *shell)
{
	if (shell->red.count_redirection >= 1)
	{
		execute_redirection(shell);
		shell->lst.file = \
			ft_split(shell->lst.redirection[shell->red.count_redirection], ' ');
		if (ft_strncmp(shell->lst.here_doc[0], "cat", 3) == 0
			&& shell->redirection_id == 4)
		{
			go_here_doc_cat(shell);
			return ;
		}
		ft_sarfree(shell->lst.file, ft_sarsize(shell->lst.file));
		if (shell->redirection_id == 4)
			go_here_doc(shell);
		ft_sarfree(shell->lst.here_doc, ft_sarsize(shell->lst.here_doc));
	}
	if (shell->here_cat == 0 && shell->check_flag == 0)
	{
		delete_op(shell);
		clean_parse(shell);
		executor(shell);
	}
}

int	check_red(char *input, t_shell *shell, int i)
{
	i = -1;
	shell->redirection_id = 0;
	shell->check_mix_red = 0;
	while (input[++i])
	{
		i = check_double_red(shell, input, i);
		check_single_red(shell, input, i);
	}
	shell->lst.redirection = split_redirection(shell->lst.input);
	shell->red.count_redirection = ft_sarsize(shell->lst.redirection) - 1;
	if (shell->red.count_redirection >= 1)
	{
		if (shell->redirection_id > 0 && shell->check_mix_red != 1)
			redirection(shell);
		if (shell->check_mix_red == 1)
			mix_redirection(shell);
		ft_sarfree(shell->lst.redirection, ft_sarsize(shell->lst.redirection));
		return (shell->redirection_id);
	}
	shell->do_redirection = 0;
	shell->check_mix_red = 0;
	ft_sarfree(shell->lst.redirection, ft_sarsize(shell->lst.redirection));
	return (0);
}

int	check_operator(t_shell *shell)
{
	int	i;
	int	c;

	i = -1;
	c = -1;
	if (!control_pipe(shell))
		c = check_red(shell->lst.input, shell, i);
	if (c == 0)
	{
		clean_parse(shell);
		executor(shell);
	}
	return (0);
}
