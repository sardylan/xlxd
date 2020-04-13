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

#ifndef __AMBED__CONFIG_DEFAULT__H
#define __AMBED__CONFIG_DEFAULT__H

#define AMBED_CONFIG_LISTEN_ADDRESS_DEFAULT "0.0.0.0";
#define AMBED_CONFIG_LISTEN_PORT_DEFAULT 10100;

#define AMBED_CONFIG_KEEPALIVE_PERIOD_DEFAULT 5;
#define AMBED_CONFIG_KEEPALIVE_TIMEOUT_DEFAULT 30;

#define AMBED_CONFIG_STREAM_MAX_NUMBER_DEFAULT 99;
#define AMBED_CONFIG_STREAM_ACTIVITY_TIMEOUT_DEFAULT 3;

#define AMBED_CONFIG_CODEC_GAIN_AMBEPLUS_DEFAULT -10;
#define AMBED_CONFIG_CODEC_GAIN_AMBE2PLUS_DEFAULT +10;

#define AMBED_CONFIG_USE_AGC_DEFAULT false;
#define AMBED_CONFIG_AGC_CLAMPING_DEFAULT 3;

#define AMBED_CONFIG_USE_BAND_PASS_FILTER_DEFAULT true;

#endif
