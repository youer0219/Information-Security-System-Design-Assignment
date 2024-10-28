#include <pch.h>
#include "openssl/evp.h"
#include "sm3hash.h"

int sm3_hash(const unsigned char *message, size_t len, unsigned char *hash, unsigned int *hash_len)
{
	EVP_MD_CTX *md_ctx;
	const EVP_MD *md;

	md = EVP_sm3();
	md_ctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(md_ctx, md, NULL);
	EVP_DigestUpdate(md_ctx, message, len);
	EVP_DigestFinal_ex(md_ctx, hash, hash_len);
	EVP_MD_CTX_free(md_ctx);
	return 0;
}
