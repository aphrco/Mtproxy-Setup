
#pragma once

#include <openssl/evp.h>
#include <openssl/opensslv.h>

#if OPENSSL_VERSION_NUMBER < 0x10100000
#define EVP_MD_CTX_new EVP_MD_CTX_create
#define EVP_MD_CTX_free EVP_MD_CTX_destroy
#endif

typedef EVP_MD_CTX sha256_context;

void sha256_starts (sha256_context *ctx);
void sha256_update (sha256_context *ctx, const unsigned char *input, int ilen);
void sha256_finish (sha256_context *ctx, unsigned char output[32]);
void sha256 (const unsigned char *input, int ilen, unsigned char output[32]);
void sha256_two_chunks (const unsigned char *input1, int ilen1, const unsigned char *input2, int ilen2, unsigned char output[32]);

void sha256_hmac (unsigned char *key, int keylen, unsigned char *input, int ilen, unsigned char output[32]);
