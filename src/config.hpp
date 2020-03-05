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

#ifndef __XLXD__CONFIG__H
#define __XLXD__CONFIG__H

#include <string>

class XLXConfig {

public:

    static XLXConfig *getInstance();

    const std::string &getCallsign() const;

    void setCallsign(const std::string &);

    const std::string &getListenIp() const;

    void setListenIp(const std::string &);

    const std::string &getTranscodedIp() const;

    void setTranscodedIp(const std::string &);

private:

    XLXConfig();

    virtual ~XLXConfig();

    static XLXConfig *instance;

    std::string callsign;
    std::string listenIp;
    std::string transcodedIp;

};

#endif
