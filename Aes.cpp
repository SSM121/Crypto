#include "Crypto.hpp"
#include "Aes.hpp"
#include <iostream>
#include <mcrypt.h>
#include <random>
#include <cstring>

void Aes::genKeys()
{
std::random_device rd;
int i;
long int x;
for(i = 0; i < m_Len; i++)
{
	x = rd() % 255;
	m_Key[i] = x;	
}
m_exist = 1;
for(i = 0; i < mcrypt_enc_get_iv_size(td); i++)
{
	m_IV[i] = rd() % 255;
}
mcrypt_generic_init(td, m_Key, m_Len, m_IV);
}

bool Aes::getKeys(uint8_t **pubKey, uint32_t &pubLen,
             uint8_t **priKey, uint32_t &priLen)
{
if(m_exist == 0)
{
return 0;
}
(*priKey) = new uint8_t[2 * m_Len];
std::memcpy((*priKey) + 0,     m_Key, m_Len);
std::memcpy((*priKey) + m_Len, m_IV,  m_Len);
return 1;
}

void Aes::setKeys(const uint8_t *pubKey, uint32_t pubLen,
             const uint8_t *priKey, uint32_t priLen)
{
int i;

for(i = 0; i < m_Len; i++)
{
	m_Key[i] = priKey[i];
}
for(i = 0; i < m_Len; i++)
{
        m_Key[i + m_Len] = m_IV[i];
}


m_exist = 1;
mcrypt_generic_init(td, m_Key, m_Len, m_IV);

}

void Aes::destroyKeys()
{
m_Key = nullptr;
m_IV = nullptr;
m_exist = 0;
}

bool Aes::encrypt(const uint8_t *data, uint32_t len)
{
uint8_t *l_encrypt;
uint8_t o;
if(len = 0)
{
o = m_Buffer.size();
for(int y = 0; y < m_Len - o; y++)
{
m_Buffer.push(0);
}

mcrypt_generic(td, l_encrypt, m_Len);
l_encrypt[m_Len + 1] = o;
m_encryptCallback(l_encrypt, (m_Len + 1));
}
for(int i = 0; i < len; i++)
{
	m_Buffer.push(data[i]);
}
if(m_Buffer.size() >= m_Len)
{
	for(int u = 0; u < m_Len; u++)
	{
		l_encrypt[u] = m_Buffer.front();
		m_Buffer.pop();
	}
mcrypt_generic(td, l_encrypt, m_Len);
m_encryptCallback(l_encrypt, (m_Len));
	 
} 


return 1;
}

bool Aes::decrypt(const uint8_t *data, uint32_t len)
{
uint8_t *l_decrypt;
uint32_t p = m_Len;  
uint32_t j = 16;
                                                    
for(int t = 0; t < len; t++)
{
m_Buffer.push(data[t]);
}

if(m_Buffer.size() >= m_Len)
{
	for(int u = 0; u < m_Len; u++)
	{
		l_decrypt[u] = m_Buffer.front();
		m_Buffer.pop();
	}

}
if(len == 0)
{
j = m_Buffer.front();
m_Buffer.pop();
}

mdecrypt_generic(td, l_decrypt, m_Len);
m_decryptCallback(l_decrypt, (j));




return 1;

}
