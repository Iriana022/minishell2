/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irazafim <irazafim@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 08:55:54 by irazafim          #+#    #+#             */
/*   Updated: 2024/10/31 13:46:29 by irazafim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    exec_ast(t_ast *ast, char *entry, char ***env, char *path)
{
	int pfd[2];
	pid_t pid_left, pid_right;

	if(!ast)
		return ;
	if (ast->identifier == CMD)
	{
		pid_t pid = fork();
		if (pid == -1)
			printf("Fork error");
		if (pid == 0)
		{
			char	*dir_path = get_dir_path(ast->text, path);
			char    *p;
			
			if (ast->argv != NULL)
			{
				ast->argv++;	
				p = ft_strjoin(ft_strjoin(ast->text, " "), merge_argv(ast->argv));
			}
			else
				p = ft_strjoin(ast->text, " ");
			printf("p >>> %s\n",  p);
			execve(ft_strjoin(dir_path, ast->text), ft_split(p, ' '), *env); 
			perror("error execve");
		}
		else    
			wait(NULL);
	}
	else if (ast->identifier == RIGHT_REDIRECTION)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			int fd = open(ast->right->text, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			printf("%s %s\n", ast->argv[0], ast->argv[1]);
			if (ast->argv)
				ast->right->argv++;
			exec_ast(ast->left, entry, env, path);
			exit(0);
		}
		else
			wait(NULL);
    }
	else if (ast->identifier == PIPE)
	{
		pipe(pfd);
		pid_left = fork();
		if (pid_left == 0)
		{
			close(pfd[0]);
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
			if (ast->argv)
				ast->left->argv++;
			exec_ast(ast->left, entry, env, path);
			exit(0);
		}
		pid_right = fork();
		if (pid_right == 0)
		{
			close(pfd[1]);
			dup2(pfd[0], STDIN_FILENO);
			close(pfd[0]);
			if (ast->argv)
				ast->right->argv++;
			exec_ast(ast->right, entry, env, path);
			exit(0);
		}
		close(pfd[0]);
		close(pfd[1]);
		wait(NULL);
		wait(NULL);
	}
	else if (ast->identifier == LEFT_REDIRECTION)
	{
		int fd2;
		pid_t pid2;
		pid2 = fork();
		
		if(pid2 == 0)
		{
			fd2 = open(ast->right->text, O_RDONLY);
			dup2(fd2, STDIN_FILENO);
			close(fd2);
			exec_ast(ast->left, entry, env, path);
			exit(0);
		}
		else
			wait(NULL);
	}
	else if (ast->identifier == DOUBLE_RIGHT_REDIRECTION)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			int fd = open(ast->right->text, O_WRONLY | O_APPEND | O_CREAT, 0666);
			dup2(fd, STDOUT_FILENO);
			close(fd);
			exec_ast(ast->left, entry, env, path);
			exit(0);
		}
		else
			wait(NULL);
    }
}