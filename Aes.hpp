#ifndef AES_HPP
#define AES_HPP
#include "Crypto.hpp"
#include <queue>
#include <mcrypt.h>
class Aes : public  Crypto
{
public:
Aes(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
     std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
: Crypto(encryptCallback, decryptCallback)
{
m_Len = 16;
m_exist = 0;
td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
}
~Aes()
{
mcrypt_generic_deinit(td);
mcrypt_module_close(td);
}
void genKeys();
bool getKeys(uint8_t **pubKey, uint32_t &pubLen,
             uint8_t **priKey, uint32_t &ptiLen);
void setKeys(const uint8_t *pubKey, uint32_t pubLen,
             const uint8_t *priKey, uint32_t ptiLen);
void destroyKeys();
bool encrypt(const uint8_t *data, uint32_t len);
bool decrypt(const uint8_t *data, uint32_t len);

protected:
uint8_t *m_Key;
uint32_t m_Len;
std::queue<uint8_t> m_Buffer; 
bool m_exist;
MCRYPT td;
uint8_t *m_IV;
};


#endif
