/*
 * wuserver.cpp -- weather update server
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/05/28 13:10:49
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

#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define within(num) (int)((float)(num) * random() / (RAND_MAX + 1.0))

int main(int argc, char *argv[])
{
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5556");
    publisher.bind("ipc://weather.ipc");

    srandom((unsigned) time(NULL));
    while(1) {
        int zipcode, temperature, relhumidity;

        zipcode = within(100000);
        temperature = within(215) - 80;
        relhumidity = within(50) + 10;

        zmq::message_t message(20);
        snprintf((char *)message.data(), 20,
                 "%05d %d %d", zipcode, temperature, relhumidity);
        publisher.send(message);

    }
    return 0;
}
