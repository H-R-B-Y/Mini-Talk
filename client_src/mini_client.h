/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_client.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:44:00 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/27 16:29:04 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_CLIENT_H
# define MINI_CLIENT_H

# define _GNU_SOURCE

// Standard stuff
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

// For Signals
# include <sys/types.h>
# include <signal.h>

void	send_message(char *str, pid_t server);

void	send_byte(unsigned int b, pid_t server);

void	expect_response(int sig, siginfo_t *info, void *ucontext);

#endif