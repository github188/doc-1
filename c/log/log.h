/*
 * log.h -- log
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/12/15 17:28:56
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

#ifndef LOG_H
#define LOG_H
#include <stdio.h>
#include <pthread.h>
#define DEBUG(handle, format, ...) \
        LOG(handle, LOGLEVEL_DEBUG, format, ##__VA_ARGS__);
#define INFO(handle, format, ...) \
        LOG(handle, LOGLEVEL_INFO, format, ##__VA_ARGS__);
#define WARNING(handle, format, ...) \
        LOG(handle, LOGLEVEL_WARNING, format, ##__VA_ARGS__);
#define ERROR(handle, format, ...) \
        LOG(handle, LOGLEVEL_ERROR, format, ##__VA_ARGS__);
#define FATAL(handle, format, ...) \
        LOG(handle, LOGLEVEL_FATAL, format, ##__VA_ARGS__);

#define MAX_BAK 2
#define MAX_FILESIZE 10*1024*1024


#define VERBOSE
// #define SYSLOG
// #define SOCKLOG
// #define STDERRLOG

#ifdef SOCKLOG
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#define LOGSERVER "127.0.0.1"
#define LOGPORT 34567
#endif

#ifdef SYSLOG
#include <syslog.h>
#endif

typedef enum {
        LOGLEVEL_EMERG,
        LOGLEVEL_ALERT,
        LOGLEVEL_CRIT,
#define LOGLEVEL_FATAL LOGLEVEL_CRIT
        LOGLEVEL_ERROR,
#define LOGLEVEL_ERR LOGLEVEL_ERROR
        LOGLEVEL_WARNING,
        LOGLEVEL_NOTICE,
        LOGLEVEL_INFO,
        LOGLEVEL_DEBUG,
} LOGLEVEL;

typedef struct {
        FILE *fp;
        char logfile[256];
        pthread_mutex_t mutex;
        size_t count;
}logfp;

typedef struct _loger loger;
struct _loger {
        char logfile[256];
        LOGLEVEL loglevel;
        logfp *lfp;
        size_t count;
        // pthread_mutex_t mutex;
#ifdef SOCKLOG
        int sockfd;
        struct sockaddr_in addr;
#endif
        loger *self;
        void (*LOG)(loger *handle, LOGLEVEL level,const char *format, ...);
};

extern pthread_mutex_t logmutex;
loger *log_init(const char *file, LOGLEVEL level);
void LOG(loger *handle, LOGLEVEL level,const char *format, ...);

#endif
