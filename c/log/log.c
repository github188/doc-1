/*
 * log.c -- log
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/12/16 19:41:29
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
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "log.h"

pthread_mutex_t logmutex = PTHREAD_MUTEX_INITIALIZER;
static logfp lfps[MAX_OPENFILE] = {
        {.fp = NULL, .logfile = "default.log", .count = 0},
        /* {.fd = -1, .logfile = "default.log", .count = 0}, */
};
loger sloger = {
        .loglevel = LOGLEVEL_DEBUG,
        .lfp = &lfps[0],
};

static const char * const LOGLEVELSTR[] = {
        "NONE",
        "EMERG",
        "ALERT",
        "FATAL",
        "ERROR",
        "WARN",
        "NOTICE",
        "INFO",
        "DEBUG",
};

static inline void makebak(const char *filename)
{
        int bakcnt;
        char old_bakfile[256];
        char new_bakfile[256];
        if (access(filename, F_OK)) {
                return ;
        }
        bakcnt = MAX_BAK;
        while (bakcnt >= 0) {
                if (bakcnt == 0) {
                        snprintf(old_bakfile, sizeof(old_bakfile), "%s", filename);
                } else {
                        snprintf(old_bakfile, sizeof(old_bakfile), "%s.%d", filename, bakcnt-1);
                }
                if(!access(old_bakfile, F_OK)) {
                        if (bakcnt == MAX_BAK) {
                                unlink(old_bakfile);
                                continue;
                        } else {
                                snprintf(new_bakfile, sizeof(new_bakfile), "%s.%d", filename, bakcnt);
                                rename(old_bakfile, new_bakfile);

                        }
                }
        }

#if 0
        for (bakcnt = MAX_BAK - 1; bakcnt >=0 ; bakcnt--) {
                if (bakcnt == 0){
                        snprintf(old_bakfile, sizeof(old_bakfile), "%s", filename);
                        snprintf(new_bakfile, sizeof(new_bakfile), "%s.%d", filename, bakcnt);
                } else {
                        snprintf(old_bakfile, sizeof(old_bakfile), "%s.%d", filename, bakcnt);
                        snprintf(new_bakfile, sizeof(new_bakfile), "%s.%d", filename, bakcnt+1);
                }
                if (!access(old_bakfile, F_OK) && (bakcnt == MAX_BAK -1)) {
                                unlink(old_bakfile);
                                continue;
                }
                snprintf(new_bakfile, sizeof(new_bakfile), "%s.%d", filename, bakcnt + 1);
                rename(old_bakfile, new_bakfile);
        }
#endif

}

loger *log_create(const char *file, LOGLEVEL level)
{
        loger *handler = NULL;

        handler = (loger *)calloc(1, sizeof(loger));

        if (!strlen(file)) {
                file = "default.log";
        }

        int i;
        pthread_mutex_lock(&logmutex);
        for (i = 0; i < MAX_OPENFILE; i++) {
                if (strcmp(file, lfps[i].logfile) == 0) {
                        handler->lfp = &lfps[i];
                        break;
                }
        }

        if (!handler->lfp) {
                for (i = 0; i < MAX_OPENFILE; i++) {
                        if (!lfps[i].fp)  {
                        /* if (lfps[i].fd == -1) { */
                                strncpy(lfps[i].logfile, file, sizeof(lfps[i].logfile));
                                makebak(handler->lfp->logfile);
                                lfps[i].fp = fopen(file, "a+");
                                if (lfps[i].fp == NULL) {
                                        free(handler);
                                        return NULL;
                                }
                                lfps[i].count = 0;
                                lfps[i].countbyte = 0;
                                lfps[i].writefail = 0;
                                lfps[i].bakcount = 0;

                                /*
                                 * lfps[i].fd = open(file, O_CREAT|O_APPEND | O_WRONLY, FILEPERM);
                                 * if (lfps[i].fd < 0) {
                                 *         free(handler);
                                 *         return NULL;
                                 * }
                                 */

                                pthread_mutex_init(&lfps[i].mutex, NULL);

                                handler->lfp = &lfps[i];
                                break;
                        }
                }
        }

        pthread_mutex_unlock(&logmutex);
        if (handler->lfp == NULL) {
                fprintf(stderr, "too many files.");
                exit(-1);
        }

        if (level <= LOGLEVEL_DEBUG && level >= LOGLEVEL_NONE) {
                handler->loglevel = level;
        } else {
                handler->loglevel = LOGLEVEL_DEBUG;
        }



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
        /* openlog("test", LOG_CONS | LOG_PID, 0); */
#endif
        return handler;
}

void vlog(loger *handle, LOGLEVEL level, const char *file, size_t filelen,
          const char *function, size_t functionlen, long line, const char *format, va_list args)
{
        if (handle == NULL || handle->loglevel < level)
                return;

        char buf[BUFSZ];

        int idx = 0;
#ifdef VERBOSE
        char timebuf[24];
        time_t t= time(NULL);
        struct tm now;
        localtime_r(&t, &now);
        strftime(timebuf, sizeof(timebuf), VERBOSE_TIMEFORMAT, &now);
        idx = snprintf(buf, sizeof(buf), "%s [%-5.5s]  %s %s():%ld ",
                       timebuf, LOGLEVELSTR[level], file, function, line);
#endif
        int n = vsnprintf(buf + idx, sizeof(buf) - idx, format, args);
        if (n < 0) {
                fprintf(stderr, "vsnprintf failed\n");
                return ;
        }

        size_t len = n + idx;
        if (len >= sizeof(buf)) {
                fprintf(stderr, "msg too long, truancated.\n");
                len = sizeof(buf) - 1;
                buf[len-1] = '\n';
                buf[len] = '\0';
        } else {
                buf[len] = '\n';
                len++;
                buf[len] = '\0';
        }

#ifdef SOCKLOG
        socklen_t addrlen = sizeof(handle->addr);
        sendto(handle->sockfd, buf, len+1, 0, (struct sockaddr *)&handle->addr, addrlen);
        /* close(sockfd); */
#endif

        pthread_mutex_lock(&handle->lfp->mutex);
        /* pthread_mutex_lock(&logmutex); */
        struct stat st;
        if (stat(handle->lfp->logfile, &st) == 0) {
                if (MAX_BAK > 0 && (st.st_size + len  >= MAX_FILESIZE)) {
                        /* fprintf(stderr, "size: %lu, len: %lu\n", (unsigned long)st.st_size, (unsigned long)len); */
                        fclose(handle->lfp->fp);
                        makebak(handle->lfp->logfile);
                        handle->lfp->bakcount++;
                        handle->lfp->fp = fopen(handle->lfp->logfile, "a+");
                        /*
                         * close(handle->lfp->fd);
                         * handle->lfp->fd = open(handle->lfp->logfile, O_CREAT | O_APPEND | O_WRONLY, FILEPERM);
                         */
                }
        }

        /* write(handle->lfp->fd, buf, len); */
        if (fprintf(handle->lfp->fp, "%s", buf) != (int)len) {
                perror("fprintf");
                handle->lfp->writefail ++;
        } else {
                handle->lfp->count ++;
                handle->lfp->countbyte += len;
        }
        /* fflush(handle->lfp->fp); */
        /* fclose(handle->fp); */

#ifdef STDERRLOG
        fprintf(stderr, "%s", buf);
#endif

#ifdef SYSLOG
        syslog(level, "%s", buf);
#endif
        /* handle->lfp->count++; */
        /* pthread_mutex_unlock(&logmutex); */
        pthread_mutex_unlock(&handle->lfp->mutex);
}

void mlog(loger *handle, LOGLEVEL level, const char *file, size_t filelen,
         const char *function, size_t functionlen, long line, const char *format, ...)
{
#if 1
        va_list args;
        va_start(args, format);
        vlog(handle, level, file, filelen, function, functionlen, line, format, args);
        va_end(args);
        return;
#endif
#if 0
        if (handle == NULL || handle->loglevel < level)
                return;

        char buf[BUFSZ];

        int idx = 0;
#ifdef VERBOSE
        char timebuf[24];
        time_t t= time(NULL);
        struct tm now;
        localtime_r(&t, &now);
        strftime(timebuf, sizeof(timebuf), VERBOSE_TIMEFORMAT, &now);
        idx = snprintf(buf, sizeof(buf), "%s [%-5.5s] %lu(%lu) %s %s():%ld ",
                       timebuf, LOGLEVELSTR[level], (unsigned long)getpid(), (unsigned long)pthread_self(), file, function, line);
#endif
        va_list args;
        va_start(args, format);
        int n = vsnprintf(buf + idx, sizeof(buf) - idx, format, args);
        va_end(args);
        if (n < 0) {
                fprintf(stderr, "vsnprintf failed\n");
                return ;
        }

        size_t len = n + idx;
        if (len >= sizeof(buf)) {
                fprintf(stderr, "msg too long, truancated.\n");
                len = sizeof(buf) - 1;
                buf[len-1] = '\n';
                buf[len] = '\0';
        } else {
                buf[len] = '\n';
                len++;
                buf[len] = '\0';
        }

#ifdef SOCKLOG
        socklen_t addrlen = sizeof(handle->addr);
        sendto(handle->sockfd, buf, len+1, 0, (struct sockaddr *)&handle->addr, addrlen);
        /* close(sockfd); */
#endif

        pthread_mutex_lock(&handle->lfp->mutex);
        /* pthread_mutex_lock(&logmutex); */
        struct stat st;
        if (stat(handle->lfp->logfile, &st) == 0) {
                if (st.st_size + len  >= MAX_FILESIZE) {
                        /* fprintf(stderr, "size: %lu, len: %lu\n", (unsigned long)st.st_size, (unsigned long)len); */
                        fclose(handle->lfp->fp);
                        makebak(handle->lfp->logfile);
                        handle->lfp->bakcount++;
                        handle->lfp->fp = fopen(handle->lfp->logfile, "a+");

                        /*
                         * close(handle->lfp->fd);
                         * handle->lfp->fd = open(handle->lfp->logfile, O_CREAT | O_APPEND | O_WRONLY, FILEPERM);
                         */
                }
        }

        /* write(handle->lfp->fd, buf, len); */
        if (fprintf(handle->lfp->fp, "%s", buf) != (int)len) {
                perror("fprintf");
                handle->lfp->writefail ++;
        } else {
                handle->lfp->count ++;
                handle->lfp->countbyte += len;
        }
        /* fflush(handle->lfp->fp); */
        /* fclose(handle->fp); */

#ifdef STDERRLOG
        fprintf(stderr, "%s", buf);
#endif

#ifdef SYSLOG
        syslog(level, "%s", buf);
#endif
        /* handle->lfp->count++; */
        /* pthread_mutex_unlock(&logmutex); */
        pthread_mutex_unlock(&handle->lfp->mutex);
#endif
}


int slog_init(const char *file, LOGLEVEL level)
{

        pthread_mutex_lock(&logmutex);
        if (strlen(file)) {
                strncpy(lfps[0].logfile, file, sizeof(lfps[0].logfile));
        }
        makebak(lfps[0].logfile);
        lfps[0].fp = fopen(lfps[0].logfile, "a+");
        if (lfps[0].fp == NULL) {
                return -1;
        }
        /*
         * lfps[0].fd = open(lfps[0].logfile, O_CREAT | O_APPEND | O_WRONLY, FILEPERM);
         * if (lfps[0].fd < 0)
         *         return -1;
         */

        pthread_mutex_init(&lfps[0].mutex, NULL);
        lfps[0].count = 0;
        lfps[0].countbyte = 0;
        lfps[0].writefail = 0;
        lfps[0].bakcount = 0;
        pthread_mutex_unlock(&logmutex);

        if (level <= LOGLEVEL_DEBUG && level >= LOGLEVEL_NONE) {
                sloger.loglevel = level;
        }
#ifdef SOCKLOG
        sloger.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sloger.sockfd == -1) {
                perror("socket");
                return -1;
        }
        memset(&sloger.addr, 0, sizeof(sloger.addr));
        sloger.addr.sin_family = AF_INET;
        sloger.addr.sin_port = htons(LOGPORT);
        if (inet_pton(AF_INET, LOGSERVER, &sloger.addr.sin_addr) < 0) {
                perror("inet_pton");
                close(sloger.sockfd);
                return -1;
        }
#endif
#ifdef SYSLOG
        /* openlog("test", LOG_CONS | LOG_PID, 0); */
#endif
        return 0;
}

void slog(LOGLEVEL level, const char * file, size_t filelen, const char * function, size_t functionlen, long line, const char *format, ...)
{
        va_list args;
        va_start(args, format);
        vlog(&sloger, level, file, filelen, function, functionlen, line, format,  args);
        va_end(args);
        return ;
#if 0
        if (sloger.loglevel < level)
                return;

        char buf[BUFSZ];

        int idx = 0;
#ifdef VERBOSE
        char timebuf[24];
        time_t t= time(NULL);
        struct tm now;
        localtime_r(&t, &now);
        strftime(timebuf, sizeof(timebuf), VERBOSE_TIMEFORMAT, &now);
        idx = snprintf(buf, sizeof(buf), "%s [%-5.5s] %lu(%lu) %s %s():%ld ",
                       timebuf, LOGLEVELSTR[level], (unsigned long)getpid(),(unsigned long)pthread_self(), file, function, line);
#endif
        va_list args;
        va_start(args, format);
        int n = vsnprintf(buf + idx, sizeof(buf) - idx, format, args);
        va_end(args);

        size_t len = n + idx;
        if (len >= sizeof(buf)) {
                fprintf(stderr, "msg too long, truancated.\n");
                len = sizeof(buf) - 1;
                buf[len-1] = '\n';
                buf[len] = '\0';
        } else {
                buf[len] = '\n';
                len++;
                buf[len] = '\0';
        }


#ifdef SOCKLOG
        socklen_t addrlen = sizeof(sloger.addr);
        sendto(sloger.sockfd, buf, len+1, 0, (struct sockaddr *)&sloger.addr, addrlen);
        /* close(sockfd); */
#endif

        /* pthread_mutex_lock(&logmutex); */
        pthread_mutex_lock(&sloger.lfp->mutex);
        if (sloger.lfp->fp == NULL) {
                sloger.lfp->fp = fopen(sloger.lfp->logfile, "a+");
        }
        /*
         * if (sloger.lfp->fd == -1) {
         *         sloger.lfp->fd = open(sloger.lfp->logfile, O_CREAT | O_APPEND | O_WRONLY, FILEPERM);
         * }
         */
        struct stat st;
        if (stat(sloger.lfp->logfile, &st) == 0) {
                if (st.st_size + len  >= MAX_FILESIZE) {
                        /* fprintf(stderr, "size: %lu, len: %lu\n", (unsigned long)st.st_size, (unsigned long)len); */
                        fclose(sloger.lfp->fp);
                        makebak(sloger.lfp->logfile);
                        sloger.lfp->bakcount++;
                        sloger.lfp->fp = fopen(sloger.lfp->logfile, "a+");

                        /*
                         * close(sloger.lfp->fd);
                         * sloger.lfp->fd = open(sloger.lfp->logfile, O_CREAT | O_APPEND | O_WRONLY, FILEPERM);
                         */
                }
        } else {
                perror("stat");
        }

        /*
         * if (write(sloger.lfp->fd, buf, len) != (ssize_t)len) {
         *         perror("write");
         *         sloger.lfp->writefail ++;
         * } else {
         *         sloger.lfp->count++;
         *         sloger.lfp->countbyte += len;
         * }
         */
        if (fprintf(sloger.lfp->fp, "%s", buf) != (int)len) {
                perror("fprintf\n");
                sloger.lfp->writefail ++;
        } else {
                sloger.lfp->count++;
                sloger.lfp->countbyte += len;
        }
        /* fflush(sloger.lfp->fp); */
        /* fclose(handle->fp); */

#ifdef STDERRLOG
        fprintf(stderr, "%s", buf);
#endif

#ifdef SYSLOG
        syslog(level, "%s", buf);
#endif
        /* pthread_mutex_unlock(&logmutex); */
        pthread_mutex_unlock(&sloger.lfp->mutex);
#endif
}

void log_dump()
{
        int i;
        for (i = 0; i < MAX_OPENFILE; i++) {
                if (lfps[i].fp != NULL) {
                        fprintf(stderr, "logfile: %s\nsuccess:%llu\nsuccessSize:%llu\nwritefail:%lu\nbakcount:%lu\n\n",
                                lfps[i].logfile,
                                (unsigned long long)lfps[i].count, (unsigned long long)lfps[i].countbyte,
                                (unsigned long)lfps[i].writefail, (unsigned long)lfps[i].bakcount);

                }
        }
}
