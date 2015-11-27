/*
 * wuclient.cpp -- weather update client
 *
 * Copyright (C) 2015 liyunteng
 * Auther: liyunteng <li_yunteng@163.com>
 * License: GPL
 * Update time:  2015/05/28 13:10:31
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
#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
    zmq::context_t context(1);
    std::cout << "Collecting updates from weather server..." << std::endl;
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");

    const char *filter = (argc > 1) ? argv[1]: "10001 ";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen(filter));


    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr ++) {
        zmq::message_t update;
        int zipcode, temperature, relhumidity;
        subscriber.recv(&update);

        std::istringstream iss(static_cast<char *>(update.data()));
        iss >> zipcode >> temperature >> relhumidity;

        total_temp += temperature;
    }

    std::cout << "Average temperature for zipcode '" << filter
              <<"' was " << (int)(total_temp / update_nbr) << "F"
              << std::endl;

    return 0;
}
