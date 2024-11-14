/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_red_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbellucc <vbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:15:58 by vbellucc          #+#    #+#             */
/*   Updated: 2023/04/17 12:17:28 by vbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exp_red.h"

void	init_var(t_shell *shell, int i)
{
	if (shell->lst.redirection[i][0] == '$')
		shell->dollar = 1;
	if (shell->lst.redirection[i][0] == '\a')
		shell->flag = 1;
	shell->expn.j = -1;
	shell->expn.pos = 0;
	shell->expn.flag = 0;
	shell->lst.expansion = ft_split(shell->lst.redirection[i], '$');
	if (shell->dollar == 1)
		shell->expn.j = -1;
	else
		shell->expn.j = 0;
}

void	control_a(t_shell *shell)
{
	if (shell->lst.expansion[shell->expn.j][shell->expn.pos - 1] == '\a')
	{
		shell->lst.expansion[shell->expn.j][shell->expn.pos - 1] = '\0';
		shell->expn.flag = 1;
	}
}
