/*
* Copyright (C) 2013 Nivis LLC.
* Email:   opensource@nivis.com
* Website: http://www.nivis.com
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3 of the License.
* 
* Redistribution and use in source and binary forms must retain this
* copyright notice.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#ifndef READATTRIBUTEOPERATION_H_
#define READATTRIBUTEOPERATION_H_

#include "Model/Operations/IEngineOperation.h"

namespace NE {

namespace Model {

namespace Operations {


/**
 * Operation used to read an attribute from a device. The address of the device, the entity type
 * and the attribute value index are contained in EntityIndex.
 * @author Radu Pop
 * @version 1.0
 */
class ReadAttributeOperation: public NE::Model::Operations::IEngineOperation {

    public:

        ReadAttributeOperation(EntityIndex entityIndex);

        virtual ~ReadAttributeOperation();

        /**
         *
         */
        bool accept(IEngineOperationsVisitor & visitor);

        std::ostream& toString(std::ostream& stream) const;


        /**
         * Returns a string representation of this operation.
         */
        friend std::ostream& operator<<(std::ostream&, const ReadAttributeOperation& operation);
};

typedef boost::shared_ptr<ReadAttributeOperation> ReadAttributeOperationPointer;

}

}

}

#endif /* READATTRIBUTEOPERATION_H_ */
