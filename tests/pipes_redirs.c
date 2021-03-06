/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:13:04 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:13:05 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests_minishell.h"

static int redirection(char **env)
{
	int status;
	int std_out;
	int fd;

	std_out = dup(STDOUT_FILENO);
	printf("*** Starting redirection sample\n");
	if (!fork()) {
		char *argv[2];
		argv[0] = "ls";
		argv[1] = 0;

		fd = open("./redirection_redirected_output", O_CREAT | O_TRUNC | O_RDWR, 0666);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		printf("*** Executing child redirected to file\n");
		execve("/bin/ls", argv, env);
	}
	wait(&status);
	dup2(std_out, STDOUT_FILENO);
	printf("*** Printing the final status after the redirection has been recovered: %d (%s)\n", status, strerror(errno));
	if (!fork()) {
		char *cat[3];
		cat[0] = "cat";
		cat[1] = "redirection_redirected_output";
		cat[2] = 0;

		printf("*** Printing contents of redirected output\n");
		execve("/bin/cat", cat, env);
	}
	wait(&status);
	return (0);
}

static int pipelining(char **env)
{
	int status;
	int std_out;
	int std_in;
	int pipes[2];

	printf("*** Starting pipe sample\n");
	pipe(pipes);
	printf("*** Created pipes\n");
	std_out = dup(STDOUT_FILENO);
	std_in = dup(STDIN_FILENO);
	printf("*** Dupped in & out\n");
	if (!fork()) {
		char *ls[2];
		ls[0] = "ls";
		ls[1] = 0;

		printf("*** First thread: /bin/ls (%d)\n", pipes[1]);
		dup2(pipes[1], STDOUT_FILENO);
		execve("/bin/ls", ls, env);
	}
	if (!fork()) {
		char *grepp[3];
		grepp[0]= "grep";
		grepp[1]= "pipes";
		grepp[2] = 0;

		printf("*** Second thread: grep (%d)\n", pipes[0]);
		dup2(pipes[0], STDIN_FILENO);
		execve("/bin/grep", grepp, env);
	}
	printf("*** Threads launched\n");
	wait(&status);
	wait(&status);
	printf("*** Threads completed\n");
	close(pipes[0]);
	close(pipes[1]);
	dup2(std_out, STDOUT_FILENO);
	dup2(std_in, STDIN_FILENO);
	printf("*** Recovered original in & out");
	return (0);
}

static void		redirection_input(char **env)
{
	char *argv[2];
	int	fd;

	fd = open("/home/visv/42/code/minishell_adrian/minishell/author", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("Error abriendo archivo %s\n", strerror(errno));
		exit(0);
	}
	argv[0] = "cat";
	argv[1] = 0;
	execve(*argv, argv, env);
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	redirection_input(env);
	//redirection(env);
	// (pipelining(env));
	return (0);
}
