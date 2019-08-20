//
// Created by Master on 4/24/19.
//

#include <vitasdk.h>
#include <stdarg.h>
#include <string.h>
#include <kuio.h>

#include "headers/constants.h"
#include "headers/log.h"

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

/**
 * https://github.com/CelesteBlue-dev/PSVita-StorageMgr/blob/master/kernel/main.c#L1221
 */
void log_write(const char *buffer) {
    if (kuIoMkdir(OOE_FOLDER_PATH) == -1) {
        sceClibPrintf("Failed to make directory \"%s\"!\n", OOE_FOLDER_PATH);
        return;
    }

    SceUID fd;
    kuIoOpen(LOG_FILE_PATH, SCE_O_WRONLY | SCE_O_CREAT | SCE_O_APPEND, &fd);
    if (!fd) return;
    kuIoWrite(fd, buffer, strlen(buffer));
    kuIoClose(fd);
}
