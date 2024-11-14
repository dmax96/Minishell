/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzak <kzak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:25:14 by mich              #+#    #+#             */
/*   Updated: 2023/04/20 11:46:42 by kzak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	print_export(t_shell *shell, char **str_save)
{
	int	i;

	i = -1;
	while (shell->exp.sort_env[++i])
	{
		str_save = ft_split(shell->exp.sort_env[i], '=');
		if (str_save[1] == NULL)
			printf("declare -x %s\n", str_save[0]);
		else
		{
			printf("declare -x %s=%c", str_save[0], 34);
			printf("%s%c\n", str_save[1], 34);
		}
		ft_sarfree(str_save, ft_sarsize(str_save));
	}
}

char	**sort(char **sorting)
{
	int		i;
	int		j;
	int		c;
	char	**sort_env;

	i = 0;
	while (sorting[i])
		++i;
	sort_env = malloc(sizeof(char *) * (i + 1));
	sort_env[i] = NULL;
	i = -1;
	while (sorting[++i])
	{
		j = -1;
		c = 0;
		while (sorting[++j])
			if (ft_strncmp(sorting[i], sorting[j], ft_strlen(sorting[i])) > 0)
				c++;
		sort_env[c] = ft_strdup(sorting[i]);
	}
	return (sort_env);
}

int	change_var(t_shell *shell, int c)
{
	int		i;
	int		pos;

	if (ft_strncmp(shell->lst.executor[c], "=", 1) == 0)
		printf("minishell: export: '=': not a valid identifier\n");
	shell->echo.j = 0;
	i = -1;
	while (shell->env.current[++i])
	{
		pos = save_str(shell, pos, i, c);
		pos = ft_strchrp(shell->env.current[i], '=');
		if (ft_strncmp(shell->curr, shell->str, ft_strlen(shell->str) + 1) == 0)
		{
			if (change_a(i, c, pos, shell))
			{
				free_str(shell->str, shell->curr);
				return (1);
			}
			free_str(shell->str, shell->curr);
			return (1);
		}
		free_str(shell->str, shell->curr);
	}
	return (0);
}

void	add_var(t_shell *shell, int c)
{
	int	i;
	int	j;

	i = -1;
	j = ft_sarsize(shell->env.current);
	shell->env.save = (char **)malloc(sizeof(char *) * j + 10);
	while (shell->env.current[++i])
		shell->env.save[i] = ft_strdup(shell->env.current[i]);
	shell->env.save[i] = NULL;
	ft_sarfree(shell->env.current, ft_sarsize(shell->env.current));
	shell->env.current = (char **)malloc(sizeof(char *) * \
		ft_sarsize(shell->env.save) + 10);
	i = -1;
	while (shell->env.save[++i])
		shell->env.current[i] = ft_strdup(shell->env.save[i]);
	shell->env.current[i] = ft_strdup(shell->lst.executor[c]);
	j = -1;
	while (shell->env.current[i][++j])
	{
		if (shell->env.current[i][j] == '\a' || shell->env.current[i][j] == '~')
			shell->env.current[i][j] = ' ';
	}
	shell->env.current[i + 1] = NULL;
	ft_sarfree(shell->env.save, ft_sarsize(shell->env.save));
}

void	ft_export(t_shell *shell)
{
	char	**str_save;
	int		c;

	c = 0;
	str_save = NULL;
	if (shell->lst.executor[1] == NULL)
	{
		shell->exp.sort_env = sort(shell->env.current);
		print_export(shell, str_save);
		ft_sarfree(shell->exp.sort_env, ft_sarsize(shell->exp.sort_env));
	}
	else
	{
		while (shell->lst.executor[++c])
		{
			shell->exp.i = -1;
			if (!change_var(shell, c))
				add_var(shell, c);
		}
	}
}
