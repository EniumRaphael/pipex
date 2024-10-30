/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:46:00 by rparodi           #+#    #+#             */
/*   Updated: 2024/04/24 09:16:54 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_init_cmd_path(char *argv[], t_utils *utils)
{
	if (access(argv[2], X_OK) == -1)
	{
		utils->first_cmd = ft_strjoin_before_space(argv[2]);
		if (!utils->first_cmd)
			ft_exit(utils, NULL, 1, "Error during the alloc of first_cmd !\n");
		utils->first_cmd_path = ft_strjoin("/", utils->first_cmd);
		if (!utils->first_cmd_path)
			ft_exit(utils, NULL, 1, "The join of cmd 1 has failed !\n");
	}
	else
	{
		utils->first_cmd = ft_strdup(argv[2]);
		utils->first_cmd_path = ft_strdup(argv[2]);
	}
}

int	ft_check_path(char *arge[])
{
	size_t	i;

	i = 0;
	while (arge[i] != NULL)
	{
		if (arge[i][0] == 'P' && arge[i][1] == 'A' && arge[i][2] == 'T' && \
			arge[i][3] == 'H' && arge[i][4] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *maiboyerlpb[])
{
	t_utils	*utils;

	ft_check_args(argc, argv);
	if (ft_check_path(maiboyerlpb) == 0 || !argv[0])
		ft_exit(NULL, NULL, 1, "The path is not set!\n");
	utils = (t_utils *)malloc(sizeof(t_utils));
	if (!utils)
		ft_exit(NULL, NULL, 1, "The allocation of the struct has crashed!\n");
	utils->envp = maiboyerlpb;
	ft_init_arge(maiboyerlpb, utils);
	ft_init_args(argv, utils);
	utils->check_first_cmd = ft_check_cmds(utils, utils->first_cmd_path);
	utils->check_second_cmd = ft_check_cmds(utils, utils->second_cmd_path);
	ft_pipex(utils);
	ft_exit(utils, NULL, 0, "");
	return (0);
}
