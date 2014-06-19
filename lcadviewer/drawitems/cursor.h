#ifndef CURSOR_H
#define CURSOR_H

#include <cad/meta/color.h>
#include <events/drawevent.h>
#include "events/snappointevent.h"
#include "helpers/snapmanager.h"
#include "events/mousereleaseevent.h"


class Cursor {
    public:
        Cursor(int cursorSize, SnapManager_SPtr  snapManager, const lc::Color& xAxisColor, const lc::Color& yAxisColor);

    public:
        void on_Draw_Event(const DrawEvent&) ;
        void on_SnapPoint_Event(const SnapPointEvent&);
       // void on_MouseRelease_Event(const MouseReleaseEvent&);

    public:
        /**
          * \deprecated well, just may be...
          */
        void mouseReleaseEvent(const MouseReleaseEvent&);

    private:
        const lc::Color _xAxisColor;
        const lc::Color _yAxisColor;
        const double _cursorSize;

        SnapPointEvent _lastSnapEvent;
};

#endif // CURSOR_H
