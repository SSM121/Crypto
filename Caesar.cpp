#include "Crypto.hpp"
#include "Caesar.hpp"
#include <random>
Caesar::Caesar(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
	       std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
: Crypto(encryptCallback, decryptCallback)
{
}
void Caesar::genKeys()
{
std::random_device rd;
long int x = rd();
m_Key  = (x % 255);
}

bool Caesar::getKeys(uint8_t **pubKey, uint32_t &pubLen,
		     uint8_t **priKey, uint32_t &priLen)
{
**pubKey = m_Key;
pubLen = 1;
return 1;
}

void Caesar::setKeys(const uint8_t *pubKey, uint32_t pubLen,
		     const uint8_t *priKey, uint32_t priLen)
{
m_Key = *pubKey;

}

void Caesar::destroyKeys()
{
m_Key = 0;
}
bool Caesar::encrypt(const uint8_t *data, uint32_t len)
{
uint8_t *cur = new uint8_t[len];



for(uint32_t i =0; i < len; i++)
	{
        cur[i]=data[i];
	cur[i] = (cur[i] + m_Key) % 255;
	
	}
m_encryptCallback(cur, len);
return 1;
}

bool Caesar::decrypt(const uint8_t *data, uint32_t len)
{
uint8_t *cur = new uint8_t[len];

for(uint32_t i=0; i<len; i++)
	{
	cur[i]  = data[i];
	cur[i] = (cur[i] - m_Key)  % 255;
	}
m_decryptCallback(cur, len);
return 1;
}

