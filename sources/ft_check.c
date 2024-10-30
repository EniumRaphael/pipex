/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:15:49 by rparodi           #+#    #+#             */
/*   Updated: 2024/04/24 09:19:46 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc > 5)
		ft_exit(NULL, NULL, 1, "Too many arguments !\n");
	else if (argc < 5)
		ft_exit(NULL, NULL, 1, "Not enough arguments !\n");
	while (i <= 4)
	{
		if (argv[i][0] == '\0')
			ft_exit(NULL, NULL, 1, "The args are not valid !\n");
		i++;
	}
	if ((argv[2][0] == '.' && argv[2][1] == '\0') || \
			(argv[3][0] == '.' && argv[3][1] == '\0'))
		ft_exit(NULL, NULL, 1, "Don't have enought args\n");
	if (access(argv[1], R_OK) == -1)
		ft_exit(NULL, NULL, 1, "Don't have access of file 1\n");
}

char	*ft_check_cmds(t_utils *utils, char *command)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (access(command, X_OK) != -1)
		return (ft_strdup(command));
	else if (command && ft_strlen(command) != 1)
	{
		while (utils->path[i] != NULL)
		{
			if (str)
				ft_free(str);
			str = ft_strjoin(utils->path[i], command);
			if (str == NULL)
				ft_exit(utils, NULL, 1, \
			"The alloc to check_cmds has crashed !\n");
			if (access(str, F_OK) == -1 || access(str, X_OK) == -1)
				i++;
			else
				return (str);
		}
	}
	return (ft_exit(utils, str, 1, "No commands found !\n"), NULL);
}
