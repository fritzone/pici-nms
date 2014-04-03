#ifndef _MESSAGE_DIGEST_H_
#define _MESSAGE_DIGEST_H_

#include <openssl/evp.h>

#include <stdlib.h>
#include <string>


using namespace std;

/**
 * Class representing a message digestet, generates SHA hash codes for various stuff
 */
class MessageDigest
{
public:
	static string getHashCode(const string& input);

private:

	static char *spc_digest_message(const EVP_MD *type, const char *in, unsigned long n, unsigned int *outlen); 
};

#endif
