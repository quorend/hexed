#ifndef __FILE_ACCESS_H__
#define __FILE_ACCESS_H__

#include "buffer.h"

/**
 * @brief Read file into buffer_ctx's buffer.
 * @param[in,out] buffer_ctx context containing pointer to buffer
 * @param[in] path file to be read
 * @return 0 on success, otherwise non-zero
 *
 * @note This function allocates memory for the buffer. Caller is responsible
 *       for calling free() on buffer_ctx->buf when file_access_loadFile() is
 *       successful.
 */
int file_access_loadFile(struct Buffer_Ctx *buffer_ctx, const char *path);

/**
 * @brief Write buffer to file.
 * @param[in] buffer_ctx context containing file path and pointer to buffer
 * @return 0 on success, otherwise negative return code
 */
int file_access_saveFile(struct Buffer_Ctx *buffer_ctx);

#endif /* __FILE_ACCESS_H__ */
