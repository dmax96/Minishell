/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:15:53 by mvolpi            #+#    #+#             */
/*   Updated: 2023/04/20 15:32:10 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

int	control_space(t_shell *shell, int k)
{
	int	p;

	p = 0;
	while (shell->lst.input[++k])
	{
		if (shell->lst.input[k] == ' ')
			p = 1;
		else
		{
			p = 0;
			break ;
		}
	}
	return (p);
}

int	check_error_cod(t_shell *shell)
{
	shell->lst.error = split_cmd(shell->lst.input);
	g_exit = parse(shell->lst.error, shell, -1);
	if (g_exit > 0)
	{
		shell->old_g_exit = g_exit;
		ft_sarfree(shell->lst.error, ft_sarsize(shell->lst.error));
		return (g_exit);
	}
	ft_sarfree(shell->lst.error, ft_sarsize(shell->lst.error));
	return (g_exit);
}

void	loop2(t_shell *shell, int p)
{
	if (p == 0)
	{
		shell->lst.redirection = NULL;
		if (ft_strncmp(shell->lst.input, "", 1))
			add_history(shell->lst.input);
		if (ft_strncmp(shell->lst.input, "", 1) != 0)
		{
			g_exit = check_error_cod(shell);
			if (g_exit == 0)
				check_operator(shell);
		}
		dup2(shell->stdout, STDOUT_FILENO);
		dup2(shell->stdin, STDIN_FILENO);
	}
}

int	loop(t_shell *shell)
{
	int	k;
	int	p;

	while (1)
	{	
		p = 0;
		k = -1;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		shell->lst.input = readline("minishell: ");
		ctrl_d(shell);
		if (g_exit != 0)
			shell->old_g_exit = g_exit;
		if (ft_strncmp(shell->lst.input, "$?", 3) != 0)
			shell->old_g_exit = g_exit;
		reset_var(shell);
		p = control_space(shell, k);
		loop2(shell, p);
		free(shell->lst.input);
		shell->lst.input = NULL;
	}
}

/**
 * @brief the start of the program that checks for errors,
 * saves the enviroment in a list and sets up a new prompt
 * waiting for a command and for now if in input there is
 * exit the program exit with no errors
 * 
 * @param argc number of argument in input from the teminal with which
 * we check that to start the programm only ./minishell is given in input
 * @param argv counter of argument in input from the terminal that
 * we set up at void because it is not needed within the program but
 * we need to call the force to have envp
 * @param envp an array where we have all the enviroment variables and we
 * need to save in a list where we can modify each variable to our liking
 * @return int return a 0 for now
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	g_exit = 0;
	if (argc > 1)
		exit(printf("Error, there are too many argument!!!\n"));
	get_env(envp, &shell);
	shell.stdout = dup(STDOUT_FILENO);
	shell.stdin = dup(STDIN_FILENO);
	init_all(&shell);
	loop(&shell);
	return (0);
}
