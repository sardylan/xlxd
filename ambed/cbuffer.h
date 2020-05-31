//
//  cbuffer.h
//  xlxd
//
//  Created by Jean-Luc Deltombe (LX3JL) on 02/11/2015.
//  Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
//
// ----------------------------------------------------------------------------
//    This file is part of xlxd.
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

#ifndef cbuffer_h
#define cbuffer_h

////////////////////////////////////////////////////////////////////////////////////////

class CBuffer : public std::vector<uint8>
{
public:
    // constructor
    CBuffer() {};
    CBuffer(uint8 *, int);
    
    // destructor
    virtual ~CBuffer() {};
    
    // set
    void Set(uint8 *, size_t);
    void Set(const char *);
    void Append(uint8 *, size_t);
    void Append(uint8, size_t);
    void Append(uint8);
    void Append(uint16);
    void Append(uint32);
    void Append(const char *);
    void ReplaceAt(size_t, uint8);
    void ReplaceAt(size_t, uint16);
    void ReplaceAt(size_t, uint32);
    void ReplaceAt(size_t, const uint8 *, size_t);
    
    // operation
    int Compare(uint8 *, size_t) const;
    int Compare(uint8 *, size_t, size_t) const;
    
    // operator
    bool operator ==(const CBuffer &) const;
    bool operator ==(const char *) const;
    operator const char *() const;
    
    // debug
    void DebugDump(std::ofstream &);
};

////////////////////////////////////////////////////////////////////////////////////////
#endif /* cbuffer_h */
