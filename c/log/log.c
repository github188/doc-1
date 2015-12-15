/*
 * log.c -- log
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/12/15 17:57:09
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
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "log.h"
static logfp lfps[256];
pthread_mutex_t logmutex = PTHREAD_MUTEX_INITIALIZER;
/* char logfile[256] = "default.log"; */
/* static LOGLEVEL loglevel = LOG_DEBUG; */
static const char * const LOGLEVELSTR[] = {
        "FATAL",
        "ALERT",
        "CRIT",
        "ERROR",
        "WARNING",
        "NOTICE",
        "INFO",
        "DEBUG",
};

/* static FILE *fp = NULL; */
static inline void makebak(loger *handle)
{
        int bakcnt;
        char old_bakfile[256];
        char new_bakfile[256];
        for (bakcnt = MAX_BAK - 1; bakcnt >=0 ; bakcnt--) {
                snprintf(old_bakfile, sizeof(old_bakfile), "%s.%d", handle->logfile, bakcnt);
                if (!access(old_bakfile, F_OK)) {
                        if (bakcnt == MAX_BAK - 1) {
                                unlink(old_bakfile);
                                continue;
                        } else {
                                snprintf(new_bakfile, sizeof(new_bakfile), "%s.%d", handle->logfile, bakcnt + 1);
                                rename(old_bakfile, new_bakfile);
                        }
                }
        }

        snprintf(new_bakfile, sizeof(new_bakfile), "%s.0", handle->logfile);
        rename(handle->logfile, new_bakfile);
}

loger *log_init(const char *file, LOGLEVEL level)
{
        loger *handler = NULL;

        handler = (loger *)calloc(1, sizeof(loger));
        /* pthread_mutex_init(&handler->mutex, NULL); */

        if (!strlen(file)) {
                file = "default.log";
        }


        int i;
        pthread_mutex_lock(&logmutex);
        for (i = 0; i < 256; i++) {
                if (strcmp(file, lfps[i].logfile) == 0) {
                        handler->lfp = &lfps[i];
                }
        }

        if (!handler->lfp) {
                for (i = 0; i < 256; i++) {
                        if (!lfps[i].fp)  {
                                strncpy(lfps[i].logfile, file, sizeof(lfps[i].logfile));
                                lfps[i].fp = fopen(file, "a+");
                                if (lfps[i].fp == NULL) {
                                        free(handler);
                                        return NULL;
                                }
                                pthread_mutex_init(&lfps[i].mutex, NULL);
                                lfps[i].count = 0;

                                handler->lfp = &lfps[i];
                                fprintf(stderr, "init file : %d\n", i+1);
                                break;
                        }
                }
        }
        pthread_mutex_unlock(&logmutex);
        if (handler->lfp == NULL) {
                fprintf(stderr, "too many files.");
                exit(-1);
        }

        if (level >= LOGLEVEL_DEBUG && level <= LOGLEVEL_FATAL) {
                handler->loglevel = level;
        } else {
                handler->loglevel = LOGLEVEL_DEBUG;
        }

        /* makebak(handler); */

#ifdef SOCKLOG
        handler->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (handler->sockfd == -1) {
                perror("socket");
                free(handler);
                return NULL;
        }
        memset(&handler->addr, 0, sizeof(handler->addr));
        handler->addr.sin_family = AF_INET;
        handler->addr.sin_port = htons(LOGPORT);
        if (inet_pton(AF_INET, LOGSERVER, &handler->addr.sin_addr) < 0) {
                perror("inet_pton");
                close(handler->sockfd);
                free(handler);
                return NULL;
        }
#endif
#ifdef SYSLOG
        openlog("test", LOG_CONS | LOG_PID, 0);
#endif
        handler->self = handler;
        handler->LOG = LOG;
        return handler;
}

static inline void get_time(char *buf, size_t len)
{
        time_t t= time(NULL);
        struct tm now;
        localtime_r(&t, &now);
        snprintf(buf, len, "%04d-%02d-%02d %02d:%02d:%02d", now.tm_year+1990,
                now.tm_mon+1, now.tm_mday, now.tm_hour,
                now.tm_min, now.tm_sec);
}

void LOG(loger *handle,  LOGLEVEL level,const char *format, ...) {
        if (handle == NULL || handle->loglevel < level)
                return;

        char buf[1024];

        int idx = 0;
        va_list args;
        va_start(args, format);
#ifdef VERBOSE
        char timebuf[24];
        get_time(timebuf, sizeof(timebuf));
        idx = snprintf(buf, sizeof(buf) - 1, "%s [%5.5s] ", timebuf,  LOGLEVELSTR[level]);
#endif
        vsnprintf(buf + idx, sizeof(buf) - 1 - idx, format, args);
        va_end(args);
        size_t len = strlen(buf);
        buf[len] = '\n';
        len++;
        buf[len] = '\0';

#ifdef SOCKLOG
        socklen_t addrlen = sizeof(handle->addr);
        sendto(handle->sockfd, buf, len+1, 0, (struct sockaddr *)&handle->addr, addrlen);
        /* close(sockfd); */
#endif


        pthread_mutex_lock(&handle->lfp->mutex);
        struct stat st;
        if (stat(handle->logfile, &st) == 0) {
                if (st.st_size + len  >= MAX_FILESIZE) {
                        makebak(handle);
                        fclose(handle->lfp->fp);
                        handle->lfp->fp = fopen(handle->logfile, "a+");
                }
        }

        size_t a;
        if ((a = fprintf(handle->lfp->fp, "%s", buf)) != len) {
                fprintf(stderr, "fprintf write fail: %lu,  should be: %lu\n",
                        (unsigned long)a, (unsigned long)len);
        }
        /* fflush(handle->fp); */
        /* fclose(handle->fp); */

#ifdef STDERRLOG
        fprintf(stderr, "%s", buf);
#endif

#ifdef SYSLOG
        syslog(level, "%s", buf);
#endif
        handle->count++;
        /* pthread_mutex_unlock(&handle->mutex); */
        pthread_mutex_unlock(&handle->lfp->mutex);
}
