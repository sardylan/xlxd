//
//  main.cpp
//  ambed
//
//  Created by Jean-Luc Deltombe (LX3JL) on 13/04/2017.
//  Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
//
// ----------------------------------------------------------------------------
//    This file is part of ambed.
//
//    xlxd is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    xlxd is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <csignal>
#include <sys/stat.h>

#include "main.hpp"
#include "globals.h"
#include "ctimepoint.h"
#include "cambeserver.h"
#include "syslog.h"
#include "cconfigparser.hpp"


bool keepRunning = true;


int main(int argc, char **argv) {
    CConfigParser configParser(argc, argv);

    if (!configParser.parse())
        exit(EXIT_SUCCESS);

#ifdef RUN_AS_DAEMON

    // redirect cout, cerr and clog to syslog
    syslog::redirect cout_redir(std::cout);
    syslog::redirect cerr_redir(std::cerr);
    syslog::redirect clog_redir(std::clog);
    
    //Fork the Parent Process
    pid_t pid, sid;
    pid = ::fork();
    //pid = ::vfork();
    if ( pid < 0 )
    {
        exit(EXIT_FAILURE);
    }
    
    // We got a good pid, Close the Parent Process
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    
    // Change File Mask
    ::umask(0);
    
    //Create a new Signature Id for our child
    sid = ::setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }
    
    // Change Directory
    // If we cant find the directory we exit with failure.
    if ( (::chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }
    
    // Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

#endif

    signal(SIGINT, signalHandler);

    CConfig *config = CConfig::getInstance();
    g_AmbeServer.SetListenIp(CIp(config->getListenAddress().c_str()));

    std::cout << "Starting AMBEd "
              << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_REVISION
              << std::endl;

    if (!g_AmbeServer.Start()) {
        std::cout << "Error starting AMBEd" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "AMBEd started and listening on "
              << g_AmbeServer.GetListenIp() << ":" << config->getListenPort()
              << std::endl;

    while (keepRunning)
        CTimePoint::TaskSleepFor(1000);

    g_AmbeServer.Stop();

    std::cout << "AMBEd stopped" << std::endl;

    exit(EXIT_SUCCESS);
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        std::cout << "SIGINT received" << std::endl;
        std::cout << "Stopping AMBE Server" << std::endl;
        keepRunning = false;
    }
}
