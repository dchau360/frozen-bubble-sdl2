/*
 * WebSocket upgrade and frame codec for fb-server.
 * Allows browser clients (WASM) to connect alongside native TCP clients.
 */

#pragma once

#include <sys/types.h>

int     ws_is_websocket(int fd);
void    ws_reset(int fd);

/* After accept(): sniff for HTTP upgrade; upgrade the fd if WS.
 * Returns 1 if upgraded, 0 if plain TCP (leaves fd untouched). */
int     ws_detect_and_upgrade(int fd);

/* Send data wrapped in a WebSocket text frame. */
ssize_t ws_send(int fd, const char* data, int len);

/* Decode all complete WebSocket frames in buf[0..*len-1] in-place,
 * replacing raw frame bytes with decoded payload bytes.
 * On return *len holds the total decoded payload bytes.
 * Returns:  1  at least one frame decoded successfully
 *           0  buffer holds an incomplete frame (partial raw bytes
 *              remain at the start of buf so the caller can save them)
 *          -1  fatal protocol error (close frame, bad length, etc.)  */
int     ws_decode_inplace(char* buf, int* len);
