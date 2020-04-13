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

#include "config.hpp"
#include "config_default.hpp"

Config *Config::instance = nullptr;

Config::Config() {
    listenAddress = AMBED_CONFIG_LISTEN_ADDRESS_DEFAULT;
    listenPort = AMBED_CONFIG_LISTEN_PORT_DEFAULT;

    keepalivePeriod = AMBED_CONFIG_KEEPALIVE_PERIOD_DEFAULT;
    keepaliveTimeout = AMBED_CONFIG_KEEPALIVE_TIMEOUT_DEFAULT;

    streamMaxNumber = AMBED_CONFIG_STREAM_MAX_NUMBER_DEFAULT;
    streamActivityTimeout = AMBED_CONFIG_STREAM_ACTIVITY_TIMEOUT_DEFAULT;

    codecGainAMBEPlus = AMBED_CONFIG_CODEC_GAIN_AMBEPLUS_DEFAULT;
    codecGainAMBE2Plus = AMBED_CONFIG_CODEC_GAIN_AMBE2PLUS_DEFAULT;

    useAgc = AMBED_CONFIG_USE_AGC_DEFAULT;
    agcClamping = AMBED_CONFIG_AGC_CLAMPING_DEFAULT;

    useBandPassFilter = AMBED_CONFIG_USE_BAND_PASS_FILTER_DEFAULT;
}

Config::~Config() = default;

Config *Config::getInstance() {
    if (Config::instance == nullptr)
        Config::instance = new Config();

    return Config::instance;
}

const std::string &Config::getListenAddress() const {
    return listenAddress;
}

void Config::setListenAddress(const std::string &value) {
    Config::listenAddress = value;
}

uint16_t Config::getListenPort() const {
    return listenPort;
}

void Config::setListenPort(uint16_t value) {
    Config::listenPort = value;
}

unsigned int Config::getKeepalivePeriod() const {
    return keepalivePeriod;
}

void Config::setKeepalivePeriod(unsigned int value) {
    Config::keepalivePeriod = value;
}

unsigned int Config::getKeepaliveTimeout() const {
    return keepaliveTimeout;
}

void Config::setKeepaliveTimeout(unsigned int value) {
    Config::keepaliveTimeout = value;
}

unsigned int Config::getStreamMaxNumber() const {
    return streamMaxNumber;
}

void Config::setStreamMaxNumber(unsigned int value) {
    Config::streamMaxNumber = value;
}

unsigned int Config::getStreamActivityTimeout() const {
    return streamActivityTimeout;
}

void Config::setStreamActivityTimeout(unsigned int value) {
    Config::streamActivityTimeout = value;
}

int Config::getCodecGainAmbePlus() const {
    return codecGainAMBEPlus;
}

void Config::setCodecGainAmbePlus(int value) {
    codecGainAMBEPlus = value;
}

int Config::getCodecGainAmbe2Plus() const {
    return codecGainAMBE2Plus;
}

void Config::setCodecGainAmbe2Plus(int value) {
    codecGainAMBE2Plus = value;
}

bool Config::isUseAgc() const {
    return useAgc;
}

void Config::setUseAgc(bool value) {
    Config::useAgc = value;
}

int Config::getAgcClamping() const {
    return agcClamping;
}

void Config::setAgcClamping(int value) {
    Config::agcClamping = value;
}

bool Config::isUseBandPassFilter() const {
    return useBandPassFilter;
}

void Config::setUseBandPassFilter(bool value) {
    Config::useBandPassFilter = value;
}
