#include "../inc/crypto_openssl.h"
#include "c-utils/common/inc/common.h"

static EVP_MD *select_crypto_type(crypto_type type) {
  switch (type) {

  case crypto_type_md4:
    return (EVP_MD *)EVP_md4();
    break;

  case crypto_type_md5:
    return (EVP_MD *)EVP_md5();
    break;

  case crypto_type_md5_sha1:
    return (EVP_MD *)EVP_sha1();
    break;

  case crypto_type_blake2b512:
    return (EVP_MD *)EVP_blake2b512();
    break;

  case crypto_type_blake2s256:
    return (EVP_MD *)EVP_blake2s256();
    break;

  case crypto_type_sha1:
    return (EVP_MD *)EVP_sha1();
    break;

  case crypto_type_sha224:
    return (EVP_MD *)EVP_sha224();
    break;

  case crypto_type_sha256:
    return (EVP_MD *)EVP_sha256();
    break;

  case crypto_type_sha384:
    return (EVP_MD *)EVP_sha384();
    break;

  case crypto_type_sha512:
    return (EVP_MD *)EVP_sha512();
    break;

  case crypto_type_sha512_224:
    return (EVP_MD *)EVP_sha512_224();
    break;

  case crypto_type_sha512_256:
    return (EVP_MD *)EVP_sha512_256();
    break;

  case crypto_type_sha3_224:
    return (EVP_MD *)EVP_sha3_224();
    break;

  case crypto_type_sha3_256:
    return (EVP_MD *)EVP_sha3_256();
    break;

  case crypto_type_sha3_384:
    return (EVP_MD *)EVP_sha3_384();
    break;

  case crypto_type_sha3_512:
    return (EVP_MD *)EVP_sha3_512();
    break;

  case crypto_type_shake128:
    return (EVP_MD *)EVP_shake128();
    break;

  case crypto_type_shake256:
    return (EVP_MD *)EVP_shake256();
    break;
  }

  return NULL;
}

static int openssl_crypto_init_handler(struct crypto_operator *opr,
                                       crypto_type type) {
  crypto_info *info = &opr->info;

  OpenSSL_add_all_digests();

  info->md = select_crypto_type(type);
  info->mdctx = EVP_MD_CTX_new();

  if (info->mdctx == NULL)
    return ret_err;

  if (EVP_DigestInit(info->mdctx, info->md) != 1)
    return ret_err;

  return ret_ok;
}

static int openssl_crypto_update_handler(struct crypto_operator *opr, void *buf,
                                         int len) {
  crypto_info *info = &opr->info;
  if (EVP_DigestUpdate(info->mdctx, buf, (size_t)len) != 1)
    return ret_err;
  return ret_ok;
}

static int openssl_crypto_final_handler(struct crypto_operator *opr,
                                        unsigned char *hash, int *size) {
  crypto_info *info = &opr->info;
  if (EVP_DigestFinal(info->mdctx, hash, (unsigned int *)size) != 1)
    return ret_err;
  return ret_ok;
}

static int openssl_crypto_destroy_handler(struct crypto_operator *opr) {
  crypto_info *info = &opr->info;
  EVP_MD_CTX_free(info->mdctx);
  return ret_ok;
}

ret_val create_openssl_crypto_opr(crypto_operator *opr) {
  opr->init = openssl_crypto_init_handler;
  opr->update = openssl_crypto_update_handler;
  opr->final = openssl_crypto_final_handler;
  opr->destroy = openssl_crypto_destroy_handler;
  return ret_ok;
}
