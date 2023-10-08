/**
 * @file socket_operator.h
 * @brief Socket Operator Header File
 * @author moecly
 */

#ifndef __SOCKET_OPERATOR_H_
#define __SOCKET_OPERATOR_H_

#include "c-utils/c-utils.h"
#include <arpa/inet.h>

/**
 * @struct socket_info
 * @brief Structure to hold socket information.
 */
typedef struct {
  int sockfd;                  /**< Socket file descriptor. */
  struct sockaddr_in sockaddr; /**< Socket address information. */
  socklen_t addr_len;          /**< Length of the socket address. */
} socket_info;

/**
 * @struct socket_client_operator
 * @brief Structure for socket client operations.
 */
typedef struct socket_client_operator {
  socket_info client_info; /**< Socket client information. */
  /**
   * @brief Function pointer to connect a socket client to a server.
   *
   * @param opr Pointer to the socket client operator.
   * @param ip_addr IP address of the server.
   * @param port Port number of the server.
   * @return Returns ret_ok on success, ret_err on failure.
   */
  ret_val (*connect)(struct socket_client_operator *opr, char *ip_addr,
                     int port);
} socket_client_operator;

/**
 * @struct socket_server_operator
 * @brief Structure for socket server operations.
 */
typedef struct socket_server_operator {
  socket_info server_info; /**< Socket server information. */
  /**
   * @brief Function pointer to accept an incoming connection on the server
   * socket (non-blocking).
   *
   * @param opr Pointer to the socket server operator.
   * @param info Pointer to the socket_info structure to store connection
   * details.
   * @return Returns ret_ok on success, ret_err on failure.
   */
  ret_val (*accept_unblock)(struct socket_server_operator *opr,
                            socket_info *info);
  /**
   * @brief Function pointer to accept an incoming connection on the server
   * socket (blocking).
   *
   * @param opr Pointer to the socket server operator.
   * @param info Pointer to the socket_info structure to store connection
   * details.
   * @return Returns ret_ok on success, ret_err on failure.
   */
  ret_val (*accept_block)(struct socket_server_operator *opr,
                          socket_info *info);
  /**
   * @brief Function pointer to listen for incoming connections on the server
   * socket.
   *
   * @param opr Pointer to the socket server operator.
   * @param port Port number to listen on.
   * @param max_conn_num Maximum number of connections.
   * @return Returns ret_ok on success, ret_err on failure.
   */
  ret_val (*listen)(struct socket_server_operator *opr, int port,
                    int max_conn_num);
} socket_server_operator;

/**
 * @brief Initializes a socket client operator.
 *
 * This function initializes a socket client operator and sets the function
 * pointers for connecting to a server.
 *
 * @param opr Pointer to the socket client operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_client_init(socket_client_operator *opr);

/**
 * @brief Initializes a socket server operator.
 *
 * This function initializes a socket server operator and sets the function
 * pointers for accepting connections and listening for incoming connections.
 *
 * @param opr Pointer to the socket server operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_server_init(socket_server_operator *opr);

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
                              int port);

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
                                   socket_info *info);

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
                                     socket_info *info);

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
                             int max_conn_num);

/**
 * @brief Closes a socket client.
 *
 * This function closes a socket client.
 *
 * @param opr Pointer to the socket client operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_client_close(socket_client_operator *opr);

/**
 * @brief Closes a socket server.
 *
 * This function closes a socket server.
 *
 * @param opr Pointer to the socket server operator.
 * @return Returns ret_ok on success, ret_err on failure.
 */
ret_val socket_server_close(socket_server_operator *opr);

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
ssize_t socket_recv(socket_info *info, void *buf, ssize_t len);

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
ssize_t socket_send(socket_info *info, const void *buf, ssize_t len);

#endif // !__SOCKET_OPERATOR_H_
