/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_server.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 20:44:35 by hbreeze           #+#    #+#             */
/*   Updated: 2024/09/27 19:13:27 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SERVER_H
# define MINI_SERVER_H

# define _GNU_SOURCE

// Standard stuff
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

// For Signals
# include <sys/types.h>
# include <signal.h>

// index =     7 6 5 4 3 2 1 0
// word  =  0b 0 0 0 0 0 0 0 0;

typedef struct message_chunk_s
{
	unsigned int			word;
	size_t					index;
	struct message_chunk_s	*next;
}	t_chunk;

typedef struct signal_sender_s
{
	pid_t					client_pid;
	struct message_chunk_s	*msg_start;
	int						msg_terminated;
	struct signal_sender_s	*next_pid;
}	t_sig_sender;

void			*zeroit(void *ptr, size_t n);
void			free_message(t_chunk *this_chunk);
void			print_new_message(t_chunk *this_chunk);

t_chunk			*create_chunk(void);
t_chunk			*last_chunk(t_chunk *start);
t_sig_sender	*create_client(pid_t pid);
t_sig_sender	*last_client(t_sig_sender *start);

void			check_new_message(void);
void			handle_low_signal(int sig, siginfo_t *info, void *ucontext);
void			handle_high_signal(int sig, siginfo_t *info, void *ucontext);
t_sig_sender	*get_client(pid_t pid);

#endif