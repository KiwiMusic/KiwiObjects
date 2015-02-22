/*
 ==============================================================================
 
 This file is part of the KIWI library.
 Copyright (c) 2014 Pierre Guillot & Eliott Paris.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 KIWI is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses KIWI, contact : guillotpierre6@gmail.com
 
 ==============================================================================
*/

#include "ObjectsDspIo.h"

namespace Kiwi
{
    static vector<ulong> fromAtomVecToUlongVec(vector<Atom> const& atoms)
    {
        vector<ulong> vec;
        for(vector<Atom>::size_type i = 0; i < atoms.size(); i++)
        {
            if(atoms[i].isLong() && (long)(atoms[i]) > 0)
            {
                vec.push_back((ulong)atoms[i]);
            }
        }
        return vec;
    }
    
    DacTilde::DacTilde(Detail const& detail) :
    Object(detail, Tag::create("dac~")),
    DspDac(detail.patcher, fromAtomVecToUlongVec(detail.args))
    {
        vector<ulong> channels;
        DspDac::getChannels(channels);
        for(vector<ulong>::size_type i = 0; i < channels.size(); i++)
        {
            addInlet(Io::Signal, Io::Hot, "Channel " + toString(channels[i]));
        }
    }
    
    DacTilde::~DacTilde()
    {
        ;
    }
    
    void DacTilde::receive(ulong index, vector<Atom> const& atoms)
    {
        ;
    }
    
    void DacTilde::bang()
    {
        ;
    }
}

