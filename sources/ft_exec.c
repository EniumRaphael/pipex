/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:23:10 by rparodi           #+#    #+#             */
/*   Updated: 2024/04/24 09:17:46 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_close(t_utils *utils, int *fd)
{
	if (utils->fd_output > 2)
		close(utils->fd_output);
	if (utils->fd_input > 2)
		close(utils->fd_input);
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
}

int	ft_open_fds(t_utils *utils, int *fd, int cmd_count)
{
	if (cmd_count == 1)
	{
		close(fd[0]);
		close(utils->fd_output);
		dup2(utils->fd_input, 0);
		close(utils->fd_input);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	else if (cmd_count == 2)
	{
		close(fd[1]);
		close(utils->fd_input);
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(utils->fd_output, 1);
		close(utils->fd_output);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
	return (cmd_count);
}

void	ft_wait(pid_t pid1, pid_t pid2, t_utils *utils, int *fd)
{
	if (pid1 != 0 || pid2 != 0)
		ft_open_fds(utils, fd, 0);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	ft_pipex(t_utils *utils)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == -1)
		ft_exit(utils, NULL, 1, "Fork failed!\n");
	if (pid1 == 0)
	{
		ft_open_fds(utils, fd, 1);
		ft_exec_cmd(utils, utils->check_first_cmd, utils->first_cmd_args);
		ft_close(utils, fd);
	}
	pid2 = fork();
	if (pid2 == -1)
		ft_exit(utils, NULL, 1, "Fork failed!\n");
	if (pid2 == 0)
	{
		ft_open_fds(utils, fd, 2);
		ft_exec_cmd(utils, utils->check_second_cmd, utils->second_cmd_args);
		ft_close(utils, fd);
	}
	ft_wait(pid1, pid2, utils, fd);
}

void	ft_exec_cmd(t_utils *utils, char *cmd, char *cmd_args)
{
	const char	**args = (const char **)ft_split(cmd_args, ' ');

	if (execve(cmd, (char *const *)args, (char *const *)utils->envp) == -1)
	{
		ft_free_strs((char **)args);
		ft_exit(utils, NULL, 1, "Execution of the command failed!\n");
	}
}
