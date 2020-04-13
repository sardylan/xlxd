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

#include "cconfig.hpp"
#include "cconfig_default.hpp"

CConfig *CConfig::instance = nullptr;

CConfig::CConfig() {
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

CConfig::~CConfig() = default;

CConfig *CConfig::getInstance() {
    if (CConfig::instance == nullptr)
        CConfig::instance = new CConfig();

    return CConfig::instance;
}

const std::string &CConfig::getListenAddress() const {
    return listenAddress;
}

void CConfig::setListenAddress(const std::string &value) {
    CConfig::listenAddress = value;
}

uint16_t CConfig::getListenPort() const {
    return listenPort;
}

void CConfig::setListenPort(uint16_t value) {
    CConfig::listenPort = value;
}

unsigned int CConfig::getKeepalivePeriod() const {
    return keepalivePeriod;
}

void CConfig::setKeepalivePeriod(unsigned int value) {
    CConfig::keepalivePeriod = value;
}

unsigned int CConfig::getKeepaliveTimeout() const {
    return keepaliveTimeout;
}

void CConfig::setKeepaliveTimeout(unsigned int value) {
    CConfig::keepaliveTimeout = value;
}

unsigned int CConfig::getStreamMaxNumber() const {
    return streamMaxNumber;
}

void CConfig::setStreamMaxNumber(unsigned int value) {
    CConfig::streamMaxNumber = value;
}

unsigned int CConfig::getStreamActivityTimeout() const {
    return streamActivityTimeout;
}

void CConfig::setStreamActivityTimeout(unsigned int value) {
    CConfig::streamActivityTimeout = value;
}

int CConfig::getCodecGainAmbePlus() const {
    return codecGainAMBEPlus;
}

void CConfig::setCodecGainAmbePlus(int value) {
    codecGainAMBEPlus = value;
}

int CConfig::getCodecGainAmbe2Plus() const {
    return codecGainAMBE2Plus;
}

void CConfig::setCodecGainAmbe2Plus(int value) {
    codecGainAMBE2Plus = value;
}

bool CConfig::isUseAgc() const {
    return useAgc;
}

void CConfig::setUseAgc(bool value) {
    CConfig::useAgc = value;
}

int CConfig::getAgcClamping() const {
    return agcClamping;
}

void CConfig::setAgcClamping(int value) {
    CConfig::agcClamping = value;
}

bool CConfig::isUseBandPassFilter() const {
    return useBandPassFilter;
}

void CConfig::setUseBandPassFilter(bool value) {
    CConfig::useBandPassFilter = value;
}
