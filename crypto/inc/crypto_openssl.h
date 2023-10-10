/**
 * @file crypto_openssl.h
 * @brief OpenSSL-based Crypto Module Header File
 * @author moecly
 */

#ifndef __CRYPTO_OPENSSL_H_
#define __CRYPTO_OPENSSL_H_

#include "../../common/inc/common.h"
#include "crypto_operator.h"
#include "openssl/evp.h"

/**
 * @brief Create an OpenSSL-based crypto operator.
 *
 * This function initializes an OpenSSL-based crypto operator and associates it
 * with the provided `crypto_operator` structure.
 *
 * @param opr Pointer to the crypto operator to be initialized with OpenSSL.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val create_openssl_crypto_opr(crypto_operator *opr);

#endif // !__CRYPTO_OPENSSL_H_
