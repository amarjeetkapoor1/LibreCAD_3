#include "layer.h"

using namespace lc;

Layer::Layer() {
}

Layer::~Layer() {
}

Layer::Layer(const std::string& name, const LineWidth lineWidth, const MetaColor color) : MetaType() {
    _name = name;
    _lineWidth = lineWidth;
    _color = color;
}

MetaColor Layer::color() const {
    return _color;
}
LineWidth Layer::lineWidth() const {
    return _lineWidth;
}

std::string Layer::name() const {
    return _name;
}

