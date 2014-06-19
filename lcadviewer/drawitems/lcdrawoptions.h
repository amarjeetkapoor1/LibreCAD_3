#ifndef LCDRAWOPTIONS_H
#define LCDRAWOPTIONS_H

#include <cad/meta/color.h>

/**
 * @brief The LcDrawOptions class
 * will specift various default on how to render a object during specific situations.
 * For example when a entity is selected,the method selectedColor will specify in what color the entity must be drawn.
 */
class LcDrawOptions {
    public:
        LcDrawOptions();

        const lc::Color& selectedColor() const;

    private:
        lc::Color  _selectedColor;
};

#endif // LCDRAWOPTIONS_H
