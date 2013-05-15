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
 * SecuritySymJoinResponse.h
 *
 *  Created on: Mar 16, 2009
 *      Author: Andy, sorin.bidian
 */

#ifndef SECURITYSYMJOINRESPONSE_H_
#define SECURITYSYMJOINRESPONSE_H_


#include <Misc/Convert/Convert.h>
#include <Common/smTypes.h>
#include "Model/Policy.h"
#include <iomanip>

using namespace NE::Misc::Convert;
using namespace NE::Misc::Marshall;

namespace Isa100 {
namespace Security {

struct SecuritySymJoinResponse {
public:
     /**
      * 128_Bit_Challenge_from_system_manager is a fresh unique challenge generated by the system manager
	  * for the device.
      */
     Common::Uint128 BitChallengeFromSystemManager; // 1

     Common::Uint128 BitChallengeResponseToNewDevice;	// 2

     /**
      * The Key_info_from_new_device shall be as defined in I.4.1
      */

     /*
      * The Master_Key_Policy shall have the structure of a compressed policy
      * field as outlined in Table 59 with the first octet elided since it can
      * be inferred implicitly during the key agreement protocol.
      */
     NE::Model::CompressedPolicy MasterKeyPolicy;	// 3

     /*
      * DL_Key_Policy and Sys_Mgr_Session_Key_Policy shall have the structure
      * of a compressed policy field as outlined in Table 59
      */
     NE::Model::CompressedPolicy DlKeyPolicy;	// 4

     NE::Model::CompressedPolicy SysMgrSessionKeyPolicy;	// 5

     Uint8 DLKeyID;	// 6

     /*
      * The DL key and the session key to support the contract with the system
      * manager shall be encrypted using the master key.
      */
     Common::Uint128 EncryptedDLKey;	// 7

     Common::Uint128 EncryptedSysMgrSessionKey;	// 8



     void marshall(OutputStream& stream) {
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.write(BitChallengeFromSystemManager[i]);
         }
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.write(BitChallengeResponseToNewDevice[i]);
         }

         stream.write(MasterKeyPolicy.KeyHardLifetime);
         stream.write(DlKeyPolicy.KeyHardLifetime);
         stream.write(SysMgrSessionKeyPolicy.KeyHardLifetime);
         stream.write(DLKeyID);

         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.write(EncryptedDLKey[i]);
         }
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.write(EncryptedSysMgrSessionKey[i]);
         }
     }

     void unmarshall(InputStream& stream) {
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.read(BitChallengeFromSystemManager[i]);
         }
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.read(BitChallengeResponseToNewDevice[i]);
         }
         stream.read(MasterKeyPolicy.KeyHardLifetime);
         stream.read(DlKeyPolicy.KeyHardLifetime);
         stream.read(SysMgrSessionKeyPolicy.KeyHardLifetime);
         stream.read(DLKeyID);
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.read(EncryptedDLKey[i]);
         }
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream.read(EncryptedSysMgrSessionKey[i]);
         }   }

     std::string toString() {
         std::ostringstream stream;
         stream << "SecuritySymJoinResponse {";

         stream << " BitChallengeFromSystemManager=";
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int) BitChallengeFromSystemManager[i];
             if (i % 2 == 1 && i != Common::CHALLENGE_BYTES_NO - 1) {
                 stream << ':';
             }
         }
         stream << ", BitChallengeResponseToNewDevice=";
         for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
             stream << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int) BitChallengeResponseToNewDevice[i];
             if (i % 2 == 1 && i != Common::CHALLENGE_BYTES_NO - 1) {
                 stream << ':';
             }
         }

        std::string policyString;
        NE::Model::ToString(MasterKeyPolicy, policyString);
        stream << ", MasterKeyPolicy=" << policyString;

        NE::Model::ToString(DlKeyPolicy, policyString);
        stream << ", DlKeyPolicy=" << policyString ;

        NE::Model::ToString(SysMgrSessionKeyPolicy, policyString);
		stream << ", SysMgrSessionKeyPolicy=" << policyString;

		 stream << ", DLKeyID=" << (int)DLKeyID;

		 stream << ", EncryptedDLKey=";
		 for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
			 stream << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int) EncryptedDLKey[i];
			 if (i % 2 == 1 && i != Common::CHALLENGE_BYTES_NO - 1) {
				 stream << ':';
			 }
		 }
		 stream << ", EncryptedSysMgrSessionKey=";
		 for (Uint8 i = 0; i < Common::CHALLENGE_BYTES_NO; i++) {
			 stream << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int) EncryptedSysMgrSessionKey[i];
			 if (i % 2 == 1 && i != Common::CHALLENGE_BYTES_NO - 1) {
				 stream << ':';
			 }
		 }

		 stream << "}";
		 return stream.str();
     }
};

}
}
#endif /* SECURITYSYMJOINRESPONSE_H_ */