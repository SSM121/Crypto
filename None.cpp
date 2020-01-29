#include "Crypto.hpp"
#include "None.hpp"
#include <iostream>


void None::genKeys()
{

}

bool None::getKeys(uint8_t **pubKey, uint32_t &pubLen,
             uint8_t **priKey, uint32_t &ptiLen)
{

return 1;
}

void None::setKeys(const uint8_t *pubKey, uint32_t pubLen,
             const uint8_t *priKey, uint32_t priLen)
{


}

void None::destroyKeys()
{

}

bool None::encrypt(const uint8_t *data, uint32_t len)
{
m_encryptCallback(data, len);
return 1;
}

bool None::decrypt(const uint8_t *data, uint32_t len)
{
m_decryptCallback(data, len);
return 1;

}
