/*
 * log.h -- log
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/12/16 12:16:01
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

#define VERBOSE_TIMEFORMAT "%Y-%m-%d %H:%M:%S"

#define MAX_BAK 4
#define MAX_FILESIZE 100*1024*1024
#define MAX_OPENFILE 256

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
        LOGLEVEL_DEBUG,
        LOGLEVEL_INFO,
        LOGLEVEL_NOTICE,
        LOGLEVEL_WARNING,
        LOGLEVEL_ERROR,
        LOGLEVEL_CRIT,
        // LOGLEVEL_ALERT,
        // LOGLEVEL_EMERG,
#define LOGLEVEL_FATAL  LOGLEVEL_CRIT
#define LOGLEVEL_ERR    LOGLEVEL_ERROR
#define LOG_DEBUG       LOGLEVEL_DEBUG
#define LOG_INFO        LOGLEVEL_INFO
#define LOG_WARNING     LOGLEVEL_WARNING
#define LOG_NOTICE      LOGLEVEL_NOTICE
#define LOG_ERROR       LOGLEVEL_ERROR
#define LOG_CRIT        LOGLEVEL_CRIT
#define LOG_FATAL       LOGLEVEL_FATAL
} LOGLEVEL;


typedef struct {
        FILE *fp;
        char logfile[256];
        pthread_mutex_t mutex;
        size_t count;
}logfp;

typedef struct _loger loger;
struct _loger {
        LOGLEVEL loglevel;
        logfp *lfp;
#ifdef SOCKLOG
        int sockfd;
        struct sockaddr_in addr;
#endif
};

extern pthread_mutex_t logmutex;
extern loger sloger;
loger *log_create(const char *file, LOGLEVEL level);
void mlog(loger *handle, LOGLEVEL level, const char * file, size_t filelen, const char * function, size_t functionlen, long line, const char *format, ...);



#define DEBUG(handle, format, ...)                                      \
        mlog(handle, LOGLEVEL_DEBUG,   __FILE__, sizeof(__FILE__), __FUNCTION__, sizeof(__FUNCTION__), __LINE__, format, __VA_ARGS__);
#define INFO(handle, format, ...)                                       \
        mlog(handle, LOGLEVEL_INFO,    __FILE__, sizeof(__FILE__), __FUNCTION__, sizeof(__FUNCTION__), __LINE__, format, __VA_ARGS__);
#define WARNING(handle, format, ...)                                    \
        mlog(handle, LOGLEVEL_WARNING, __FILE__, sizeof(__FILE__), __FUNCTION__, sizeof(__FUNCTION__), __LINE__, format, __VA_ARGS__);
#define ERROR(handle, format, ...)                                      \
        mlog(handle, LOGLEVEL_ERROR,   __FILE__, sizeof(__FILE__), __FUNCTION__, sizeof(__FUNCTION__), __LINE__, format, __VA_ARGS__);
#define FATAL(handle, format, ...)                                      \
        mlog(handle, LOGLEVEL_FATAL,   __FILE__, sizeof(__FILE__), __FUNCTION__, sizeof(__FUNCTION__), __LINE__, format, __VA_ARGS__);


int slog_init(const char *file, LOGLEVEL level);
void slog(LOGLEVEL level, const char * file, size_t filelen, const char * function, size_t functionlen, long line, const char *format, ...);
#define LOG(level, format, ...)                                         \
        slog(level, __FILE__, sizeof(__FILE__), __FUNCTION__, sizeof(__FUNCTION__), __LINE__, format, __VA_ARGS__);
#define LOG_INIT(file, level)                                           \
        slog_init(file, level);
#endif
