#ifndef __SOCKET_OPERATOR_H_
#define __SOCKET_OPERATOR_H_

#include "c-utils/common/common.h"
#include <arpa/inet.h>

typedef struct {
  int sockfd;
  struct sockaddr_in sockaddr;
  socklen_t addr_len;
} socket_info;

typedef struct socket_client_operator {
  socket_info client_info;
  ret_val (*connect)(struct socket_client_operator *opr, char *ip_addr,
                     int port);
  ssize_t (*send)(struct socket_client_operator *opr, const void *buf,
                  ssize_t len);
} socket_client_operator;

typedef struct socket_server_operator {
  socket_info server_info;
  ret_val (*accept_unblock)(struct socket_server_operator *opr,
                            socket_info *info);
  ret_val (*accept_block)(struct socket_server_operator *opr,
                          socket_info *info);
  ssize_t (*send)(struct socket_server_operator *opr, const void *buf,
                  ssize_t len);
  ret_val (*listen)(struct socket_server_operator *opr, int port,
                    int max_conn_num);
} socket_server_operator;

ret_val socket_client_init(socket_client_operator *opr);

ret_val socket_server_init(socket_server_operator *opr);

ret_val socket_client_connect(socket_client_operator *opr, char *ip_addr,
                              int port);

ret_val socket_client_send(socket_client_operator *opr, const void *buf,
                           ssize_t len);

ret_val socket_server_accept_block(socket_server_operator *opr,
                                   socket_info *info);

ret_val socket_server_accept_unblock(socket_server_operator *opr,
                                     socket_info *info);

ret_val socket_server_send(socket_server_operator *opr, const void *buf,
                           ssize_t len);

ret_val socket_server_listen(socket_server_operator *opr, int port,
                             int max_conn_num);

ssize_t socket_recv(socket_info *info, void *buf, ssize_t len);

#endif // !__SOCKET_OPERATOR_H_
