/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 01:07:40 by smonroe           #+#    #+#             */
/*   Updated: 2018/10/01 01:08:53 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

void	err(char *s)
{
	write(2, s, ft_strlen(s));
	exit(1);
}

void	store_log(char *user, char *line)
{
	int		fd;
	off_t	end;

	if ((fd = open(user, O_WRONLY | O_APPEND)) == -1)
		if ((fd = open(user, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
			err("Could not create file");
	end = lseek(fd, 0, SEEK_END);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
}

void	get_log(char *user)
{
	int		fd;
	int		ret;
	char	buf[1024];

	if (access(user, F_OK) == -1)
		err("No logs to show. Please Speak a command first.");
	if ((fd = open(user, O_RDONLY)) == -1)
		err("File can't be opened");
	else
	{
		while ((ret = read(fd, buf, 1024)) > 0)
			write(1, buf, ret);
		close(fd);
	}
}

uint8_t	get_arg(int ac, char **av)
{
	if (av[1][1] == 's' && ac < 4)
		return ('?');
	if (av[1][0] == '-' && av[1][1] && ac >= 3)
		return ((uint8_t)av[1][1]);
	else
		return ('?');
}

int		main(int ac, char **av)
{
	uint8_t		opt;

	if (ac == 1)
		return (1);
	opt = get_arg(ac, av);
	if (opt == '?')
		return (1);
	else if (opt == 's')
		store_log(av[2], av[3]);
	else if (opt == 'g')
		get_log(av[2]);
	else if (opt == 'c')
		if (remove(av[2]) == 0)
			ft_printf("Deleted logs successfully\n");
	return (0);
}
