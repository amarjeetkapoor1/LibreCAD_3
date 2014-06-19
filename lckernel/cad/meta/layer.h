#ifndef LAYER_H
#define LAYER_H

#include <string>

#include "cad/const.h"

#include "cad/interface/variantable.h"
#include "cad/meta/linewidth.h"
#include "cad/meta/metacolor.h"


namespace lc {
    class Layer : public MetaType  {
        public:
            Layer();
            Layer(const std::string& name, const LineWidth lineWidth, const MetaColor color);
            virtual ~Layer();

            LineWidth lineWidth() const;
            MetaColor color() const;
            std::string name() const;

            bool operator == (const Layer& layer) const {
                return (layer._name == _name);
            }

            bool variantValid() const {
                return true;
            }

            metaTypeId metaName() const {
                return MetaType::LAYER;
            }

        private:
            std::string _name;
            LineWidth _lineWidth;
            MetaColor _color;
    };
    typedef std::shared_ptr<Layer> Layer_SPtr;
    typedef std::shared_ptr<const Layer> Layer_CSPtr;
}

#endif // LAYER_H
