/*
 * xlxd
 *
 * Created by Jean-Luc Deltombe (LX3JL) on 31/10/2015.
 * Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
 *
 * Modified by Luca Cireddu (IS0GVH)
 *
 * ----------------------------------------------------------------------------
 * This file is part of xlxd.
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
 * ----------------------------------------------------------------------------
 *
 */


#include "config.hpp"
#include "default.hpp"

XLXConfig *XLXConfig::instance = nullptr;

XLXConfig::XLXConfig() {
    XLXConfig::callsign = CONFIG_CALLSIGN_DEFAULT;
    XLXConfig::listenIp = CONFIG_LISTEN_IP_DEFAULT;
    XLXConfig::transcodedIp = CONFIG_TRANSCODER_IP_DEFAULT;
}

XLXConfig::~XLXConfig() = default;

XLXConfig* XLXConfig::getInstance() {
    if (XLXConfig::instance == nullptr)
        XLXConfig::instance = new XLXConfig();

    return XLXConfig::instance;
}

const std::string &XLXConfig::getCallsign() const {
    return callsign;
}

void XLXConfig::setCallsign(const std::string &value) {
    XLXConfig::callsign = value;
}

const std::string &XLXConfig::getListenIp() const {
    return listenIp;
}

void XLXConfig::setListenIp(const std::string &value) {
    XLXConfig::listenIp = value;
}

const std::string &XLXConfig::getTranscodedIp() const {
    return transcodedIp;
}

void XLXConfig::setTranscodedIp(const std::string &value) {
    XLXConfig::transcodedIp = value;
}
