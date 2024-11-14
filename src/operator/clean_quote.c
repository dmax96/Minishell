/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbellucc <vbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:02:46 by mich              #+#    #+#             */
/*   Updated: 2023/04/20 10:32:24 by vbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

void	clean_double(t_shell *shell)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(shell->lst.input);
	j = 0;
	str = malloc(sizeof(char *) * i + 4);
	j = 0;
	i = -1;
	while (shell->lst.input[++i])
	{
		if (shell->lst.input[i] != 34)
		{
			str[j] = shell->lst.input[i];
			j++;
		}		
	}
	change_input(shell, str, j);
	free(str);
}

int	cnt_quote(t_shell *shell, int j)
{
	while (shell->lst.input[++shell->exp.i])
	{
		if (shell->lst.input[shell->exp.i] == 39)
		{
			if (shell->lst.input[shell->exp.i + 1] == '$')
				shell->lst.input[shell->exp.i] = '\a';
			else
				j++;
		}
	}
	return (j);
}

void	clean_single(t_shell *shell)
{
	int		j;
	char	*str;

	shell->exp.i = ft_strlen(shell->lst.input);
	j = 6;
	str = malloc(sizeof(char *) * (shell->exp.i - j));
	j = 0;
	shell->exp.i = -1;
	while (shell->lst.input[++shell->exp.i])
	{
		if (shell->lst.input[shell->exp.i] != 39)
		{
			str[j] = shell->lst.input[shell->exp.i];
			j++;
		}
		str[j] = '\0';
	}
	free(shell->lst.input);
	shell->lst.input = NULL;
	shell->lst.input = ft_strdup(str);
	shell->lst.input[j] = '\0';
	free(str);
}

void	clean_all_quote(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->lst.input[++i])
	{
		if (shell->lst.input[i] == 39)
			clean_single(shell);
		if (shell->lst.input[i] == 34)
			clean_double(shell);
	}
}

void	clean_parse(t_shell *shell)
{
	int	count_single;
	int	count_double;
	int	i;

	count_single = 0;
	count_double = 0;
	i = -1;
	shell->single_quote = 0;
	while (shell->lst.input[++i])
	{
		if (shell->lst.input[i] == 39)
			count_single = 1;
		if (shell->lst.input[i] == 34)
			count_double = 1;
	}
	loop_quote(shell, -1);
	if (count_single == 0 && count_double == 1)
		clean_double(shell);
	else if (count_single == 1 && count_double == 0)
		clean_single(shell);
	else if (count_single == 1 && count_double == 1)
		clean_all_quote(shell);
}
