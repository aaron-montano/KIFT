/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_app.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 14:17:30 by smonroe           #+#    #+#             */
/*   Updated: 2018/10/01 01:25:06 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kift.h"

void	init_env(int n)
{
	char	buf[1];

	buf[0] = 0;
	if (n == 1)
	{
		ft_putstr("Running Backend\n");
		system("sh back.sh");
		ft_putstr("Press enter when Backend loads to run Frontend");
		read(0, buf, 1);
	}
	else if (n == 2)
	{
		ft_putstr("Running Frontend\n");
		system("sh front.sh");
		ft_putstr("Press enter when Frontend loads to run Web Interface");
		read(0, buf, 1);
		system("open \"http://localhost:8000/#/kift\" &");
	}
}

void	dispatch_dos(char *com)
{
	if (CHK("VOLUMEHALF"))
		system("./shell/volume_half");
	else if (CHK("VOLUMEMAX"))
		system("./shell/volume_max");
	else if (CHK("VOLUMEMIN"))
		system("./shell/volume_mute");
	else if (CHK("WHATSHAPPENING"))
		system("./shell/events.command");
	else if (CHK("WHATSTHEWEATHER"))
		system("./shell/weather");
	else if (CHK("WHEREAMI"))
		system("./shell/where_am_i");
	else if (CHK("WHOAMI"))
		system("./shell/who_am_i");
	else if (CHK("WHYAMI"))
		system("./shell/why_am_i");
}

void	dispatch(char *com)
{
	if (CHK("CHECKDATE"))
		system("./shell/date");
	else if (CHK("CHECKTIME"))
		system("./shell/time");
	else if (CHK("CHECKTRAFFIC"))
		system("./shell/traffic.command");
	else if (CHK("GOOGLESEARCH"))
		system("./shell/google.command");
	else if (CHK("HISTORY"))
		system("./shell/history");
	else if (CHK("KIFTSENDEMAIL"))
		system("./shell/send_email");
	else if (CHK("LOCKSCREEN"))
		system("./shell/lock");
	else if (CHK("PLAYMUSIC"))
		system("./shell/play_music");
	else if (CHK("STARTTIMERLONG"))
		system("./shell/timer_long");
	else if (CHK("STARTTIMERSHORT"))
		system("./shell/timer_short");
	else if (CHK("STOPSONG"))
		system("./shell/stop_music");
	else
		dispatch_dos(com);
}

void	execute(int sock)
{
	int		ret;
	char	com[BUFF + 1];

	init_env(2);
	ret = BUFF + 1;
	while (1)
	{
		bzero(com, ret);
		ret = read(sock, com, BUFF);
		write(1, com, ret);
		if (ret)
		{
			if (CHK("BRIGHTNESSDOWN"))
				system("osascript shell/bright_down.scpt");
			else if (CHK("BRIGHTNESSMAX"))
				system("osascript shell/bright_max.scpt");
			else if (CHK("BRIGHTNESSMIN"))
				system("osascript shell/bright_min.scpt");
			else if (CHK("BRIGHTNESSUP"))
				system("osascript shell/bright_up.scpt");
			else
				dispatch(&com[0]);
		}
	}
}

int		main(void)
{
	struct sockaddr_in	server;
	int					sock;

	init_env(1);
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		ft_putstr("APP: Error: Socket\n");
		exit(1);
	}
	ft_memset(&server, '0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0)
	{
		ft_putstr("APP: Error: Invalid address || Unsupported format\n");
		exit(1);
	}
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		ft_putstr("APP: Error: Connection Failed\n");
		exit(1);
	}
	execute(sock);
	close(sock);
	return (0);
}
