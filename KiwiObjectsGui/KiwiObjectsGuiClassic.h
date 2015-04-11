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

#ifndef __DEF_KIWI_OBJECTS_GUI_CLASSIC__
#define __DEF_KIWI_OBJECTS_GUI_CLASSIC__

#include "../../KiwiPatcher/KiwiPatcher.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      GUI                                         //
    // ================================================================================ //
    
    // ================================================================================ //
    //                                      BANG                                        //
    // ================================================================================ //
    
    class Bang : public Object, public GuiMouser, public Clock
    {
    private:
        atomic_bool m_led;
    public:
        Bang(Infos const& detail);
        ~Bang();
        void receive(ulong index, vector<Atom> const& atoms) override;
        bool receive(scGuiController ctrl, MouseEvent const& event) override;
        void draw(scGuiController ctrl, Sketch& sketch) const override;
        bool notify(sAttr attr) override;
        void tick() override;
    };
}

#endif


