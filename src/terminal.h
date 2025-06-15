#ifndef __TERMINAL_H__
#define __TERMINAL_H__

/**
 * @brief Set to noncannonical mode and do not echo. Only necessary when input
 *        comes from stdin. Terminal attributes are restored on program exit.
 * @return void
 */
void set_input_mode(void);

#endif /* __TERMINAL_H__ */
