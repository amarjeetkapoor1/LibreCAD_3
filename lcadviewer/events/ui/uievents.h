#ifndef UIEVENTS_H
#define UIEVENTS_H

#include "nano-signal-slot/nano_signal_slot.hpp"

#include "uimousemoveevent.h"

#include "documentrenderer.h"

class UIEvents
{
    enum Reason {
        press=0,
        release=1,
        doubleClick=2,
        move=3
    };


public:
    UIEvents(DocumentRenderer *documentRenderer);


    void sendMouseEvent(unsigned int X, unsigned int Y, Reason reason);


    Nano::Signal<void(const UIMouseEvents&)>  _mousePressEvent;
    Nano::Signal<void(const UIMouseEvents&)>  _mouseReleaseEvent;
    Nano::Signal<void(const UIMouseEvents&)>  _mouseDoubleClickEvent;
    Nano::Signal<void(const UIMouseEvents&)>  _mouseMoveEvent;
};

#endif // UIEVENTS_H
