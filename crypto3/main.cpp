#include <iostream>
#include <fstream>
#include "libs/cryptopp562/sha.h"

#define BLOCK_SIZE 1024

int main(int argv, char** argc)
{
    std::fstream fs1(argc[1], std::ios::in | std::ios::binary);

    CryptoPP::SHA256 hash;

    if (argv > 1){
        if (fs1.is_open())
        {

            size_t block_size = 0;
            byte digest[CryptoPP::SHA256::DIGESTSIZE];
            fs1.seekg(0, fs1.end);
            int digest_size = 0;
            int pos = fs1.tellg();
            while(pos > 0){

                block_size = (pos - 1) % BLOCK_SIZE + 1;
                pos -= block_size;
                fs1.seekg(pos);

                byte buf[block_size + digest_size];\
                fs1.read(reinterpret_cast<char*>(buf), block_size);

                for (int i = 0; i <  digest_size; i++)
                    buf[block_size + i] = digest[i];

                hash.CalculateDigest(digest, buf, block_size+digest_size);

                digest_size = CryptoPP::SHA256::DIGESTSIZE;
            }

            for (int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++)
                std::cout << std::hex << (int)digest[i] << std::dec;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "cannot open file " << argc[1];
        }
    }else{
        byte digest[CryptoPP::SHA256::DIGESTSIZE];
        byte test[2] = {1, 1};
        hash.CalculateDigest(digest, test, 2);
        for (int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++)
            std::cout << std::hex << (int)digest[i] << std::dec;
    }
    std::cout << std::endl;
    return 0;
}

