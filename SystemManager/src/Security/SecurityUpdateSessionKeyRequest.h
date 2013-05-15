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

/*
 * SecurityUpdateSessionKeyRequest.h
 *
 *  Created on: Jun 10, 2009
 *      Author:fl0r1
 */

#ifndef SECURITYUPDATESESSIONKEYREQUEST_H_
#define SECURITYUPDATESESSIONKEYREQUEST_H_


#include "Misc/Convert/Convert.h"
#include "Common/smTypes.h"
#include "Common/NEAddress.h"

using namespace NE::Misc::Convert;
using namespace NE::Misc::Marshall;

namespace Isa100 {
namespace Security {

/**
 * Security session key update request from a device to security manager.
 */

struct SecurityUpdateSessionKeyRequest{
    /**
     * 128_Bit_Address_A shall be the 128-bit network address of the first end device
     * (typically the source) in the session.
     */
    Address128 address128A;

    /**
     * 128_Bit_Address_B shall be the 128-bit network address of the second end device
     * (typically the destination) in the session.
     */
    Address128 address128B;

    /**
     *
     */
    TSAP::TSAP_Enum endPortA;

    /**
     *
     */
    TSAP::TSAP_Enum endPortB;

    /**
     * Algorithm_Identifier defines the algorithm and mode of operation supported in this session.
     * In the current release this shall be set to 0x1 = AES_CCM*.
     */
    Uint8 algorithmIdentifier;

    /**
     * The protocol version identifies the protocol used for this security association.
     * In this standard, this octet shall be 0x01.
     */
    Uint8 protocolVersion;

    /**
     * Security_Control shall be as defined in 7.3.3.2 with the security level = 0x01 (32-bit Authentication only)
     * and the Key Identifier Mode shall be b 1 b 0 01 corresponding to a Key index Field length of 1 octet.
     */
    Uint8 securityControl;

    /**
     * Key_Identifier shall be the key identifier of the master key used in protecting this structure.
     */
    Uint8 keyIdentifier;

    /**
     * Time_Stamp shall be the full 32-bit time used in the nonce construction.
     */
    Uint32 timeStamp;

    /**
     * MIC shall be the 32-bit integrity code generated by the AES_CCM* computation.
     */
    Uint32 MIC;

    void marshall(OutputStream& stream) {
        address128A.marshall(stream);
        address128B.marshall(stream);
        stream.write((uint16_t)endPortA);
        stream.write((uint16_t)endPortB);
        stream.write(algorithmIdentifier);
        stream.write(protocolVersion);
        stream.write(securityControl);
        stream.write(keyIdentifier);
        stream.write(timeStamp);
        stream.write(MIC);
    }

    void unmarshall(InputStream& stream) {

        address128A.unmarshall(stream);
        address128B.unmarshall(stream);
        Uint16 portA;
        stream.read(portA);
        endPortA = (TSAP::TSAP_Enum) portA;
        Uint16 portB;
        stream.read(portB);
        endPortB = (TSAP::TSAP_Enum) portB;
        stream.read(algorithmIdentifier);
        stream.read(protocolVersion);
        stream.read(securityControl);
        stream.read(keyIdentifier);
        stream.read(timeStamp);
        stream.read(MIC);
    }

    void toString( std::string &updateKeyString) {
        std::ostringstream stream;
        stream << "SecurityUpdateSessionKeyRequest {";
        stream << "address128A=" << address128A.toString();
        stream << ", address128B=" << address128B.toString();
        stream << ", endPortA=" << endPortA;
        stream << ", endPortB=" << endPortB;
        stream << ", algorithmIdentifier=" << algorithmIdentifier;
        stream << ", protocolVersion=" << protocolVersion;
        stream << ", securityControl=" << securityControl;
        stream << ", keyIdentifier=" << keyIdentifier;
        stream << ", timeStamp=" << timeStamp;
        stream << ", mic=" << MIC;
        stream << "}";

        updateKeyString =  stream.str();
    }

};

}

}

#endif /* SECURITYUPDATESESSIONKEYREQUEST_H_ */
