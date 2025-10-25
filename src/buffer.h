#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define NONBUF_ROWS 3
#define BUF_HEIGHT_LARGE_BUFFER (buffer_ctx->term_height - NONBUF_ROWS)
#define BUF_HEIGHT_SMALL_BUFFER ((buffer_ctx->buf_len / 0x10) + 1)
#define BUF_HEIGHT (buffer_ctx->buf_len < BUF_HEIGHT_LARGE_BUFFER * 0x10 ? \
                    BUF_HEIGHT_SMALL_BUFFER : BUF_HEIGHT_LARGE_BUFFER)

/**
 * @enum Mode
 * @brief Enumeration of possible editing modes.
 */
enum Mode
{
    MODE_READ,
    MODE_OVERWRITE,
    MODE_INSERT,
};

/**
 * @enum Style
 * @brief Enumeration of possible byte entry styles.
 */
enum Style
{
    STYLE_ASCII,
    STYLE_HEX,
    STYLE_OCTAL,
    STYLE_DECIMAL,
};

/**
 * @struct Buffer_Ctx
 * @brief Contains context information about the buffer. This information is
 *        used e.g. for navigating and displaying the buffer.
 */
struct Buffer_Ctx
{
    /* File path */
    const char *path;
    /* Buffer contents */
    uint8_t *buf;
    /* Number of bytes in buffer (may be shorter than allocated length) */
    size_t buf_len;
    /* Number of bytes allocated */
    size_t alloc_len;
    /* Determine which address to show at the top of the address frame */
    size_t first_row;
    /* Position of point as offset from the begining of buffer */
    size_t point_pos;
    /* Mode for editing buffer */
    enum Mode mode;
    /* Style of byte entry */
    enum Style style;
    /* Byte entry keystroke count */
    uint8_t k_stroke;
    /* Advance point after overwriting */
    bool advance;
    /* Number of rows in terminal */
    volatile unsigned int term_height;
};

/**
 * @brief Initialize Buffer_Ctx struct.
 * @param[in,out] buffer_ctx structure to initialize
 * @return void
 */
void buffer_init(struct Buffer_Ctx *buffer_ctx);

/**
 * @brief Get position of point (cursor).
 * @param[in] buffer_ctx buffer context structure
 * @return position of point as offset from the begining of buffer
 */
size_t buffer_getPosition(struct Buffer_Ctx *buffer_ctx);

#endif /* __BUFFER_H__ */
