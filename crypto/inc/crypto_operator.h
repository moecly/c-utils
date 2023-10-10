/**
 * @file crypto_operator.h
 * @brief Crypto Operator Header File
 * @author moecly
 */

#ifndef __CRYPTO_OPERATOR_H_
#define __CRYPTO_OPERATOR_H_

#include "../../common/inc/common.h"

#define USE_OPENSSL
#ifdef USE_OPENSSL
#include "openssl/evp.h"
/**
 * @brief Structure holding cryptographic information.
 */
typedef struct {
  EVP_MD *md;        /**< OpenSSL EVP_MD structure */
  EVP_MD_CTX *mdctx; /**< OpenSSL EVP_MD_CTX structure */
} crypto_info;
#endif

/**
 * @brief Maximum size of a cryptographic hash.
 */
#define HASH_MAX_SIZE 64

/**
 * @brief Enumeration of supported crypto types.
 */
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

/**
 * @brief Structure defining a cryptographic operator.
 */
typedef struct crypto_operator {
  crypto_info info; /**< Cryptographic information */
  int (*init)(struct crypto_operator *opr,
              crypto_type type); /**< Initialization function */
  int (*update)(struct crypto_operator *opr, void *buf,
                int len); /**< Update function */
  int (*final)(struct crypto_operator *opr, unsigned char *hash,
               int *size);                     /**< Finalize function */
  int (*destroy)(struct crypto_operator *opr); /**< Destruction function */
} crypto_operator;

/**
 * @brief Calculate the hash of a file using a crypto operator.
 *
 * This function calculates the hash of a file using the specified crypto
 * operator and crypto type. It reads the file in chunks and updates the crypto
 * operation accordingly.
 *
 * @param opr Pointer to the crypto operator.
 * @param type The crypto type to use for the calculation.
 * @param file_path Path to the file to calculate the hash for.
 * @param hash Pointer to the buffer to store the hash.
 * @param size Pointer to store the size of the hash.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val crypto_cal_file(crypto_operator *opr, crypto_type type, char *file_path,
                        unsigned char *hash, int *size);

#endif // !__CRYPTO_OPERATOR_H_
