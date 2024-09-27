/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:43:26 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/27 16:58:31 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_client.h"

static pid_t	g_server_pid;

void	send_byte(unsigned int b, pid_t server)
{
	short	index;

	index = 0;
	while (index < 8)
	{
		b = (b >> (!!index));
		if ((b & 1) >= 1)
			kill(server, SIGUSR1);
		else
			kill(server, SIGUSR2);
		index++;
		usleep(500);
	}
}

void	send_message(char *str, pid_t server)
{
	size_t	len;
	size_t	index;

	len = ft_strlen(str);
	index = 0;
	while (index <= len)
		send_byte(str[index++], server);
	return ;
}

void	expect_response(int sig, siginfo_t *info, void *ucontext)
{
	(void) sig;
	(void) ucontext;
	if (info->si_pid != g_server_pid)
		return ;
	ft_putstr_fd("Server sent OK! response!\n", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	size_t				index;
	struct sigaction	sa_high;

	index = 0;
	if (argc != 3)
		return (1);
	while (argv[1][index] && ft_isdigit(argv[1][index]))
		index++;
	g_server_pid = ft_atoi(argv[1]);
	if (index != ft_strlen(argv[1]) || !g_server_pid)
		return (2);
	sa_high.sa_flags = SA_SIGINFO;
	sigemptyset(&sa_high.sa_mask);
	sa_high.sa_sigaction = &expect_response;
	sigaction(SIGUSR1, &sa_high, 0);
	send_message(argv[2], g_server_pid);
	while (1)
		sleep(1);
	return (1);
}
