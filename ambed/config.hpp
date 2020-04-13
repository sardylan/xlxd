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

#ifndef __AMBED__CONFIG__H
#define __AMBED__CONFIG__H

#include <string>

class Config {

public:

    static Config *getInstance();

    const std::string &getListenAddress() const;

    void setListenAddress(const std::string &value);

    uint16_t getListenPort() const;

    void setListenPort(uint16_t value);

    unsigned int getKeepalivePeriod() const;

    void setKeepalivePeriod(unsigned int value);

    unsigned int getKeepaliveTimeout() const;

    unsigned int getStreamMaxNumber() const;

    void setStreamMaxNumber(unsigned int value);

    void setKeepaliveTimeout(unsigned int value);

    unsigned int getStreamActivityTimeout() const;

    void setStreamActivityTimeout(unsigned int value);

    int getCodecGainAmbePlus() const;

    void setCodecGainAmbePlus(int value);

    int getCodecGainAmbe2Plus() const;

    void setCodecGainAmbe2Plus(int value);

    bool isUseAgc() const;

    void setUseAgc(bool value);

    int getAgcClamping() const;

    void setAgcClamping(int value);

    bool isUseBandPassFilter() const;

    void setUseBandPassFilter(bool value);

private:

    Config();

    ~Config();

    static Config *instance;

    std::string listenAddress;
    uint16_t listenPort;

    unsigned int keepalivePeriod;
    unsigned int keepaliveTimeout;

    unsigned int streamMaxNumber;
    unsigned int streamActivityTimeout;

    int codecGainAMBEPlus;
    int codecGainAMBE2Plus;

    bool useAgc;
    int agcClamping;

    bool useBandPassFilter;
};

#endif
