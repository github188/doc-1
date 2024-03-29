/*
 * mqnoyifysigl.c--
 *
 * Copyright (C) 2014,2015,  <li_yunteng@163.com>
 * Auther: liyunteng
 * License: GPL
 * Update time:
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <mqueue.h>
#include <signal.h>
#include "../unpipc.h"

mqd_t	mqd;
void	*buf;
struct mq_attr attr;
struct sigevent sigev;

static void sig_usr1(int);

int main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: mqnotifysig1 <name>\n");

	/* open queue, get attribute, allocate read buffer */
	mqd = mq_open(argv[1], O_RDONLY);
	if (mqd < 0) {
		err_sys("mq open error:");
	}
	if (mq_getattr(mqd, &attr) < 0) {
		err_sys("mq_getattr error:");
	}
	buf = malloc(attr.mq_msgsize);
	if (buf == NULL) {
		err_sys("malloc error:");
	}


	/* establish signal handler, enable notification */
	if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
		err_sys("signal error:");
	}

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	if (mq_notify(mqd, &sigev) < 0) {
		err_sys("mq_notify error:");
	}

	for (;;)
		pause();
	
	return 0;
}
/* 有错误， 因为printf 和 mq_notify mq_recive 都不是异步信号安全的 */
static void sig_usr1(int signo)
{
	ssize_t	n;

	if (mq_notify(mqd, &sigev) < 0) {
		err_sys("mq_notify error:");
	}
	n = mq_receive(mqd, buf, attr.mq_msgsize, NULL);
	if (n < 0) {
		err_sys("mq_receive error:");
	}
	printf("SIGUSR1 received, read %ld bytes\n", (long)n);
	return;
}
