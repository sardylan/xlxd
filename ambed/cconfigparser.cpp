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

#include <cstring>
#include <iostream>
#include <getopt.h>
#include <sstream>

#include "cconfigparser.hpp"
#include "cconfig_default.hpp"
#include "globals.h"

CConfigParser::CConfigParser(int argc, char **argv) {
    CConfigParser::config = CConfig::getInstance();

    CConfigParser::argc = argc;
    CConfigParser::argv = argv;
}

CConfigParser::~CConfigParser() = default;

bool CConfigParser::parse() {
    bool ret = false;
    int optionIndex = 0;
    int c;
    char *endPointer;

    std::string configFile;

    bool confFile = false;
    bool helpRequested = false;
    bool versionRequested = false;

    static struct option longOptions[] = {
            {"help",                    no_argument,       nullptr, 'h'},
            {"version",                 no_argument,       nullptr, 'V'},
            {"config",                  required_argument, nullptr, 'c'},
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
        c = getopt_long(argc, argv, "hVc:a:p:k:i:n:t:g:G:A:C:B:", longOptions, &optionIndex);

        switch (c) {
            case -1:
                ret = true;
                break;

            case '?':
            case 'h':
                helpRequested = true;
                break;

            case 'V':
                versionRequested = true;
                break;

            case 'c':
                confFile = true;
                configFile = optarg;
                break;

            case 'a':
                config->setListenAddress(std::string(optarg));
                break;

            case 'p':
                config->setListenPort((uint16_t) strtol(optarg, &endPointer, 10));
                break;

            case 'k':
                config->setKeepalivePeriod((unsigned int) strtol(optarg, &endPointer, 10));
                break;

            case 'i':
                config->setKeepaliveTimeout((unsigned int) strtol(optarg, &endPointer, 10));
                break;

            case 'n':
                config->setStreamMaxNumber((unsigned int) strtol(optarg, &endPointer, 10));
                break;

            case 't':
                config->setStreamActivityTimeout((unsigned int) strtol(optarg, &endPointer, 10));
                break;

            case 'g':
                config->setCodecGainAmbePlus((int) strtol(optarg, &endPointer, 10));
                break;

            case 'G':
                config->setCodecGainAmbe2Plus((int) strtol(optarg, &endPointer, 10));
                break;

            case 'A':
                config->setUseAgc(std::strcmp(optarg, "true") == 0);
                break;

            case 'C':
                config->setAgcClamping((int) strtol(optarg, &endPointer, 10));
                break;

            case 'B':
                config->setUseAgc(std::strcmp(optarg, "true") == 0);
                break;

            default:
                std::cerr << "Option" << c << "not covered" << std::endl;;
        }
    } while (c != -1);


    if (helpRequested == 1) {
        ret = false;
        printHelp();
    } else if (versionRequested == 1) {
        ret = false;
        printVersion();
    } else if (confFile == 1) {
        ret = parseConfigFile(configFile);
    }

    return ret;
}

bool CConfigParser::parseConfigFile(const std::string &configFile) {
    std::ifstream cfgFile(configFile);
    if (!cfgFile.good()) {
        std::cerr << "Config file \"" << configFile << "\" not found";
        return false;
    }

    std::string line;
    while (std::getline(cfgFile, line)) {
        std::istringstream iss(line);

        std::string param;
        std::string value;
        if (!(iss >> param >> value))
            continue;

        std::cout << param << value;
    }

//    FILE *fd;
//    char param[80];
//    char value[80];
//    size_t ln;
//    int linecount = 0;
//    char *endptr;
//
//    fd = fopen(configFile, "r");
//
//    if (fd == NULL) {
//        log_error(LOG_TAG, "Unable to open config file %s", configFile);
//        return false;
//    }
//
//    log_info(LOG_TAG, "Parsing config file %s", configFile);
//
//    while (!feof(fd)) {
//        linecount++;
//
//        bzero(param, sizeof(param));
//        bzero(value, sizeof(value));
//
//        if (fscanf(fd, "%s %s", param, value) != 2) {
//            if (std::strlen(param) != 0 || std::strlen(value) != 0)
//                log_error(LOG_TAG, "Unable to parse config file in line %d", linecount);
//            continue;
//        }
//
//        log_debug(LOG_TAG, "Param: %s - Value: %s", param, value);
//
//        if (strcmp(param, "debug-level") == 0) {
//            conf->debug_level = (int) strtol(optarg, &endptr, 10);
//            log_debug(LOG_TAG, "Configuration updated. debug-level = %d", conf->debug_level);
//            continue;
//        } else if (strcmp(param, "log-file-level") == 0) {
//            conf->log_file_level = (int) strtol(optarg, &endptr, 10);
//            log_debug(LOG_TAG, "Configuration updated. log-file-level = %d", conf->log_file_level);
//            continue;
//        } else if (strcmp(param, "log-file") == 0) {
//            ln = std::strlen(value) + 1;
//            conf->log_file = (char *) realloc((void *) conf->log_file, sizeof(char) * ln);
//            strcpy(conf->log_file, value);
//            log_debug(LOG_TAG, "Configuration updated. log-file = %s", conf->log_file);
//            continue;
//        } else if (strcmp(param, "inverter-loop-wait") == 0) {
//            conf->inverter_loop_wait = (int) strtol(optarg, &endptr, 10);
//            log_debug(LOG_TAG, "Configuration updated. inverter-loop-wait = %d", conf->inverter_loop_wait);
//            continue;
//        } else if (strcmp(param, "server-loop-wait") == 0) {
//            conf->server_loop_wait = (int) strtol(optarg, &endptr, 10);
//            log_debug(LOG_TAG, "Configuration updated. server-loop-wait = %d", conf->server_loop_wait);
//            continue;
//        } else if (strcmp(param, "daemon-num") == 0) {
//            conf->daemon_num = (int) strtol(optarg, &endptr, 10);
//            log_debug(LOG_TAG, "Configuration updated. daemon-num = %d", conf->daemon_num);
//            continue;
//        } else if (strcmp(param, "inverter-host") == 0) {
//            ln = std::strlen(value) + 1;
//            conf->inverter_host = (char *) realloc((void *) conf->inverter_host, sizeof(char) * ln);
//            strcpy(conf->inverter_host, value);
//            log_debug(LOG_TAG, "Configuration updated. inverter-host = %s", conf->inverter_host);
//            continue;
//        } else if (strcmp(param, "inverter-port") == 0) {
//            conf->inverter_port = (int) strtol(optarg, &endptr, 10);
//            log_debug(LOG_TAG, "Configuration updated. inverter-port = %d", conf->inverter_port);
//            continue;
//        } else if (strcmp(param, "inverter-num") == 0) {
//            conf->inverter_num = (int) strtol(optarg, &endptr, 10);
//            log_debug(LOG_TAG, "Configuration updated. inverter-num = %d", conf->inverter_num);
//            continue;
//        }
//    }

    cfgFile.close();

    return false;
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
    std::cerr << "                                    (if present, will override command line params)" << std::endl;
    std::cerr << std::endl;
    std::cerr << " -a | --listen-address              Transcoder listen address"
              << formatDefault(AMBED_CONFIG_LISTEN_ADDRESS_DEFAULT) << std::endl;
    std::cerr << " -p | --listen-port                 Transcoder port (first control port)"
              << formatDefault(AMBED_CONFIG_LISTEN_PORT_DEFAULT) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -k | --keepalive-period            Stream keep-alive period [in seconds]"
              << formatDefault(AMBED_CONFIG_KEEPALIVE_PERIOD_DEFAULT) << std::endl;
    std::cerr << " -i | --keepalive-timeout           Stream keep-alive timeout [in seconds]"
              << formatDefault(AMBED_CONFIG_KEEPALIVE_TIMEOUT_DEFAULT) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -n | --stream-max-number           Max number of concurrent streams"
              << formatDefault(AMBED_CONFIG_STREAM_MAX_NUMBER_DEFAULT) << std::endl;
    std::cerr << " -t | --stream-activity-timeout     Stream activity timeout"
              << formatDefault(AMBED_CONFIG_STREAM_ACTIVITY_TIMEOUT_DEFAULT) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -g | --codec-gain-ambeplus         Gain for AMBE-Plus codec [in dB, integer]"
              << formatDefault(AMBED_CONFIG_CODEC_GAIN_AMBEPLUS_DEFAULT) << std::endl;
    std::cerr << " -G | --codec-gain-ambe2plus        Gain for AMBE2-Plus codec [in dB, integer]"
              << formatDefault(AMBED_CONFIG_CODEC_GAIN_AMBE2PLUS_DEFAULT) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -A | --use-agc                     Enable use of AGC [true|false]"
              << formatDefault(AMBED_CONFIG_USE_AGC_DEFAULT) << std::endl;
    std::cerr << " -C | --agc-clamping                AGC clamping value [in dB, integer]"
              << formatDefault(AMBED_CONFIG_AGC_CLAMPING_DEFAULT) << std::endl;
    std::cerr << std::endl;
    std::cerr << " -B | --use-band-pass-filter        Enable use of Band-Pass filter [true|false]"
              << formatDefault(AMBED_CONFIG_USE_BAND_PASS_FILTER_DEFAULT) << std::endl;
    std::cerr << "                                    (works only if AGC is disabled)" << std::endl;
    std::cerr << std::endl;
}

void CConfigParser::printVersion() {
    std::cout << "AMBEd "
              << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_REVISION
              << std::endl;
}

std::string CConfigParser::formatDefault(const char *value) {
    char buff[1024];
    std::sprintf(buff, " <%s>", value);
    return std::string(buff);
}

std::string CConfigParser::formatDefault(const std::string &value) {
    return formatDefault(value.c_str());
}

std::string CConfigParser::formatDefault(int value) {
    char buff[1024];
    std::sprintf(buff, "%d", value);
    return formatDefault(buff);
}

std::string CConfigParser::formatDefault(unsigned int value) {
    char buff[1024];
    std::sprintf(buff, "%ud", value);
    return formatDefault(buff);
}

std::string CConfigParser::formatDefault(uint16_t value) {
    char buff[1024];
    std::sprintf(buff, "%ud", value);
    return formatDefault(buff);
}

std::string CConfigParser::formatDefault(bool value) {
    return formatDefault(value ? "true" : "false");
}
