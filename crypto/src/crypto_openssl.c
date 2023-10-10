/**
 * @file crypto_openssl.c
 * @brief OpenSSL-based Crypto Module Implementation File
 * @author moecly
 */

#include "../inc/crypto_openssl.h"
#include "c-utils/common/inc/common.h"

/**
 * @brief Select the OpenSSL digest method based on the crypto_type.
 *
 * This function selects the OpenSSL digest method based on the provided
 * crypto_type.
 *
 * @param type The crypto_type to select the digest method for.
 * @return Returns the selected EVP_MD method or NULL if not found.
 */
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

/**
 * @brief Initialize the OpenSSL crypto operator.
 *
 * This function initializes the OpenSSL crypto operator and selects the digest
 * method.
 *
 * @param opr Pointer to the crypto operator to be initialized.
 * @param type The crypto_type to use for initialization.
 * @return Returns ret_ok on success, ret_err on failure.
 */
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

/**
 * @brief Update the OpenSSL crypto operator with data.
 *
 * This function updates the OpenSSL crypto operator with data.
 *
 * @param opr Pointer to the crypto operator.
 * @param buf Pointer to the data buffer.
 * @param len Length of the data buffer.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static int openssl_crypto_update_handler(struct crypto_operator *opr, void *buf,
                                         int len) {
  crypto_info *info = &opr->info;
  if (EVP_DigestUpdate(info->mdctx, buf, (size_t)len) != 1)
    return ret_err;
  return ret_ok;
}

/**
 * @brief Finalize the OpenSSL crypto operator and get the hash.
 *
 * This function finalizes the OpenSSL crypto operator and retrieves the hash
 * and size.
 *
 * @param opr Pointer to the crypto operator.
 * @param hash Pointer to the hash buffer.
 * @param size Pointer to the size of the hash.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static int openssl_crypto_final_handler(struct crypto_operator *opr,
                                        unsigned char *hash, int *size) {
  crypto_info *info = &opr->info;
  if (EVP_DigestFinal(info->mdctx, hash, (unsigned int *)size) != 1)
    return ret_err;
  return ret_ok;
}

/**
 * @brief Destroy the OpenSSL crypto operator.
 *
 * This function destroys the OpenSSL crypto operator and frees resources.
 *
 * @param opr Pointer to the crypto operator to be destroyed.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static int openssl_crypto_destroy_handler(struct crypto_operator *opr) {
  crypto_info *info = &opr->info;
  EVP_MD_CTX_free(info->mdctx);
  return ret_ok;
}

/**
 * @brief Create an OpenSSL-based crypto operator.
 *
 * This function initializes an OpenSSL-based crypto operator and associates it
 * with the provided `crypto_operator` structure.
 *
 * @param opr Pointer to the crypto operator to be initialized with OpenSSL.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val create_openssl_crypto_opr(crypto_operator *opr) {
  opr->init = openssl_crypto_init_handler;
  opr->update = openssl_crypto_update_handler;
  opr->final = openssl_crypto_final_handler;
  opr->destroy = openssl_crypto_destroy_handler;
  return ret_ok;
}
