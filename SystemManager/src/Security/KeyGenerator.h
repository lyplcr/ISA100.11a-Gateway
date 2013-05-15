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

#ifndef KEYGENERATOR_H_
#define KEYGENERATOR_H_

#include <cstdlib>
#include "Model/SecurityKey.h"
#include "Common/logging.h"

using namespace NE::Model;

namespace Isa100 {
namespace Security {

/**
 * Generates randomly new Security Keys
 * @author catalin.pop, ion.ticus, andrei.petrut
 * @version 1.0
 */
class KeyGenerator {
        LOG_DEF("I.S.KeyGenerator");

    private:
        //The challenge generated by System Manager
        Uint32 nextChallenge;

    public:
        KeyGenerator();

        virtual ~KeyGenerator();

        /**
         * Generates randomly a new Security Key
         * @return the new generated key
         */
        virtual SecurityKey generateKey();

        /**
         * Returns the next challenge
         */
        virtual Uint32 getNextChallenge();

        /**
         * Reset the value of the next chellenge
         * @param Uint32 - next challenge
         */
        virtual void setNextChallenge(Uint32 nextChallenge);
};
}
}
#endif /*KEYGENERATOR_H_*/
