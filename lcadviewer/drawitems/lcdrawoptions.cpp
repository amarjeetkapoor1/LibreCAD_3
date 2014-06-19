#include "lcdrawoptions.h"

LcDrawOptions::LcDrawOptions() {
    _selectedColor = lc::Color(1.0, 0., 0.);
}


const lc::Color& LcDrawOptions::selectedColor() const {
    return _selectedColor;
}
