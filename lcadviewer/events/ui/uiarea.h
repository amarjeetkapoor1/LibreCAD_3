#ifndef UIAREA_H
#define UIAREA_H

#include <cad/geometry/geoarea.h>

class UIArea
{
public:
    UIArea(lc::geo::Area area);


    private: lc::geo::Area _area;
};

#endif // UIAREA_H
