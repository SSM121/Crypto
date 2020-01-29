#ifndef NONE_HPP
#define NONE_HPP
#include "Crypto.hpp"


class None : public  Crypto
{
public:
None(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
     std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
: Crypto(encryptCallback, decryptCallback)
{
}
void genKeys();
bool getKeys(uint8_t **pubKey, uint32_t &pubLen,
             uint8_t **priKey, uint32_t &ptiLen);
void setKeys(const uint8_t *pubKey, uint32_t pubLen,
             const uint8_t *priKey, uint32_t ptiLen);
void destroyKeys();
bool encrypt(const uint8_t *data, uint32_t len);
bool decrypt(const uint8_t *data, uint32_t len);

};


#endif
