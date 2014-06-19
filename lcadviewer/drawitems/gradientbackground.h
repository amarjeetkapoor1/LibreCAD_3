#ifndef GRADIENTBACKGROUND_H
#define GRADIENTBACKGROUND_H

#include <cad/meta/color.h>
#include "lcvdrawitem.h"

/**
  * Create a garident background
  *
  */
typedef struct _cairo cairo_t;
class GradientBackground : public LCVDrawItem {
    public:
        GradientBackground(const lc::Color& topColor, const lc::Color& bottomColor);
        virtual ~GradientBackground();

        virtual void draw(LcPainter* _painter, LcDrawOptions* options, const lc::geo::Area& updateRect) const;
    private:
        const lc::Color _topColor;
        const lc::Color _bottomColor;
};

#endif // GRADIENTBACKGROUND_H
