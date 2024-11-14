/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:31:00 by mich              #+#    #+#             */
/*   Updated: 2023/04/20 15:18:17 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	delete_file2(t_shell *shell)
{
	while (shell->lst.delete_str[++shell->count.k])
	{
		shell->count.i = -1;
		while (shell->lst.executor[++shell->count.i])
		{
			if (ft_strncmp(shell->lst.executor[shell->count.i], \
				shell->lst.delete_str[shell->count.k], \
				ft_strlen(shell->lst.executor[shell->count.i])) == 0)
			{
				shell->count.j = shell->count.i;
				while (shell->lst.executor[shell->count.j])
				{
					free(shell->lst.executor[shell->count.j]);
					if (shell->lst.executor[shell->count.j + 1] != NULL)
					{
						shell->lst.executor[shell->count.j] = \
							ft_strdup(shell->lst.executor[shell->count.j + 1]);
						shell->count.j++;
					}
					else
						shell->lst.executor[shell->count.j] = NULL;
				}
			}
		}
	}
}

int	check_file(t_shell *shell)
{
	if (shell->check_mix_red == 1)
	{
		shell->count.k = -1;
		delete_file2(shell);
		ft_sarfree(shell->lst.delete_str, ft_sarsize(shell->lst.delete_str));
	}
	if (shell->lst.redirection == NULL || shell->do_redirection == 0)
	{
		return (1);
	}
	else
	{
		shell->count.k = -1;
		delete_file2(shell);
		ft_sarfree(shell->lst.delete_str, ft_sarsize(shell->lst.delete_str));
		return (0);
	}
}

int	control_g_exit(t_shell *shell)
{
	shell->lst.executor = ft_split(shell->lst.input, ' ');
	if (!shell->lst.executor[0])
	{
		printf("minishell:  : command not found\n");
		ft_sarfree(shell->lst.executor, ft_sarsize(shell->lst.executor));
		g_exit = 127;
		return (g_exit);
	}
	if (ft_strncmp(shell->lst.input, "$?", 3) == 0)
	{
		printf("%d: command not found\n", shell->old_g_exit);
		shell->old_g_exit = 127;
		return (1);
	}
	return (0);
}

int	executor(t_shell *shell)
{
	if (control_g_exit(shell))
		return (g_exit);
	check_file(shell);
	expansion(shell);
	if (ft_strncmp(shell->lst.executor[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(shell->lst.executor[0], "echo", 5) == 0)
		ft_echo(shell);
	else if (ft_strncmp(shell->lst.executor[0], "cd", 3) == 0)
		ft_cd(shell);
	else if (ft_strncmp(shell->lst.executor[0], "env", 4) == 0)
		ft_env(shell, shell->env.current);
	else if (ft_strncmp(shell->lst.executor[0], "exit", 5) == 0)
		ft_exit(shell);
	else if (ft_strncmp(shell->lst.executor[0], "export", 7) == 0)
		ft_export(shell);
	else if (ft_strncmp(shell->lst.executor[0], "unset", 6) == 0)
		ft_unset (shell, shell->env.current);
	else
		commands(shell);
	ft_sarfree(shell->lst.executor, ft_sarsize(shell->lst.executor));
	return (0);
}
