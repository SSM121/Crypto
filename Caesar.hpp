#ifndef CAESAR_HPP
#define CAESAR_HPP

#include "Crypto.hpp"

class Caesar : public Crypto
{
public:
Caesar(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
       std::function<void(const uint8_t *data, uint32_t len)> decryptCallback);
void genKeys();
bool getKeys(uint8_t **pubKey, uint32_t &pubLen,
             uint8_t **priKey, uint32_t &priLen);
void setKeys(const uint8_t *pubKey, uint32_t pubLen,
	     const uint8_t *priKey, uint32_t priLen);
void destroyKeys();
bool encrypt(const uint8_t *data, uint32_t len);
bool decrypt(const uint8_t *data, uint32_t len);


private:
uint8_t m_Key;
uint8_t m_priKey;

};
#endif
