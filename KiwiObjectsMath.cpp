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


#include "KiwiObjectsMath.h"

namespace Kiwi
{
    
    // ================================================================================ //
    //                                    PLUS                                          //
    // ================================================================================ //
	
    ObjectPlus::ObjectPlus(Infos const& infos) : Box(infos, Tag::create("+")),
    m_addend(0.),
    m_augend(0.)
    {
        addInlet(Io::Message, Io::Hot, "Addend");
        if(infos.args.empty())
        {
            addInlet(Io::Message, Io::Cold, "Augend");
        }
        else
        {
            if(infos.args[0].isNumber())
            {
                m_augend = double(infos.args[0]);
            }
            else
            {
                error(Errors::WrongArgument());
            }
            if(infos.args.size() > 1ul)
            {
                throw Errors::WrongArgument();
            }
        }
        addOutlet(Io::Message, "Sum");
    }
    
    ObjectPlus::~ObjectPlus()
    {
        ;
    }
    
    void ObjectPlus::receive(const ulong index, vector<Atom> const& atoms)
    {
        if(index)
        {
            if(!atoms.empty() && atoms[0].isNumber())
            {
                m_augend = double(atoms[0]);
            }
            else
            {
                warning(Errors::WrongArgument());
            }
        }
        else
        {
            if(!atoms.empty())
            {
                if(atoms[0].isNumber())
                {
                    m_augend = double(atoms[0]);
                    send(0ul, m_addend + m_augend);
                }
                else if(atoms[0].isTag() && sTag(atoms[0]) == Tags::bang)
                {
                    send(0ul, m_addend + m_augend);
                }
                else
                {
                    warning(Errors::WrongArgument());
                }
            }
            else
            {
                warning(Errors::WrongArgument());
            }
        }
    }
    
}