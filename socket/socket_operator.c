/**
 * @file socket_operator.c
 * @brief Socket Operator Source File
 * @author moecly
 */

#include "socket_operator.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/**
 * @brief Connects a client socket to a server.
 *
 * This function establishes a connection from a client socket to a server
 * with the specified IP address and port.
 *
 * @param opr Pointer to the socket client operator.
 * @param ip_addr IP address of the server.
 * @param port Port number of the server.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val socket_client_connect_handler(socket_client_operator *opr,
                                             char *ip_addr, int port) {
  struct sockaddr_in *addr = &opr->client_info.sockaddr;
  memset(addr, 0, sizeof(struct sockaddr_in));
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);
  inet_pton(AF_INET, ip_addr, &(addr->sin_addr));

  if (connect(opr->client_info.sockfd, (struct sockaddr *)addr,
              sizeof(*addr)) == -1)
    return ret_err;

  return ret_ok;
}

/**
 * @brief Listens for incoming connections on the server socket.
 *
 * This function prepares the server socket to accept incoming connections
 * on the specified port and maximum connection number.
 *
 * @param opr Pointer to the socket server operator.
 * @param port Port number to listen on.
 * @param max_conn_num Maximum number of connections.
 * @return Returns ret_ok on success, ret_err on failure.
 */
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

/**
 * @brief Accepts an incoming connection on the server socket (non-blocking).
 *
 * This function accepts an incoming connection on the server socket in
 * non-blocking mode, setting the socket of the accepted connection in the
 * provided `info` structure.
 *
 * @param opr Pointer to the socket server operator.
 * @param info Pointer to the socket_info structure to store connection details.
 * @return Returns ret_ok on success, ret_err on failure.
 */
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

/**
 * @brief Accepts an incoming connection on the server socket (blocking).
 *
 * This function accepts an incoming connection on the server socket in
 * blocking mode, setting the socket of the accepted connection in the
 * provided `info` structure.
 *
 * @param opr Pointer to the socket server operator.
 * @param info Pointer to the socket_info structure to store connection details.
 * @return Returns ret_ok on success, ret_err on failure.
 */
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

/**
 * @brief Creates a socket and initializes the socket_info structure.
 *
 * This function creates a socket and initializes the socket_info structure.
 *
 * @param info Pointer to the socket_info structure.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val socket_create(socket_info *info) {
  info->sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (info->sockfd == -1)
    return ret_err;
  return ret_ok;
}

/**
 * @brief Closes a socket.
 *
 * This function closes a socket.
 *
 * @param info Pointer to the socket_info structure.
 * @return Returns ret_ok on success, ret_err on failure.
 */
static ret_val socket_close(socket_info *info) {
  int ret = close(info->sockfd);
  if (ret == -1)
    return ret_err;
  return ret_ok;
}

/**
 * @brief Initializes a socket client operator.
 *
 * This function initializes a socket client operator and sets the function
 * pointers for connecting to a server.
 *
 * @param opr Pointer to the socket client operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_client_init(socket_client_operator *opr) {
  opr->connect = socket_client_connect_handler;
  return socket_create(&opr->client_info);
}

/**
 * @brief Initializes a socket server operator.
 *
 * This function initializes a socket server operator and sets the function
 * pointers for accepting connections and listening for incoming connections.
 *
 * @param opr Pointer to the socket server operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_server_init(socket_server_operator *opr) {
  opr->accept_block = socket_server_accept_block_handler;
  opr->accept_unblock = socket_server_accept_unblock_handler;
  opr->listen = socket_server_listen_handler;
  return socket_create(&opr->server_info);
}

/**
 * @brief Connects a socket client to a server.
 *
 * This function connects a socket client to a server with the specified IP
 * address and port.
 *
 * @param opr Pointer to the socket client operator.
 * @param ip_addr IP address of the server.
 * @param port Port number of the server.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_client_connect(socket_client_operator *opr, char *ip_addr,
                              int port) {
  return opr->connect(opr, ip_addr, port);
}

/**
 * @brief Closes a socket client.
 *
 * This function closes a socket client.
 *
 * @param opr Pointer to the socket client operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_client_close(socket_client_operator *opr) {
  return socket_close(&opr->client_info);
}

/**
 * @brief Accepts an incoming connection on a socket server (blocking).
 *
 * This function accepts an incoming connection on a socket server in blocking
 * mode and sets the socket of the accepted connection in the provided
 * `info` structure.
 *
 * @param opr Pointer to the socket server operator.
 * @param info Pointer to the socket_info structure to store connection details.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_server_accept_block(socket_server_operator *opr,
                                   socket_info *info) {
  return opr->accept_block(opr, info);
}

/**
 * @brief Accepts an incoming connection on a socket server (non-blocking).
 *
 * This function accepts an incoming connection on a socket server in
 * non-blocking mode and sets the socket of the accepted connection in the
 * provided `info` structure.
 *
 * @param opr Pointer to the socket server operator.
 * @param info Pointer to the socket_info structure to store connection details.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_server_accept_unblock(socket_server_operator *opr,
                                     socket_info *info) {
  return opr->accept_unblock(opr, info);
}

/**
 * @brief Listens for incoming connections on a socket server.
 *
 * This function prepares a socket server to accept incoming connections on
 * the specified port and maximum connection number.
 *
 * @param opr Pointer to the socket server operator.
 * @param port Port number to listen on.
 * @param max_conn_num Maximum number of connections.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_server_listen(socket_server_operator *opr, int port,
                             int max_conn_num) {
  return opr->listen(opr, port, max_conn_num);
}

/**
 * @brief Closes a socket server.
 *
 * This function closes a socket server.
 *
 * @param opr Pointer to the socket server operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_server_close(socket_server_operator *opr) {
  return socket_close(&opr->server_info);
}

/**
 * @brief Receives data from a socket.
 *
 * This function receives data from a socket and stores it in the provided
 * buffer.
 *
 * @param info Pointer to the socket_info structure.
 * @param buf Pointer to the buffer to store received data.
 * @param len Maximum length of data to receive.
 * @return Returns the number of bytes received on success, or -1 on failure.
 */
ssize_t socket_recv(socket_info *info, void *buf, ssize_t len) {
  return recv(info->sockfd, buf, len, 0);
}

/**
 * @brief Sends data through a socket.
 *
 * This function sends data through a socket.
 *
 * @param info Pointer to the socket_info structure.
 * @param buf Pointer to the data to send.
 * @param len Length of the data to send.
 * @return Returns the number of bytes sent on success, or -1 on failure.
 */
ssize_t socket_send(socket_info *info, const void *buf, ssize_t len) {
  return send(info->sockfd, buf, len, 0);
}
