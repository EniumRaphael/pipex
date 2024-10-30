/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:22:08 by rparodi           #+#    #+#             */
/*   Updated: 2024/04/24 06:37:20 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		ft_free(strs[i]);
		i++;
	}
	ft_free(strs);
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}

void	ft_free_struct2(t_utils *utils)
{
	if (utils->first_cmd)
		ft_free(utils->first_cmd);
	if (utils->second_cmd)
		ft_free(utils->second_cmd);
	if (utils->fd_output > 2)
		close(utils->fd_output);
	if (utils->fd_input > 2)
		close(utils->fd_input);
}

void	ft_free_struct(t_utils *utils)
{
	if (utils->path)
		ft_free_strs(utils->path);
	if (utils->path_input)
		ft_free(utils->path_input);
	if (utils->path_output)
		ft_free(utils->path_output);
	if (utils->first_cmd_args)
		ft_free(utils->first_cmd_args);
	if (utils->second_cmd_args)
		ft_free(utils->second_cmd_args);
	if (utils->first_cmd_path)
		ft_free(utils->first_cmd_path);
	if (utils->second_cmd_path)
		ft_free(utils->second_cmd_path);
	if (utils->check_first_cmd)
		ft_free(utils->check_first_cmd);
	if (utils->check_second_cmd)
		ft_free(utils->check_second_cmd);
	ft_free_struct2(utils);
	ft_free(utils);
}

void	ft_exit(t_utils *utils, void *norman, short int exit_status, char *msg)
{
	if (utils != NULL)
		ft_free_struct(utils);
	if (norman != NULL)
		ft_free(norman);
	if (exit_status == 1)
	{
		ft_fprintf(2, "Error:\n");
		ft_fprintf(1 + exit_status, "> %s", msg);
	}
	exit(exit_status);
}
