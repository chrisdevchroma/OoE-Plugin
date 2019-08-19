//
// Created by Master on 4/24/19.
//

#include <string.h>
#include <stdarg.h>

#include <vitasdk.h>
#include <psp2/kernel/clib.h>
#include <psp2/io/stat.h>

#include "../../common/src/headers/constants.h"
#include "../../common/src/headers/file.h"
#include "../../common/src/headers/plate.h"
#include "../../common/src/headers/log.h"

int log_writef(const char *format, ...) {
    va_list list;
    va_start(list, format);
    int ret = log_Vwritef(format, list);
    va_end(list);
    return ret;
}

int log_Vwritef(const char *format, va_list list) {
    char buffer[BUF_MAX_LEN];
    int ret = sceClibVsnprintf(buffer, sizeof(buffer), format, list);
    log_write(buffer);
    return ret;
}
