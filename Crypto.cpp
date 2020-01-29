#include "Crypto.hpp"
#include "Caesar.hpp"
#include "None.hpp"
#include <iostream>
#include "Aes.hpp"
Crypto::Crypto(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
         std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
: m_encryptCallback(encryptCallback), m_decryptCallback(decryptCallback)
{
}



std::shared_ptr<Crypto> Crypto::cryptoFactory(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,                                              std::function<void(const uint8_t *data, uint32_t len)> decryptCallback,
                                             Algorithm algorithm)
{
std::shared_ptr<Crypto> Cr;
switch(algorithm)
	{
	case Algorithm::eNONE:
	{
		Cr.reset(new None(encryptCallback, decryptCallback));
		break;
	}
	case Algorithm::eCAESAR:
	{
		Cr.reset(new Caesar(encryptCallback, decryptCallback));
		break;
	}
	case Algorithm::eAES:
	{
		Cr.reset(new Aes(encryptCallback, decryptCallback));
		break;
	}
	default:
	{
		std::cout << "Could not recognize encryption type. " << std::endl;
		break;
	}

	}
return Cr;
}
