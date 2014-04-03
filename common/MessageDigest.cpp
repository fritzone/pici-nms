#include "MessageDigest.h"

char* MessageDigest::spc_digest_message(const EVP_MD *type, const char *in, unsigned long n, unsigned int *outlen) 
{
EVP_MD_CTX    ctx;
char *ret;

	EVP_DigestInit(&ctx, type);
	EVP_DigestUpdate(&ctx, in, n);
	if (!(ret = (char*)malloc(EVP_MD_CTX_size(&ctx)))) return 0;
	EVP_DigestFinal(&ctx, reinterpret_cast<unsigned char*>(ret), outlen);
	return ret;
}

string MessageDigest::getHashCode(const std::string &input)
{
unsigned int outlen = 0;
string result;
char* r = spc_digest_message(EVP_sha1(), input.c_str(), input.length(), &outlen);
	for(int i=0; i<outlen; i++)
	{
	char s[10];
		sprintf(s, "%2X", (unsigned char)r[i]);
		if(s[0] == ' ') s[0] = '0';
		result += s;
	}
	free(r);
	return result;
}