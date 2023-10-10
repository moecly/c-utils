/**
 * @file crypto_operator.c
 * @brief Crypto Operator Implementation File
 * @author moecly
 */

#include "../inc/crypto_operator.h"
#include "c-utils/common/inc/common.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Initializes a crypto operator with the specified crypto type.
 *
 * This function initializes a crypto operator with the specified crypto type.
 *
 * @param opr Pointer to the crypto operator.
 * @param type The crypto type to use for initialization.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val crypto_init(crypto_operator *opr, crypto_type type) {
  return opr->init(opr, type);
}

/**
 * @brief Updates the crypto operation with the provided data.
 *
 * This function updates the crypto operation with the provided data.
 *
 * @param opr Pointer to the crypto operator.
 * @param buf Pointer to the data buffer to update the crypto operation.
 * @param len Length of the data to update.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val crypto_update(struct crypto_operator *opr, void *buf, int len) {
  return opr->update(opr, buf, len);
}

/**
 * @brief Finalizes the crypto operation and retrieves the hash.
 *
 * This function finalizes the crypto operation and retrieves the hash and its
 * size.
 *
 * @param opr Pointer to the crypto operator.
 * @param hash Pointer to the buffer to store the hash.
 * @param size Pointer to store the size of the hash.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val crypto_final(struct crypto_operator *opr, unsigned char *hash,
                            int *size) {
  return opr->final(opr, hash, size);
}

/**
 * @brief Destroys the crypto operator.
 *
 * This function destroys the crypto operator, freeing any allocated resources.
 *
 * @param opr Pointer to the crypto operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val crypto_destroy(crypto_operator *opr) {
  return opr->destroy(opr);
}

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
                        unsigned char *hash, int *size) {
  int fd;

  crypto_init(opr, type);
  fd = open(file_path, O_RDONLY);
  if (fd < 0)
    goto err_open;

  unsigned char buffer[256];
  size_t bytes_read;

  // Read the file in chunks and update the crypto calculation
  while ((bytes_read = read(fd, buffer, (size_t)sizeof(buffer))) > 0) {
    if (crypto_update(opr, buffer, (int)bytes_read) != ret_ok)
      goto err_update;
  }

  // Finalize the calculation and retrieve the hash
  if (crypto_final(opr, hash, size) != ret_ok)
    goto err_final;

  crypto_destroy(opr);
  return ret_ok;

err_final:
err_update:
  close(fd);
err_open:
  return ret_err;
}
