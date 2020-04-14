/*
 * ambed
 *
 * Created by Jean-Luc Deltombe (LX3JL) on 13/04/2017.
 * Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
 *
 * Extensions created by Luca Cireddu (IS0GVH) on 2020-04-13.
 *
 * This file is part of ambed.
 *
 * xlxd is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * xlxd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __AMBED__CONFIGPARSER__H
#define __AMBED__CONFIGPARSER__H

#include "cconfig.hpp"

class CConfigParser {

public:

    CConfigParser(CConfig *config, int argc, char **argv);

    ~CConfigParser();

    void print();

    bool parse();

private:

    CConfig *config;

    int argc;
    char **argv;

    bool loadConfigFile(const std::string &configFile);

    bool saveConfigFile(const std::string &configFile);

    void printHelp();

    static void printVersion();

    static std::string formatDefault(const std::string &value);

    static std::string format(int value);

    static std::string format(unsigned int value);

    static std::string format(uint16_t value);

    static std::string format(bool value);

    static bool parseBool(const std::string &value);

    static uint16_t parseUInt16(const std::string &value);

    static unsigned int parseUInt32(const std::string &value);

    static int parseInt32(const std::string &value);

};

#endif
