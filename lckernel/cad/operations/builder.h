#pragma once

#include "builderops.h"
#include "documentoperation.h"
#include "undoable.h"
#include <vector>
#include "cad/document/storagemanager.h"

namespace lc {
    class Document;
    namespace operation {


        class Builder: public DocumentOperation, public Undoable {
                friend class lc::operation::Base;

            public:
                /**
                 * @brief Builder constructor
                 * @param document to apply operations
                 */
                Builder(std::shared_ptr<Document> document);

                virtual ~Builder();

                /**
                 * @brief move operation
                 * @param geo::Coordinate offset
                 * @return Builder
                 */
                Builder& move(const geo::Coordinate& offset);

                /**
                 * @brief copy operation
                 * @param geo::Coordinate offset
                 * @return Builder
                 */
                Builder& copy(const geo::Coordinate& offset);

                /**
                 * @brief repeat operation
                 * @param int numTimes
                 * @return Builder
                 */
                Builder& repeat(const int numTimes);

                /**
                 * @brief rotate operation
                 * @param geo::Coordinate rotation_center
                 * @param double rotation_angle
                 * @return Builder builder
                 */
                Builder& rotate(const geo::Coordinate& rotation_center, const double rotation_angle);

                /**
                 * @brief scale operation
                 * @param geo::Coordinate scale_center
                 * @param geo::Coordinate scale_factor
                 * @return Builder builder
                 */
                Builder& scale(const geo::Coordinate& scale_center, const geo::Coordinate& scale_factor);

                /**
                 * @brief begin, begins the builder operation
                 * @return builder
                 */
                Builder& begin();
                Builder& push();

                /**
                 * @brief remove entity from the builder stack
                 * @return Builder builder
                 */
                Builder& remove();
                Builder& selectByLayer(const Layer_CSPtr);

                /**
                 * @brief append, append the entity to builder stack
                 * @param cadEntity
                 * @return Builder builder
                 */
                Builder& append(entity::CADEntity_CSPtr cadEntity);

                /**
                 * Meta data object that needs to be added
                 * Convenient function taht can be usefull during large loading processes
                 */
                Builder& appendMetaData(DocumentMetaType_CSPtr metaData);

                /**
                 * Meta data that needs to be removed
                 * Convenient function that can be usefull during large loading processes
                 */
                Builder& removeMetaData(DocumentMetaType_CSPtr metaData);

                virtual void undo() const;
                virtual void redo() const;

                /**
                 * \brief Apply the operations
                 * Apply operations on the entities without updating the document, and clear the stack.
                 */
                void processStack();

            protected:
                virtual void processInternal();

            private:
                std::vector<Base_SPtr> _stack;
                std::vector<entity::CADEntity_CSPtr> _workingBuffer;


                std::vector<entity::CADEntity_CSPtr> _entitiesThatWhereUpdated;
                std::vector<entity::CADEntity_CSPtr> _entitiesThatNeedsRemoval;

                std::vector<DocumentMetaType_CSPtr > _metaDataThatNeedsUpdate;
        };

        class Builder;
        using Builder_SPtr = std::shared_ptr<Builder>;
    }
}


// BUILDER_H
