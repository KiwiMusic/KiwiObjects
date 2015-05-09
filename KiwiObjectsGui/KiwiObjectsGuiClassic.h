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
        Bang(Infos const& infos);
        ~Bang();
        void receive(const ulong index, vector<Atom> const& atoms) override;
        bool receive(scGuiView view, MouseEvent const& event) override;
        void draw(scGuiView view, Sketch& sketch) const;
        bool notify(sAttr attr) override;
        void tick() override;
    };
    
    class NewObject : public Object, public GuiTextEditor::Listener
    {
    private:
        const sGuiTextEditor m_editor;
    public:
        NewObject(Infos const& infos) : Object(infos, Tag::create("newobject")),
        m_editor(make_shared<GuiTextEditor>(infos.instance ? infos.instance : sGuiContext()))
        {
            /*
            setSize(Size(100., 100., 10., 10.));
            m_editor->setPosition(Point(4., 4.));
            m_editor->setSize(Size(92., 12., 10., 10.));
             */
            m_editor->setTabKeyBehavior(GuiTextEditor::Notify);
            m_editor->setWrapped(true);
            m_editor->setJustification(Font::Justification::Left);
            addChild(m_editor);
        }
        
        ~NewObject()
        {
            ;
        }
        
        void receive(ulong index, vector<Atom> const& atoms) override
        {
        
        }
        
        void draw(scGuiView view, Sketch& sketch) const
        {
            sketch.fillAll(Colors::white);
            const Size size(getSize());
            const Rectangle bounds(sketch.getBounds());
            if(bounds.x() < 2. || bounds.y() < 2. || bounds.bottom() > size.height() - 2. || bounds.right() > size.width() - 2.)
            {
                sketch.setColor(Color(0.4, 0.4, 0.4, 1.));
                sketch.setLineWidth(2.);
                sketch.drawRectangle(1., 1., size.width() -2., size.height() - 2.);
            }
        }
        
        bool notify(sAttr attr) override
        {
            return true;
        }


        void loaded() override
        {
            m_editor->addListener(getShared<Listener>());
            m_editor->grabFocus();
        }


        void textChanged(sGuiTextEditor editor)
        {
            const Size textsize = editor->getTextSize();
            /*
            const Size editorsize = editor->getSize();
            
            if(textsize.width() > editorsize.width() || textsize.height() != editorsize.height())
            {
                setSize(Size(max(textsize.width(), editorsize.width()) + 8., textsize.height() + 8., 10., 10.));
                editor->setSize(Size(max(textsize.width(), editorsize.width()), textsize.height()));
            }
             */
            /*
            if(textsize.height() != editorsize.height())
            {
                setSize(Size(100., textsize.height() + 8, 10., 10.));
                editor->setSize(Size(92., textsize.height()));
            }
            */
        }

        void tabKeyPressed(sGuiTextEditor editor)
        {
            wcout << editor->getText() << endl;
        }
    };
}

#endif


