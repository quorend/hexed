#ifndef __INPUT_H__
#define __INPUT_H__

#include "buffer.h"

/**
 * @brief Begin accepting input. This funtion will return when 0x04 byte is
 *        read.
 * @param[in,out] buffer_ctx buffer context structure
 * @param[in] fd file descriptor to read input from (typically stdin)
 * @return 0 on success, or errno on read() error
 */
int input_accept(struct Buffer_Ctx *buffer_ctx, int fd);

#endif /* __INPUT_H__ */
