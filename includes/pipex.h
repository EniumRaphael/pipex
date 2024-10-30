/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <rparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:50:20 by rparodi           #+#    #+#             */
/*   Updated: 2024/04/24 09:17:06 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# define UINT_MAX 4294967295
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_utils
{
	char	*path_input;
	char	*path_output;
	char	*first_cmd_args;
	char	*second_cmd_args;
	char	*first_cmd_path;
	char	*second_cmd_path;
	char	*check_first_cmd;
	char	*first_cmd;
	char	*check_second_cmd;
	char	*second_cmd;
	char	**path;
	char	**envp;
	int		fd_output;
	int		fd_input;
}			t_utils;

int		main(int argc, char *argv[], char *args_env[]);
int		ft_fprintf(int fd, const char *str, ...);
int		ft_check_percent_args(int fd, char c, va_list args, int *ret_value);
int		ft_open_fds(t_utils *utils, int *fd, int cmd_count);
char	*ft_check_cmds(t_utils *utils, char *command);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_before_space(char *str);
char	*ft_strdup(const char *s);
void	ft_free(void *ptr);
void	ft_pipex(t_utils *utils);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_exec_cmd(t_utils *utils, char *cmd, char *cmd_args);
void	ft_free_strs(char **strs);
void	ft_check_args(int argc, char *argv[]);
void	ft_errmsg(char *msg);
void	ft_wait(pid_t pid1, pid_t pid2, t_utils *utils, int *fd);
void	ft_close(t_utils *utils, int *fd);
void	ft_exit(t_utils *p1, void *p2, short int exit_status, char *msg);
void	ft_init_arge(char *arge[], t_utils *utils);
void	ft_init_args(char *argv[], t_utils *utils);
void	ft_putnbr_unsigned(int fd, unsigned int nb, int *ret_value);
void	ft_putnbr(int fd, int nb, int *ret_value);
void	ft_putchar(int fd, char c, int *ret_value);
void	ft_free_struct(t_utils *utils);
void	ft_putstr(int fd, char *str, int *ret_value);
void	ft_init_cmd_path(char *argv[], t_utils *utils);
void	ft_putnbr_base(\
unsigned long long nbr, char *base, int *ret_value, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
