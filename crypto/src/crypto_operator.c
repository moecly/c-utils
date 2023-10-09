#include "../inc/crypto_operator.h"
#include "c-utils/common/inc/common.h"
#include <fcntl.h>
#include <unistd.h>

static ret_val crypto_init(crypto_operator *opr, crypto_type type) {
  return opr->init(opr, type);
}

static ret_val crypto_update(struct crypto_operator *opr, void *buf, int len) {
  return opr->update(opr, buf, len);
}

static ret_val crypto_final(struct crypto_operator *opr, unsigned char *hash,
                            int *size) {
  return opr->final(opr, hash, size);
}

static ret_val crypto_destroy(crypto_operator *opr) {
  return opr->destroy(opr);
}

ret_val crypto_cal_file(crypto_operator *opr, crypto_type type, char *file_path,
                        unsigned char *hash, int *size) {
  int fd;

  crypto_init(opr, type);
  fd = open(file_path, O_RDONLY);
  if (fd < 0)
    goto err_open;

  unsigned char buffer[256];
  size_t bytes_read;

  // 逐块读取文件并更新计算
  while ((bytes_read = read(fd, buffer, (size_t)sizeof(buffer))) > 0) {
    if (crypto_update(opr, buffer, (int)bytes_read) != ret_ok)
      goto err_update;
  }

  // 完成计算，获取 SHA256 校验和
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
