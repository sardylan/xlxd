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

#include <iostream>
#include <getopt.h>
#include <sstream>

#include "cconfigparser.hpp"
#include "cconfig_default.hpp"
#include "globals.h"

CConfigParser::CConfigParser(CConfig *config, int argc, char **argv) {
    CConfigParser::config = config;
    CConfigParser::argc = argc;
    CConfigParser::argv = argv;
}

CConfigParser::~CConfigParser() = default;

void CConfigParser::print() {
    std::cout << std::endl;
    std::cout << "Listen address:                     "
              << config->getListenAddress()
              << std::endl;
    std::cout << "Listen port:                        "
              << format(config->getListenPort())
              << std::endl;
    std::cout << "Keep-Alive period:                  "
              << format(config->getKeepalivePeriod()) << " secs"
              << std::endl;
    std::cout << "Keep-Alive timeout:                 "
              << format(config->getKeepaliveTimeout()) << " secs"
              << std::endl;
    std::cout << "Stream max number:                  "
              << format(config->getStreamMaxNumber())
              << std::endl;
    std::cout << "Stream activity timeout:            "
              << format(config->getStreamActivityTimeout()) << " secs"
              << std::endl;
    std::cout << "Codec gain AMBE-Plus:               "
              << format(config->getCodecGainAmbePlus()) << " dB"
              << std::endl;
    std::cout << "Codec gain AMBE2-Plus:              "
              << format(config->getCodecGainAmbe2Plus()) << " dB"
              << std::endl;
    std::cout << "Use of AGC enabled:                 "
              << format(config->isUseAgc())
              << std::endl;
    std::cout << "AGC clamping:                       "
              << format(config->getAgcClamping()) << " dB"
              << std::endl;
    std::cout << "Use of Band-Pass filter enabled:    "
              << format(config->isUseBandPassFilter())
              << std::endl;
    std::cout << std::endl;
}

bool CConfigParser::parse() {
    int optionIndex = 0;
    int c;
    std::string value;
    std::string configFile;

    bool retArgs = false;
    bool retConfigFile = true;

    bool helpRequested = false;
    bool versionRequested = false;
    bool saveRequested = false;

    static struct option longOptions[] = {
            {"help",                    no_argument,       nullptr, 'h'},
            {"version",                 no_argument,       nullptr, 'V'},
            {"config",                  required_argument, nullptr, 'c'},
            {"save-config",             no_argument,       nullptr, 's'},
            {"listen-address",          required_argument, nullptr, 'a'},
            {"listen-port",             required_argument, nullptr, 'p'},
            {"keepalive-period",        required_argument, nullptr, 'k'},
            {"keepalive-timeout",       required_argument, nullptr, 'i'},
            {"stream-max-number",       required_argument, nullptr, 'n'},
            {"stream-activity-timeout", required_argument, nullptr, 't'},
            {"codec-gain-ambeplus",     required_argument, nullptr, 'g'},
            {"codec-gain-ambe2plus",    required_argument, nullptr, 'G'},
            {"use-agc",                 required_argument, nullptr, 'A'},
            {"agc-clamping",            required_argument, nullptr, 'C'},
            {"use-band-pass-filter",    required_argument, nullptr, 'B'},
            {nullptr, 0,                                   nullptr, 0}
    };

    do {
        c = getopt_long(argc, argv, "hVc:sa:p:k:i:n:t:g:G:A:C:B:", longOptions, &optionIndex);

        if (optarg != nullptr)
            value = optarg;
        else
            value = "";

        switch (c) {
            case -1:
                retArgs = true;
                break;

            case '?':
            case 'h':
                helpRequested = true;
                break;

            case 'V':
                versionRequested = true;
                break;

            case 'c':
                configFile = value;
                retConfigFile = loadConfigFile(configFile);
                break;

            case 's':
                saveRequested = true;
                break;

            case 'a':
                config->setListenAddress(value);
                break;

            case 'p':
                config->setListenPort(parseUInt16(value));
                break;

            case 'k':
                config->setKeepalivePeriod(parseUInt32(value));
                break;

            case 'i':
                config->setKeepaliveTimeout(parseUInt32(value));
                break;

            case 'n':
                config->setStreamMaxNumber(parseUInt32(value));
                break;

            case 't':
                config->setStreamActivityTimeout(parseUInt32(value));
                break;

            case 'g':
                config->setCodecGainAmbePlus(parseInt32(value));
                break;

            case 'G':
                config->setCodecGainAmbe2Plus(parseInt32(value));
                break;

            case 'A':
                config->setUseAgc(parseBool(value));
                break;

            case 'C':
                config->setAgcClamping(parseInt32(value));
                break;

            case 'B':
                config->setUseAgc(parseBool(value));
                break;

            default:
                std::cerr << "Option" << c << "not covered" << std::endl;;
        }
    } while (c != -1);

    if (saveRequested) {
        saveConfigFile(configFile);
    }

    if (helpRequested) {
        retArgs = false;
        printHelp();
    } else if (versionRequested) {
        retArgs = false;
        printVersion();
    }

    return retArgs && retConfigFile;
}

bool CConfigParser::loadConfigFile(const std::string &configFile) {
    std::ifstream cfgFile(configFile);
    if (!cfgFile.good()) {
        std::cerr << "Config file \"" << configFile << "\" not found";
        return false;
    }

    int lineCount = 0;
    std::string line;
    while (std::getline(cfgFile, line)) {
        lineCount++;

        std::istringstream iss(line);

        std::string param;
        std::string value;
        if (!(iss >> param >> value))
            continue;

        if (param == "listen-address") {
            config->setListenAddress(value);
        } else if (param == "listen-port") {
            config->setListenPort(parseUInt16(value));
        } else if (param == "keepalive-period") {
            config->setKeepalivePeriod(parseUInt32(value));
        } else if (param == "keepalive-timeout") {
            config->setKeepaliveTimeout(parseUInt32(value));
        } else if (param == "stream-max-number") {
            config->setStreamMaxNumber(parseUInt32(value));
        } else if (param == "stream-activity-timeout") {
            config->setStreamActivityTimeout(parseUInt32(value));
        } else if (param == "codec-gain-ambeplus") {
            config->setCodecGainAmbePlus(parseInt32(value));
        } else if (param == "codec-gain-ambe2plus") {
            config->setCodecGainAmbe2Plus(parseInt32(value));
        } else if (param == "use-agc") {
            config->setUseAgc(parseBool(value));
        } else if (param == "agc-clamping") {
            config->setAgcClamping(parseInt32(value));
        } else if (param == "use-band-pass-filter") {
            config->setUseBandPassFilter(parseBool(value));
        } else {
            std::cerr << "Wrong param in config file!!!"
                      << " line " << lineCount
                      << " - param: \"" << param << "\""
                      << std::endl;
        }
    }

    cfgFile.close();

    return true;
}

bool CConfigParser::saveConfigFile(const std::string &configFile) {
    std::ofstream cfgFile(configFile);

    cfgFile << "listen-address" << " " << config->getListenAddress() << std::endl;
    cfgFile << "listen-port" << " " << format(config->getListenPort()) << std::endl;
    cfgFile << "keepalive-period" << " " << format(config->getKeepalivePeriod()) << std::endl;
    cfgFile << "keepalive-timeout" << " " << format(config->getKeepaliveTimeout()) << std::endl;
    cfgFile << "stream-max-number" << " " << format(config->getStreamMaxNumber()) << std::endl;
    cfgFile << "stream-activity-timeout" << " " << format(config->getStreamActivityTimeout()) << std::endl;
    cfgFile << "codec-gain-ambeplus" << " " << format(config->getCodecGainAmbePlus()) << std::endl;
    cfgFile << "codec-gain-ambe2plus" << " " << format(config->getCodecGainAmbe2Plus()) << std::endl;
    cfgFile << "use-agc" << " " << format(config->isUseAgc()) << std::endl;
    cfgFile << "agc-clamping" << " " << format(config->getAgcClamping()) << std::endl;
    cfgFile << "use-band-pass-filter" << " " << format(config->isUseBandPassFilter()) << std::endl;

    cfgFile.close();

    return true;
}

void CConfigParser::printHelp() {
    std::cerr << "Usage:  " << argv[0] << " [params]" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Params (short, long, description, [type] and <default>):" << std::endl;
    std::cerr << std::endl;
    std::cerr << " -h | --help                        Print this help" << std::endl;
    std::cerr << " -V | --version                     Print program name and version" << std::endl;
    std::cerr << std::endl;
    std::cerr << " -c | --config                      Load configuration from file" << std::endl;
    std::cerr << "                                    (if present, next options will override)" << std::endl;
    std::cerr << std::endl;
    std::cerr << " -s | --save-config                 Save current configuration into file" << std::endl;
    std::cerr << "                                    (overwrite values in file specified with --config)" << std::endl;
    std::cerr << std::endl;
    std::cerr << " -a | --listen-address              Transcoder listen address"
              << formatDefault(AMBED_CONFIG_LISTEN_ADDRESS_DEFAULT) << std::endl;
    std::cerr << " -p | --listen-port                 Transcoder port (first control port)"
              << formatDefault(format(AMBED_CONFIG_LISTEN_PORT_DEFAULT)) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -k | --keepalive-period            Stream keep-alive period [in seconds]"
              << formatDefault(format(AMBED_CONFIG_KEEPALIVE_PERIOD_DEFAULT)) << std::endl;
    std::cerr << " -i | --keepalive-timeout           Stream keep-alive timeout [in seconds]"
              << formatDefault(format(AMBED_CONFIG_KEEPALIVE_TIMEOUT_DEFAULT)) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -n | --stream-max-number           Max number of concurrent streams"
              << formatDefault(format(AMBED_CONFIG_STREAM_MAX_NUMBER_DEFAULT)) << std::endl;
    std::cerr << " -t | --stream-activity-timeout     Stream activity timeout"
              << formatDefault(format(AMBED_CONFIG_STREAM_ACTIVITY_TIMEOUT_DEFAULT)) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -g | --codec-gain-ambeplus         Gain for AMBE-Plus codec [in dB, integer]"
              << formatDefault(format(AMBED_CONFIG_CODEC_GAIN_AMBEPLUS_DEFAULT)) << std::endl;
    std::cerr << " -G | --codec-gain-ambe2plus        Gain for AMBE2-Plus codec [in dB, integer]"
              << formatDefault(format(AMBED_CONFIG_CODEC_GAIN_AMBE2PLUS_DEFAULT)) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -A | --use-agc                     Enable use of AGC [true|false]"
              << formatDefault(format(AMBED_CONFIG_USE_AGC_DEFAULT)) << std::endl;
    std::cerr << " -C | --agc-clamping                AGC clamping value [in dB, integer]"
              << formatDefault(format(AMBED_CONFIG_AGC_CLAMPING_DEFAULT)) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -B | --use-band-pass-filter        Enable use of Band-Pass filter [true|false]"
              << formatDefault(format(AMBED_CONFIG_USE_BAND_PASS_FILTER_DEFAULT)) << std::endl;
    std::cerr << "                                    (works only if AGC is disabled)" << std::endl;
    std::cerr << std::endl;
}

void CConfigParser::printVersion() {
    std::cout << "AMBEd "
              << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_REVISION
              << std::endl;
}

std::string CConfigParser::formatDefault(const std::string &value) {
    char buff[1024];
    std::sprintf(buff, " <%s>", value.c_str());
    return std::string(buff);
}

std::string CConfigParser::format(int value) {
    char buff[1024];
    std::sprintf(buff, "%d", value);
    return std::string(buff);
}

std::string CConfigParser::format(unsigned int value) {
    char buff[1024];
    std::sprintf(buff, "%u", value);
    return std::string(buff);
}

std::string CConfigParser::format(uint16_t value) {
    char buff[1024];
    std::sprintf(buff, "%u", value);
    return std::string(buff);
}

std::string CConfigParser::format(bool value) {
    return value ? "true" : "false";
}

bool CConfigParser::parseBool(const std::string &value) {
    return (bool) (value == "true");
}

uint16_t CConfigParser::parseUInt16(const std::string &value) {
    return (uint16_t) strtol(value.c_str(), nullptr, 10);
}

unsigned int CConfigParser::parseUInt32(const std::string &value) {
    return (unsigned int) strtol(value.c_str(), nullptr, 10);
}

int CConfigParser::parseInt32(const std::string &value) {
    return (int) strtol(value.c_str(), nullptr, 10);
}
