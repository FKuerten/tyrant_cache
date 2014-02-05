#include "simulatorCore.h++"
#include <errorHandling/assert.h++>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/md5.h>
#include <fstream>
#include <map>

namespace TyrantCache {
    namespace Core {

        SimulatorCore::~SimulatorCore() {}

        void
        hashFile(std::map<std::string,std::string> & hashes
                ,std::string fileName
                )
        {
            CryptoPP::Weak1::MD5 hash;
            byte digest[ CryptoPP::Weak1::MD5::DIGESTSIZE ];
            char buffer[1024];

            std::ifstream file(fileName);
            if(! file.is_open()) {
                throw RuntimeError("file not found: " + fileName);
            }
            while(!(file.eof())) {
                file.read(buffer, sizeof(buffer));
                std::streamsize n = file.gcount();
                hash.Update((byte*)buffer, n);
            }
            file.close();
            hash.Final(digest);
            std::stringstream ssDigest;
            for(int i = 0; i < CryptoPP::Weak1::MD5::DIGESTSIZE; i++) {
                ssDigest << std::setw(2) << std::setfill('0') << std::hex << (unsigned int)(digest[i]);
            }
            hashes[fileName] = ssDigest.str();
        }

        std::map<std::string,std::string> SimulatorCore::getXMLVersions() const
        {
            std::map<std::string,std::string> hashes;
            hashFile(hashes, "achievements.xml");
            hashFile(hashes, "cards.xml");
            hashFile(hashes, "missions.xml");
            hashFile(hashes, "raids.xml");
            hashFile(hashes, "quests.xml");
            return hashes;
        }

    }
}
