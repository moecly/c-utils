#ifndef __CRYPTO_H_
#define __CRYPTO_H_

#include "../../common/inc/common.h"
#include <openssl/evp.h>

#define HASH_MAX_SIZE 64

typedef enum {
  crypto_type_md4,
  crypto_type_md5,
  crypto_type_md5_sha1,
  crypto_type_blake2b512,
  crypto_type_blake2s256,
  crypto_type_sha1,
  crypto_type_sha224,
  crypto_type_sha256,
  crypto_type_sha384,
  crypto_type_sha512,
  crypto_type_sha512_224,
  crypto_type_sha512_256,
  crypto_type_sha3_224,
  crypto_type_sha3_256,
  crypto_type_sha3_384,
  crypto_type_sha3_512,
  crypto_type_shake128,
  crypto_type_shake256,
} crypto_type;

typedef struct {
  EVP_MD *md;
  EVP_MD_CTX *mdctx;
} crypto_info;

typedef struct crypto_operator {
  crypto_info info;
  int (*init)(struct crypto_operator *opr, crypto_type type);
  int (*update)(struct crypto_operator *opr, void *buf, int len);
  int (*final)(struct crypto_operator *opr, unsigned char *hash, int *size);
  int (*destroy)(struct crypto_operator *opr);
} crypto_operator;

ret_val crypto_cal_file(crypto_operator *opr, crypto_type type, char *file_path,
                        unsigned char *hash, int *size);

#endif // !__CRYPTO_H_
