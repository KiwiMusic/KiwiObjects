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

#include "KiwiObjectsGuiClassic.h"

namespace Kiwi
{
    // ================================================================================ //
    //                                      BANG                                        //
    // ================================================================================ //
    
    Bang::Bang(Infos const& infos) : Object(infos, Tag::create("bang"))
    {
        addAttr(Attr::create("bgcolor", "Background Color", "Color", Color(1., 1., 1., 1.)));
        addAttr(Attr::create("bdcolor", "Border Color",     "Color", Color(0.4, 0.4, 0.4, 1.)));
        addAttr(Attr::create("circlecolor", "Circle Color", "Color", Color(0.4, 0.4, 0.4, 1.)));
        addAttr(Attr::create("ledcolor",    "Led Color",    "Color", Color(0.4, 0.4, 0.4, 1.)));
        setSize(Size(20., 20., 10., 10., true));
        
        addInlet(Io::Message, Io::Hot, "Flash (anything)");
        addOutlet(Io::Message, "Output (bang)");
        
        m_led = false;
    }
    
    Bang::~Bang()
    {
        ;
    }
    
    void Bang::tick()
    {
        m_led = false;
        redraw();
    }
    
    void Bang::receive(const ulong index, vector<Atom> const& atoms)
    {
        if(!atoms.empty())
        {
            Object::send(0ul, {Tag::List::bang});
            m_led = true;
            redraw();
            delay(150.);
        }
    }
    
    bool Bang::receive(scGuiView view, MouseEvent const& event)
    {
        if(event.isDown())
        {
            Object::send(0, {Tag::List::bang});
            m_led = true;
            redraw();
            return true;
        }
        else if(event.isUp())
        {
            m_led = false;
            redraw();
            return true;
        }
        return false;
    }
    
    void Bang:: draw(scGuiView ctrl, Sketch& sketch) const
    {
        const Rectangle bounds = Object::getBounds().withZeroOrigin();
        const double borderSize = bounds.width() * 0.1;
       
        const Rectangle ledRect = bounds.reduced(borderSize * 2.);
        sketch.fillAll(getAttrTyped<Color>("bgcolor")->getValue());
        sketch.setColor(getAttrTyped<Color>("bdcolor")->getValue());
        sketch.drawRectangle(bounds.reduced(borderSize * 0.5), borderSize, 0);
        sketch.setColor(getAttrTyped<Color>("circlecolor")->getValue());
        sketch.drawEllipse(ledRect, borderSize);
        
        if(m_led)
        {
            sketch.setColor(getAttrTyped<Color>("ledcolor")->getValue());
            sketch.fillEllipse(ledRect);
        }
    }
    
    bool Bang::notify(sAttr attr)
    {
        if(attr->getName() == "bgcolor" || attr->getName() == "bdcolor" || attr->getName() == "circlecolor")
        {
            cout << "attr changed : "<< attr->getName() << endl;
            redraw();
        }
        return true;
    }
}

