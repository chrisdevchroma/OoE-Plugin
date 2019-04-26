//
// Created by Master on 4/24/19.
//

#ifndef OOE_LOG_H
#define OOE_LOG_H

#endif //OOE_LOG_H

#define BUF_MAX_LEN 512

#include <stdarg.h>

int log_Vwritef(const char *buffer, va_list list);
int log_writef(const char *buffer, ...);

void log_write(const char *buffer);
