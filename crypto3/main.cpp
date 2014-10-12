#include <iostream>
#include <fstream>
#include "libs/cryptopp562/sha.h"

#define BLOCK_SIZE 1024

int main(int argv, char** argc)
{
    std::fstream fs1(argc[1], std::ios::in | std::ios::out | std::ios::binary);
    CryptoPP::SHA256 hash;

    size_t bufsize = 0;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    do{
        int pos = fs1.tellg();
        if (pos >= BLOCK_SIZE - 1) //reading from end, so we need to know distance from beginning of the file
            bufsize = BLOCK_SIZE;
        else
            bufsize = pos + 1;

        byte buf[bufsize];
        fs1.seekg(pos - bufsize);
        fs1.read(reinterpret_cast<char*>(buf), bufsize);
        hash.CalculateDigest(digest, buf, bufsize);
        fs1.seekp(pos - bufsize);
        for (int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++) //appending current MAC to the previous block
            fs1 << digest[i];
        fs1.seekg(pos - bufsize + CryptoPP::SHA256::DIGESTSIZE); //returning again, because read() shifted our position in stream, but we also appended MAC to the end of stream, so position shifted to MAC size
    }while(bufsize == BLOCK_SIZE);

    for (int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++)
        std::cout << digest[i];

    return 0;
}

