#include "socket_operator.h"
#include "c-utils/common/common.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static ret_val socket_client_connect_handler(socket_client_operator *opr,
                                             char *ip_addr, int port) {
  struct sockaddr_in *addr = &opr->client_info.sockaddr;
  memset(addr, 0, sizeof(struct sockaddr_in));
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);
  inet_pton(AF_INET, ip_addr, &(addr->sin_addr));

  if (connect(opr->client_info.sockfd, (struct sockaddr *)addr,
              sizeof(*addr)) == -1) {
    perror("Connection failed");
    close(opr->client_info.sockfd);
    return ret_err;
  }

  return ret_ok;
}

static ret_val socket_server_listen_handler(socket_server_operator *opr,
                                            int port, int max_conn_num) {
  socket_info *info = &opr->server_info;

  memset(&info->sockaddr, 0, sizeof(info->sockaddr));
  info->sockaddr.sin_family = AF_INET;
  info->sockaddr.sin_addr.s_addr = INADDR_ANY;
  info->sockaddr.sin_port = htons(port);

  if (bind(info->sockfd, (struct sockaddr *)&info->sockaddr,
           sizeof(info->sockaddr)) == -1)
    return ret_err;

  if (listen(info->sockfd, max_conn_num) == -1)
    return ret_err;

  return ret_ok;
}

static ret_val socket_server_accept_unblock_handler(socket_server_operator *opr,
                                                    socket_info *info) {
  socket_info *server_info = &opr->server_info;
  int flags = fcntl(server_info->sockfd, F_GETFL, 0);

  if (flags == -1)
    return ret_err;

  if (fcntl(server_info->sockfd, F_SETFL, flags | O_NONBLOCK) == -1)
    return ret_err;

  info->addr_len = sizeof(info->sockaddr);
  info->sockfd = accept(server_info->sockfd, (struct sockaddr *)&info->sockaddr,
                        &info->addr_len);
  if (info->sockfd == -1)
    return ret_err;

  return ret_ok;
}

static ret_val socket_server_accept_block_handler(socket_server_operator *opr,
                                                  socket_info *info) {
  socket_info *server_info = &opr->server_info;
  int flags = fcntl(server_info->sockfd, F_GETFL, 0);

  if (flags == -1)
    return ret_err;

  flags &= ~(O_NONBLOCK);
  if (fcntl(server_info->sockfd, F_SETFL, flags) == -1)
    return ret_err;

  info->addr_len = sizeof(info->sockaddr);
  info->sockfd = accept(server_info->sockfd, (struct sockaddr *)&info->sockaddr,
                        &info->addr_len);
  if (info->sockfd == -1)
    return ret_err;

  return ret_ok;
}

static ret_val socket_create(socket_info *info) {
  info->sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (info->sockfd == -1)
    return ret_err;
  return ret_ok;
}

static ret_val socket_close(socket_info *info) {
  int ret = close(info->sockfd);
  if (ret == -1)
    return ret_err;
  return ret_ok;
}

ret_val socket_client_init(socket_client_operator *opr) {
  opr->connect = socket_client_connect_handler;
  return socket_create(&opr->client_info);
}

ret_val socket_server_init(socket_server_operator *opr) {
  opr->accept_block = socket_server_accept_block_handler;
  opr->accept_unblock = socket_server_accept_unblock_handler;
  opr->listen = socket_server_listen_handler;
  return socket_create(&opr->server_info);
}

ret_val socket_client_connect(socket_client_operator *opr, char *ip_addr,
                              int port) {
  return opr->connect(opr, ip_addr, port);
}

ret_val socket_client_close(socket_client_operator *opr) {
  return socket_close(&opr->client_info);
}

ret_val socket_server_accept_block(socket_server_operator *opr,
                                   socket_info *info) {
  return opr->accept_block(opr, info);
}

ret_val socket_server_accept_unblock(socket_server_operator *opr,
                                     socket_info *info) {
  return opr->accept_unblock(opr, info);
}

ret_val socket_server_listen(socket_server_operator *opr, int port,
                             int max_conn_num) {
  return opr->listen(opr, port, max_conn_num);
}

ret_val socket_server_close(socket_server_operator *opr) {
  return socket_close(&opr->server_info);
}

ssize_t socket_recv(socket_info *info, void *buf, ssize_t len) {
  return recv(info->sockfd, buf, len, 0);
}

ssize_t socket_send(socket_info *info, const void *buf, ssize_t len) {
  return send(info->sockfd, buf, len, 0);
}
