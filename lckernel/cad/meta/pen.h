#ifndef PEN_H
#define PEN_H

#include "cad/const.h"

#include "metacolor.h"
#include "linewidth.h"
#include "cad/interface/variantable.h"
#include "cad/interface/metatype.h"
#include "cad/const.h"
namespace lc {

    /*!
     * \deprecated Pen is deperecated a user must use color or linewdith
     */
    class Pen : MetaType {
        public:

            Pen();
            Pen(MetaColor* color, LineWidth* lineWidth);
            virtual ~Pen();

            LineWidth* lineWidth() const;
            MetaColor* color() const;

            bool variantValid() const {
                return _color != nullptr && _lineWidth != nullptr;
            }

            metaTypeId metaName() const {
                return MetaType::PEN;
            }

        private:

            MetaColor* _color;
            LineWidth* _lineWidth;
    };
}


#endif // PEN_H
