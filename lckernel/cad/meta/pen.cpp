#include "pen.h"



using namespace lc;

Pen::Pen() {
    _color = nullptr;
    _lineWidth = nullptr;
}

Pen::Pen(MetaColor* color, LineWidth* lineWidth) {
    _color = color;
    _lineWidth = lineWidth;
}

Pen::~Pen() {
    if (_color != nullptr) {
        delete _color;
    }

    if (_lineWidth != nullptr) {
        delete _lineWidth;
    }
}

LineWidth* Pen::lineWidth() const {
    return _lineWidth;
}

MetaColor* Pen::color() const {
    return _color;
}
