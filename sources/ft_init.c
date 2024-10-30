/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:15:24 by rparodi           #+#    #+#             */
/*   Updated: 2024/04/24 09:15:51 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_cmd_args(char *str)
{
	size_t	i;
	char	*tempo;

	i = 0;
	tempo = NULL;
	while (str[i] != '\0' && str[i] != 32)
		i++;
	if (str[i] != '\0')
		tempo = ft_strdup(str + i + 1);
	return (tempo);
}

char	*ft_strjoin_before_space(char *str)
{
	size_t	i;
	char	*result;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0' && str[i] != ' ')
		i++;
	if (str[i] == ' ')
	{
		result = (char *)malloc(sizeof(char) * (i + 1));
		if (result == NULL)
			return (NULL);
		ft_memcpy(result, str, i);
		result[i] = '\0';
		return (result);
	}
	return (ft_strdup(str));
}

void	ft_init_args2(char *argv[], t_utils *utils)
{
	utils->first_cmd_args = ft_strdup(argv[2]);
	if (!utils->first_cmd_args)
		ft_exit(utils, NULL, 1, "first_cmd_args alloc has crashed !\n");
	utils->second_cmd_args = ft_strdup(argv[3]);
	if (!utils->first_cmd_args)
		ft_exit(utils, NULL, 1, "second_cmd_args alloc has crashed !\n");
	utils->fd_input = open(utils->path_input, O_RDWR);
	if (utils->fd_input == -1)
		ft_exit(utils, NULL, 1, "First file cannot be open !\n");
	utils->fd_output = open(utils->path_output, \
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (utils->fd_output == -1)
		ft_exit(utils, NULL, 1, "Second file cannot be open !\n");
	if (access(utils->path_input, F_OK) == -1)
		ft_exit(utils, NULL, 1, "File input doesn't exist !\n");
	else if (access(utils->path_input, R_OK) == -1 || \
			access(utils->path_input, W_OK) == -1)
		ft_exit(utils, NULL, 1, "The file 1 is not chmod correctily!\n");
	else if (access(utils->path_output, R_OK) == -1 || \
			access(utils->path_output, W_OK) == -1)
		ft_exit(utils, NULL, 1, "The file 2 is not chmod correctily!\n");
	utils->check_first_cmd = NULL;
	utils->check_second_cmd = NULL;
}

void	ft_init_args(char *argv[], t_utils *utils)
{
	ft_init_cmd_path(argv, utils);
	if (access(argv[3], X_OK) == -1)
	{
		utils->second_cmd = ft_strjoin_before_space(argv[3]);
		if (!utils->second_cmd)
			ft_exit(utils, NULL, 1, "Error during the alloc of second_cmd !\n");
		utils->second_cmd_path = ft_strjoin("/", utils->second_cmd);
		if (!utils->second_cmd_path)
			ft_exit(utils, NULL, 1, "The join of cmd2 has failed !\n");
	}
	else
	{
		utils->first_cmd = ft_strdup(argv[3]);
		utils->first_cmd_path = ft_strdup(argv[3]);
	}
	utils->path_output = ft_strdup(argv[4]);
	if (!utils->path_output)
		ft_exit(utils, NULL, 1, "path_output alloc has crashed !\n");
	utils->path_input = ft_strdup(argv[1]);
	if (!utils->path_input)
		ft_exit(utils, NULL, 1, "path_input alloc has crashed !\n");
	ft_init_args2(argv, utils);
}

void	ft_init_arge(char *arge[], t_utils *utils)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (arge[i] != NULL)
	{
		if (arge[i][0] == 'P' && arge[i][1] == 'A' && arge[i][2] == 'T' && \
			arge[i][3] == 'H' && arge[i][4] == '=')
		{
			temp = ft_strdup(arge[i] + 5);
			if (!temp)
				ft_exit(utils, NULL, 1, "The path has a probleme");
			else
				utils->path = ft_split(temp, ':');
			break ;
		}
		i++;
	}
	if (temp != NULL)
		ft_free(temp);
}
