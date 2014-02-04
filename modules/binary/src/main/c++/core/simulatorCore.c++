#include "simulatorCore.h++"
#include <errorHandling/assert.h++>

#include <openssl/md5.h>
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
            unsigned char digest[MD5_DIGEST_LENGTH];
            char buffer[1024];
            MD5_CTX md5Context;
            MD5_Init(&md5Context);

            std::ifstream file(fileName);
            assertX(file.is_open());
            while(!(file.eof())) {
                //std::streamsize n = file.readsome(buffer, sizeof(buffer));
                file.read(buffer, sizeof(buffer));
                std::streamsize n = file.gcount();
                MD5_Update(&md5Context, buffer, n);
            }
            file.close();
            MD5_Final(digest, &md5Context);
            std::stringstream ssDigest;
            for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
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
