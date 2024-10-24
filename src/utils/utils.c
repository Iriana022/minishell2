/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:31:41 by pmihangy          #+#    #+#             */
/*   Updated: 2024/10/24 12:30:10 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_space(char c)
{
	return ((c >= 8 && c <= 13) || c == 32);
}

void	print_tokens(t_token *root)
{
	t_token	*curr;

	curr = root;
	while (curr)
	{
		printf("text: %s, identifier: %d\n", curr->text, curr->identifier);
		curr = curr->next;
	}
}

void	print_ast(t_ast *ast, int indent)
{
	int	i;

	i = 0;
	if (!ast)
		return ;
	while (i < indent)
	{
		printf("	");
		i++;
	}
	printf("%s ", ast->text);
	if (ast->argv)
	{
		for (int i = 0; ast->argv[i] != NULL; ++i)
			printf("%s ", ast->argv[i]);
	}
	printf("\n");
	print_ast(ast->left, indent + 1);
	print_ast(ast->right, indent + 1);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4))
		++i;
	return (env[i] + 5);
}

char	*merge_argv(char **argv)
{
	int	i;
	char	*ret;

	ret = NULL;
	i = 0;
	while(argv[i])
	{
		ret = ft_strjoin(ret, argv[i]);
		ret = ft_strjoin(ret, " ");
		i++;
	}
	return (ret);
}
