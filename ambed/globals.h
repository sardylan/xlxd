//
//  main.h
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

#ifndef __AMBED__GLOBALS__H
#define __AMBED__GLOBALS__H

#include <vector>
#include <array>
#include <map>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <ctime>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <arpa/inet.h>

////////////////////////////////////////////////////////////////////////////////////////
// defines

// version -----------------------------------------------------

#define VERSION_MAJOR                   1
#define VERSION_MINOR                   3
#define VERSION_REVISION                5

// global ------------------------------------------------------

//#define RUN_AS_DAEMON
//#define DEBUG_DUMPFILE

// Codecs -------------------------------------------------------
#define CODEC_NONE                      0
#define CODEC_AMBEPLUS                  1
#define CODEC_AMBE2PLUS                 2

////////////////////////////////////////////////////////////////////////////////////////
// typedefs

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef unsigned int            uint;


////////////////////////////////////////////////////////////////////////////////////////
// macros

#define MIN(a,b) 				((a) < (b))?(a):(b)
#define MAX(a,b) 				((a) > (b))?(a):(b)
#define MAKEWORD(low, high)		((uint16)(((uint8)(low)) | (((uint16)((uint8)(high))) << 8)))
#define MAKEDWORD(low, high)	((uint32)(((uint16)(low)) | (((uint32)((uint16)(high))) << 16)))
#define LOBYTE(w)				((uint8)(uint16)(w & 0x00FF))
#define HIBYTE(w)				((uint8)((((uint16)(w)) >> 8) & 0xFF))
#define LOWORD(dw)				((uint16)(uint32)(dw & 0x0000FFFF))
#define HIWORD(dw)				((uint16)((((uint32)(dw)) >> 16) & 0xFFFF))

////////////////////////////////////////////////////////////////////////////////////////
// FIR Filter coefficients computed to be the closest to the recommended filter in 
// Documentation
//
// Following GNU Octave script was used
/*
pkg load signal;
fsamp = 8000;
fcuts = [300 400 3000 3400];
mags = [0 1 0];
devs = [0.2 1 0.2];

[n,Wn,beta,ftype] = kaiserord(fcuts,mags,devs,fsamp);
n = n + rem(n,2);
hh = fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale');

freqz(hh);
[H,f] = freqz(hh,1,1024,fsamp);
plot(f,abs(H))
disp(hh);
grid
*/

const float FILTER_TAPS[]{
        -0.05063341f, -0.00060337f, -0.08892498f, -0.02026701f, -0.05940750f, -0.10977641f, 0.03244024f, -0.22304499f,
        0.11452865f, 0.72500000f, 0.11452865f, -0.22304499f, 0.03244024f, -0.10977641f, -0.05940750f, -0.02026701f,
        -0.08892498f, -0.00060337f, -0.05063341f
};

#define FILTER_TAPS_LENGTH          19

////////////////////////////////////////////////////////////////////////////////////////
// global objects

class CAmbeServer;
extern CAmbeServer  g_AmbeServer;

class CVocodecs;
extern CVocodecs    g_Vocodecs;

void signalHandler(int);

////////////////////////////////////////////////////////////////////////////////////////
#endif /* main_h */
